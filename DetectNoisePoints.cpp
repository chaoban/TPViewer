//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// DetectNoisePoints.cpp
//
// Author:       Chaoban/SiS4315
// Date:         2009-05-10
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
#include "DetectNoisePoints.h"

#ifndef _QUEUE_FRAME
#undef _QUEUE_PNT
#endif

#ifdef _QUEUE_PNT
FILE *QFILE = fopen("Queue_file_output.txt", "wb");
#endif

extern LSTATE LASTATE;
extern TOUCHPOINT PreviousEvnt;

extern int QueueSize;


int
DetectNoiseOfFrame(Queue* qu)
{
#ifdef _QUEUE_PNT
//    fprintf(QFILE, "qu->front=%d, rear=%d\n", qu->front, qu->rear);
	fprintf(QFILE, "Detect Noise points of frame.\n");
#endif

    int RegNum = 0;
    int i = 0, j = 0, sum = 0;
    float temp_x = 0, temp_y = 0;
    int DelPntCnt = 0;


// Initial queue frame structure.
    qu->FilterMinNum = 0;
    qu->AvgPnt = 0;
    for (i = 0; i < (div_X * div_Y); i++)
    {
        qu->RegBuf[i] = 0;
    }


// Calcualte point region of every frames.
#if 0
    for (i = 0; i < QueueSize; i++)
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "qu->fm[%d]:\n", i);
#endif
        for (j = 0; j < qu->fm[i].pcnt; j++)
        {
            temp_x = qu->fm[i].points[j].X;
            temp_y = qu->fm[i].points[j].Y;
            RegNum = (int)(((int)(temp_y / vpay) * Area) + (int)(temp_x / vpax));

			qu->RegBuf[RegNum] ++;

#ifdef _QUEUE_PNT
            fprintf(QFILE, "point_%d: x= %0.4f, y= %0.4f\n", j+1, temp_x, temp_y);
            fprintf(QFILE, "RegNum= %d\n", RegNum);
#endif
        }

        sum += qu->fm[i].pcnt;
    }
#endif

//
// Detect ghost points in four points frames,
// and to calculate really touched points.
//

    int k = 0, k2 = 0;
    int p4fm = 0;
    unsigned int p4fmnum = 0x00;

    float cmp = 0, dist = 0;
    int nearestpnt = 0;
    int temp = 1;

    float _x = X_Line, _y = Y_Line;
    cmp = pow(_x, 2) + pow(_y, 2);

// Calculate which frames in queue have 4 points.
    for (i = 0; i < QueueSize; i++)
    {
        if (qu->fm[i].pcnt == 4)
        {
            if (1 == temp)
            {
                k = k2 = i;  // First 4 point-frames in queue.
                temp = 0;
            }
            p4fm++; // Number of 4 point-frames in queue.
            p4fmnum |= (1 << i);
        }
    }

// Detect center finger when in rotating. It is more still then other finger.
    if (p4fm > 1)
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "The 4 points frame count in Queue: %d.\n", p4fm);
        fprintf(QFILE, "The 4 points frame num in Queue: 0x%x.\n", p4fmnum);
#endif
        for (i = k + 1; i < QueueSize; i++)
        {
            if (p4fmnum & (1 << i)) // qu->fm[i].pcnt = 4
            {
                for (j = 0; j < 4; j++)
                {
#ifdef _QUEUE_PNT
                    fprintf(QFILE, "qu->fm[%d].points[%d].X = %f\n", i, j, qu->fm[i].points[j].X);
                    fprintf(QFILE, "qu->fm[%d].points[%d].Y = %f\n", i, j, qu->fm[i].points[j].Y);
                    fprintf(QFILE, "qu->fm[%d].points[%d].X = %f\n", k, j, qu->fm[k].points[j].X);
                    fprintf(QFILE, "qu->fm[%d].points[%d].Y = %f\n", k, j, qu->fm[k].points[j].Y);
#endif
                    dist = (pow(absf(qu->fm[i].points[j].X - qu->fm[k].points[j].X), 2) + pow(absf(qu->fm[i].points[j].Y - qu->fm[k].points[j].Y), 2));
#ifdef _QUEUE_PNT
                    fprintf(QFILE, "cmp= %f.\n", cmp);
                    fprintf(QFILE, "dist= %f.\n", dist);
#endif
                    if (cmp > dist)
                    {
                        cmp = dist;
                        nearestpnt = j;
                    }
                }
#ifdef _QUEUE_PNT
                fprintf(QFILE, "Nearest points: %d.\n", nearestpnt);
#endif
                k = i;
            }
        }

// Then delete Ghost 2-points, get really touched 2-points.
        for (i = 0; i < QueueSize; i++)
        {
            if (p4fmnum & (1 << i)) // qu->fm[i].pcnt = 4
            {
                switch (nearestpnt)
                {
                    case 0:
                        qu->fm[i].points[0] = qu->fm[i].points[0];
                        qu->fm[i].points[1] = qu->fm[i].points[3];
                    break;

                    case 1:
                        qu->fm[i].points[0] = qu->fm[i].points[1];
                        qu->fm[i].points[1] = qu->fm[i].points[2];
                    break;

                    case 2:
                        qu->fm[i].points[0] = qu->fm[i].points[1];
                        qu->fm[i].points[1] = qu->fm[i].points[2];
                    break;

                    case 3:
                        qu->fm[i].points[0] = qu->fm[i].points[0];
                        qu->fm[i].points[1] = qu->fm[i].points[3];
                    break;

                    default:
                    break;
                }

                qu->fm[i].points[0].ID = 1;
                qu->fm[i].points[1].ID = 2;
                qu->fm[i].pcnt = 2;
            }
        }

// Replace other noise 2-point by really touch.
        k = 0;

        for (i = 0; i < QueueSize; i++)
        {
#if 0
            if (!(p4fmnum & (1 << i)))
            {
                for (j = 0; j < qu->fm[i].pcnt; j++)
                {
                    qu->fm[i].points[j].X = 0;
                    qu->fm[i].points[j].Y = 0;
                }
                qu->fm[i].pcnt = 0;
            }
#else
            if (p4fmnum & (1 << i))
            {
                k = i;
            }
            else if (!(p4fmnum & (1 << i)))
            {
                if (k)
                {
                    qu->fm[i] = qu->fm[k];
                    k = i;
                    p4fmnum  |= (1 << i);
                }
                else
                {
#ifdef _QUEUE_PNT
                    fprintf(QFILE, "No frame in %d queue.\n", i);
#endif
                    qu->fm[i].points[j].X = 0;
                    qu->fm[i].points[j].Y = 0;
                    qu->fm[i].pcnt = 0;
                }
            }
#endif
        }

        for (i = 0; i < QueueSize; i++)
        {
            if (!(p4fmnum & (1 << i)))
            {
                qu->fm[i] = qu->fm[k2];
            }
        }

        k2 = 0;

#ifdef _QUEUE_PNT
        fprintf(QFILE, "After de-ghost points in Queue.\n");
        for (i = 0; i < QueueSize; i++)
        {
            for (j = 0; j < qu->fm[i].pcnt; j++)
            {
                fprintf(QFILE, "qu->fm[%d].points[%d].X = %f, Y = %f\n", i, j, qu->fm[i].points[j].X, qu->fm[i].points[j].Y);
            }
        }
#endif
    }
    else
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "Nothing of Detect Ghost in Queued frames.\n");
#endif
    }

// Calcualte average points in every frames.
//    qu->AvgPnt = sum / QueueSize;

/*
#ifdef _QUEUE_PNT
	fprintf(QFILE, "\n");
    fprintf(QFILE, "RegBuf[]={");
    for (i = 0; i < (div_X * div_Y); i++)
    {
        fprintf(QFILE, "%d, ", qu->RegBuf[i]);
    }
    fprintf(QFILE, "}\n");
    fprintf(QFILE, "Avg Pnt= %d\n", qu->AvgPnt);
#endif
*/

// Calculate the average to ignored some more/less points.
#if 0
    for (i = 0; i < QueueSize; i++)
    {
        if (qu->fm[i].pcnt > qu->AvgPnt)
        {
#ifdef _QUEUE_PNT
            fprintf(QFILE, "Calculate the average to ignored some more points.\n");
#endif
        }

        if (qu->fm[i].pcnt < qu->AvgPnt)
        {
            if ((1 == LASTATE.Tnum) && (2 == qu->fm[i].pcnt))
            {
#ifdef _QUEUE_PNT
                fprintf(QFILE, "Calculate the average to ignored some less points.\n");
#endif
                if (LASTATE.Scase == CASE_2)
                {
                    qu->fm[i].points[0] = qu->fm[i].points[1];
                }
                qu->fm[i].points[1].X = 0;
                qu->fm[i].points[1].Y = 0;
                qu->fm[i].pcnt = LASTATE.Tnum;
            }
        }
    }
#endif


// Calculate the FilterMinNum to ignored some less points.
#if 0
    qu->FilterMinNum = PointWegiht(qu);

    for (i = 0; i < QueueSize; i++)
    {
        DelPntCnt = 0;

        for (j = 0; j < qu->fm[i].pcnt; j++)
        {
            temp_x = qu->fm[i].points[j].X;
            temp_y = qu->fm[i].points[j].Y;
            RegNum = (int)(((int)(temp_y / vpay) * Area) + (int)(temp_x / vpax));

            // Cut noise points.
            if ((qu->RegBuf[RegNum] <= qu->FilterMinNum) && (qu->RegBuf[RegNum] != 0))
            {
                DelPntCnt ++;
                qu->fm[i].points[j].X = 0;
                qu->fm[i].points[j].Y = 0;
            }
        }

        if (DelPntCnt > 0)
        {
#ifdef _QUEUE_PNT
            fprintf(QFILE, "FilterMinNum= %d\n", qu->FilterMinNum);
#endif
            for (j = 0; j < qu->fm[i].pcnt; j++)
            {
                if ((qu->fm[i].points[j].X == 0) && (qu->fm[i].points[j].Y == 0))
                {
                    // Delete the current point, and shift the next point to this buffer
                    qu->fm[i].points[j].X = qu->fm[i].points[j+1].X;
                    qu->fm[i].points[j].Y = qu->fm[i].points[j+1].Y;
                    qu->fm[i].points[j+1].X = 0;
                    qu->fm[i].points[j+1].Y = 0;
                }
            }

            // Re calculate points number.
            qu->fm[i].pcnt = qu->fm[i].pcnt - DelPntCnt;
        }
    }
#endif

    return 1;
}

int
PointWegiht(Queue* qu)
{
    int i = 0;
    int w = 0;
    int c = 0;

    for (i = 0; i < (div_X * div_Y); i++)
    {
        if (qu->RegBuf[i])
        {
            w += (qu->RegBuf[i]);
            c++;
        }
    }

    if (c)
    {
        return ((int)( w / QueueSize));
    }

    return 1;
}
