//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// TPtrack.cpp
//
// Author:       Chaoban/SiS4315
// Date:         2009-02-17
// Purpose:      SiS810 Multi-touch screen board.
// Description:  Implementations of SiS810 Multi-touch screen.
//
//=========================================================================

#include <string.h>
#include <alloc.h>
#include "Global.h"
#include "TP_track.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "queue.h"

#ifdef _DEBUG_PRINT
unsigned int fid = 0;
FILE *fptk = fopen("Track_DetailInfo.txt", "wb");
#endif

extern bool bDeGhost;
extern bool bNsGhost;
extern bool bSmooth;
extern bool bQueue;

LSTATE LASTATE;
TOUCHPOINT	PreviousEvnt[MAXTOUCH], CurrentEvnt[MAXTOUCH], SmoothEvnt[1];

#ifdef _QUEUE_FRAME
QFrame  Qframe, Cframe;
Queue   qu;
#ifdef _QUEUE_PNT
extern FILE *QFILE;
#endif
#endif

int initialized = 1;
int death_delay;
extern int framepersecond;
int iframe;

int pcnt2;

float
absf(float a)
{
    a = a > 0 ? a : (-a);
    return (a);
}

void
InitialTrack(void)
{
    int i = 0;

    death_delay = (int)(framepersecond * death_sec);

    for (i = 0; i < MAXTOUCH; i++)
    {
        CurrentEvnt[i].X = PreviousEvnt[i].X = 0;
        CurrentEvnt[i].Y = PreviousEvnt[i].Y = 0;
        CurrentEvnt[i].TYPE = PreviousEvnt[i].TYPE = NOTOUCH;
    }

    LASTATE.Tnum = CNONE;
    LASTATE.Gcase = CNONE;
    LASTATE.Sstate = CNONE;
    LASTATE.Scase = CNONE;

#ifdef _QUEUE_FRAME
    if (bQueue)
    {
        initial_queue(&qu);
    }
#endif

#ifdef _DEBUG_PRINT
    fprintf(fptk, "Tracking Detail Information.\n");
    fprintf(fptk, "\n");
#endif
}

void
TouchPointTrack(int* TPnum, float* TP, float* TPBuf)
{
    float diff_x = 0, diff_y = 0;
    int i = 0, z = 0;

	static int track_num = 0;

	pcnt2 = 0;

    if (initialized == 1)
    {
        InitialTrack();
        initialized = 0;
    }

    CurrentEvnt[i].ID = 0;
    CurrentEvnt[i].X = 0;
	CurrentEvnt[i].Y = 0;
	CurrentEvnt[i].TYPE = NOTOUCH;

#ifdef _DEBUG_PRINT
//    fprintf(fptk, "Touch points tracking.\n");
    iframe = ++fid;
    fprintf(fptk, "Frame: %d\n", iframe);
#endif
#ifdef _QUEUE_FRAME
#ifdef _QUEUE_PNT
    fprintf(QFILE, "Frame: %d\n", iframe);
#endif
#endif

    if (*TPnum > 0)
    {
        for (i = 0; i < *TPnum; i++)
        {
            CurrentEvnt[i].ID = i+1;
            CurrentEvnt[i].X = *((float*)(TP+i*4+1));
	        CurrentEvnt[i].Y = *((float*)(TP+i*4+2));
	        CurrentEvnt[i].TYPE = POINT_BIRTH;
        }

#ifdef _DEBUG_PRINT
        fprintf(fptk, "Count: %d\n", *TPnum);
        fprintf(fptk, "Original row data:\n");
        Debug_TPInfo(CurrentEvnt, TPnum);
#endif

#ifdef _QUEUE_FRAME
        if (bQueue)
        {
            Qframe.fid = Qframe.fid + 1;
		    Qframe.pcnt = *TPnum;
            for (i = 0; i < *TPnum; i++)
            {
                Qframe.points[i] = CurrentEvnt[i];
            }

            z = enqueue(&qu, Qframe);

            if (!z)
            {
                if (dequeue(&qu))
                {
                    Cframe = qu.fm[qu.front];
                }

#ifdef _QUEUE_PNT
                fprintf(QFILE, "Cframe.fid=%d, pcnt=%d\n", Cframe.fid, Cframe.pcnt);

                for (i = 0; i < Cframe.pcnt; i++)
                {
                    fprintf(QFILE, "Cframe.points[%d].X=%f, Y=%f\n", i, Cframe.points[i].X, Cframe.points[i].Y);
                }
#endif

                *TPnum = Cframe.pcnt;

                for (i = 0; i < *TPnum; i++)
                {
                    CurrentEvnt[i] = Cframe.points[i];
                }
                Debug_TPInfo(CurrentEvnt, TPnum);

                enqueue(&qu, Qframe);
            }
            else
            {
                return;
            }
        }
#endif
	}

#ifdef _QUEUE_FRAME
    if (bQueue)
    {
        if (*TPnum == 0)
        {
            if (dequeue(&qu))
            {
                Cframe = qu.fm[qu.front];

#ifdef _QUEUE_PNT
                fprintf(QFILE, "Cframe.fid=%d, pcnt=%d\n", Cframe.fid, Cframe.pcnt);
                for (i = 0; i < Cframe.pcnt; i++)
                {
                    fprintf(QFILE, "Cframe.points[%d].X=%f, Y=%f\n", i, Cframe.points[i].X, Cframe.points[i].Y);
                }
#endif

                *TPnum = Cframe.pcnt;

                for (i = 0; i < *TPnum; i++)
                {
                    CurrentEvnt[i] = Cframe.points[i];
                }
                Debug_TPInfo(CurrentEvnt, TPnum);
            }
        }
    }
#endif

	if (*TPnum > 0)
    {
        // Filter closed-garbage point when in single touch.
/*
        if (*TPnum == 2)
        {
            diff_x = absf(CurrentEvnt[0].X - CurrentEvnt[1].X);
            diff_y = absf(CurrentEvnt[0].Y - CurrentEvnt[1].Y);

            if ((diff_x < 0.5) && (diff_y < 0.5))
            {
                *TPnum = 1;
                CurrentEvnt[1].X = 0.0;
                CurrentEvnt[1].Y = 0.0;
            }
        }
*/

#ifdef _FILTERGHOST
    if (bNsGhost)
    {
        // When Single to Multi, filter ghost signal.
        if ((*TPnum == 2) && (LASTATE.Tnum == 1))
        {
            if (CurrentEvnt[0].Y == CurrentEvnt[1].Y)
            {
                diff_x = absf(CurrentEvnt[0].X - PreviousEvnt[0].X);
#ifdef _DEBUG_PRINT
                fprintf(fptk, "diff_x=%f\n", diff_x);
#endif
                if (diff_x < gexact)
                {
                    *TPnum = 1;
#ifdef _DEBUG_PRINT
                    fprintf(fptk, "Cut ghost -.\n");
#endif
                }
                else
                {
                    diff_x = absf(CurrentEvnt[1].X - PreviousEvnt[0].X);

                    if (diff_x < gexact)
                    {
                        *TPnum = 1;

                        CurrentEvnt[0].X = CurrentEvnt[1].X;
                        CurrentEvnt[0].Y = CurrentEvnt[1].Y;
#ifdef _DEBUG_PRINT
                        fprintf(fptk, "Cut ghost -.\n");
#endif
                    }
                }
            }
            else if (CurrentEvnt[0].X == CurrentEvnt[1].X)
            {
                diff_y = absf(CurrentEvnt[0].Y - PreviousEvnt[0].Y);
#ifdef _DEBUG_PRINT
                fprintf(fptk, "diff_y=%f\n", diff_y);
#endif
                if (diff_y < gexact)
                {
                    *TPnum = 1;
#ifdef _DEBUG_PRINT
                    fprintf(fptk, "Cut ghost |.\n");
#endif
                }
                else
                {
                    diff_y = absf(CurrentEvnt[1].Y - PreviousEvnt[0].Y);

                    if (diff_y < gexact)
                    {
                        *TPnum = 1;
                        CurrentEvnt[0].X = CurrentEvnt[1].X;
                        CurrentEvnt[0].Y = CurrentEvnt[1].Y;
#ifdef _DEBUG_PRINT
                        fprintf(fptk, "Cut ghost |.\n");
#endif
                    }
                }
            }
        }
    }
#endif

        // Add Smooth points to bridged a gap.
#ifdef _SMOOTHP
    if (bSmooth)
    {
        if ((*TPnum == 1) && (LASTATE.Tnum == 1))
        {
            if (PreviousEvnt[0].TYPE == POINT_MOVE)
            {
                diff_x = absf(CurrentEvnt[0].X - PreviousEvnt[0].X);
                diff_y = absf(CurrentEvnt[0].Y - PreviousEvnt[0].Y);

                if ((diff_x > 1.0) || (diff_y > 1.0))
                {
#ifdef _DEBUG_PRINT
                    fprintf(fptk, "Add smooth point...\n");
#endif
                    float s_div = diff_x > diff_y ? (diff_x / 1.0) : (diff_y / 1.0);

                    float smooth_x = (CurrentEvnt[0].X - PreviousEvnt[0].X) / s_div;
                    float smooth_y = (CurrentEvnt[0].Y - PreviousEvnt[0].Y) / s_div;

                    int si = 0;
                    for (si = 1; si < s_div; si++)
                    {
                        SmoothEvnt[0].ID = 1;
                        SmoothEvnt[0].X = PreviousEvnt[0].X + smooth_x;
                        SmoothEvnt[0].Y = PreviousEvnt[0].Y + smooth_y;
                        SmoothEvnt[0].TYPE = POINT_MOVE;

                        PickTouchEvent(0, SmoothEvnt, PreviousEvnt, TPBuf);
                    }
                }
            }
        }
    }
#endif

#ifdef _SORT_POINTS
        // Sort two horizontal/vertical touch points in every frame.
        SortTouchPoints(CurrentEvnt, PreviousEvnt, TPnum);
#endif

#ifdef _DEL_GHOST
        // Detect ghost Points. Two fingers can make two points and two ghost points.
        if (bDeGhost)
        {
            DetectGhostPoint(CurrentEvnt, PreviousEvnt, TPnum);
        }
#else
#ifdef _PATCH_GHOST
        // Detect ghost Points. Two fingers can make two points and two ghost points.
        // Because of phase1/2 bugs. For temp only.
        PatchGhostPoint(CurrentEvnt, TPnum);
#endif
#endif
        // Pick point and prepare for flush.
        for (i = 0; i < *TPnum; i++)
        {
            PickTouchEvent(i, CurrentEvnt, PreviousEvnt, TPBuf);
        }

        LASTATE.Tnum = *TPnum;
        *TPnum = pcnt2;
        track_num = 0;
    }
    else
    {
		track_num++;

        // After no touch points in N msec, it is death.
        // Flush previous death points that be keeped.
        // If 60 points/sec, 20 points is about 300 msec.
		if (track_num == death_delay)
		{
#ifdef _DEBUG_PRINT
//            fprintf(fptk, "Flush end points. num= %d\n", LASTATE.Tnum);
#endif
			FlushDeathPoint(TPBuf, TPnum, CurrentEvnt, PreviousEvnt);
			track_num = 0;
		}
	}
}

void
DispatchTouchNumbers(int *TPnum)
{
// Dispatch touch number for sparsh-ui Gesture server.
    char sparsh_num = *TPnum;

#ifdef _DEBUG_PRINT
//    fprintf(fptk, ">>>>> Dispatch points number: %d.\n", sparsh_num);
#endif
}

void
DispatchTouchPoint(int i, TOUCHPOINT* TPEvnt, float* TPBuf)
{
    // Normalized, for sparsh-ui.
#ifdef _NORM_COORD
	TPEvnt->X = TPEvnt->X / X_Line;
	TPEvnt->Y = TPEvnt->Y / Y_Line;
#endif

    *(float*)(TPBuf+i*4+0) = TPEvnt->ID;
    *(float*)(TPBuf+i*4+1) = TPEvnt->X;
    *(float*)(TPBuf+i*4+2) = TPEvnt->Y;
    *(float*)(TPBuf+i*4+3) = TPEvnt->TYPE;

#ifdef _DEBUG_PRINT
    fprintf(fptk, ">>>>> Dispatch points id_%d: X=%f, Y=%f, ", TPEvnt->ID, TPEvnt->X, TPEvnt->Y);

    switch (TPEvnt->TYPE)
    {
        case POINT_BIRTH:
            fprintf(fptk, "state: BIRTH.\n");
            break;
        case POINT_DEATH:
            fprintf(fptk, "state: DEATH.\n");
            break;
        case POINT_MOVE:
            fprintf(fptk, "state: MOVE.\n");
            break;
        case POINT_TAP:
            fprintf(fptk, "state: TAP(=BIRTH).\n");
            break;
        default:
            fprintf(fptk, "state: UNKNOW %d.\n", TPEvnt->TYPE);
            break;
    }
#endif

    // Payload, sispatch touch points for sparsh-ui Gesture server.
#ifdef _DEBUG_PRINT
//        fprintf(fptk, "Check Saved buffer that for Gesture server.\n");
//        fprintf(fptk, "TPBuf.ID= %d\n", (unsigned int)*(TPBuf+i*4+0));
//        fprintf(fptk, "TPBuf.X= %f\n", *(TPBuf+i*4+1));
//        fprintf(fptk, "TPBuf.Y= %f\n", *(TPBuf+i*4+2));
//        fprintf(fptk, "TPBuf.STAT= %u\n", (unsigned char)*(TPBuf+i*4+3));
#endif
}

void
Debug_TPInfo(TOUCHPOINT* CurrentEvnt, int* TPnum)
{
#ifdef _DEBUG_PRINT
    int i = 0;
    for (i = 0; i < *TPnum; i++)
    {
        fprintf(fptk, "id_%d: x=%f, y=%f, state=%d.\n",
            CurrentEvnt[i].ID, CurrentEvnt[i].X, CurrentEvnt[i].Y, CurrentEvnt[i].TYPE);
    }
#else
#ifdef _QUEUE_FRAME
#ifdef _QUEUE_PNT
    int i = 0;
    for (i = 0; i < *TPnum; i++)
    {
        fprintf(QFILE, "id_%d: x=%f, y=%f, state=%d.\n",
            CurrentEvnt[i].ID, CurrentEvnt[i].X, CurrentEvnt[i].Y, CurrentEvnt[i].TYPE);
    }
#endif
#endif
#endif
}
