//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// PickPoint.cpp
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

extern FILE* fptk;

extern LSTATE LASTATE;

extern int pcnt2;

void
PickTouchEvent(int i, TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt, float* TPBuf)
{
    float fx = CurrentEvnt[i].X;
    float fy = CurrentEvnt[i].Y;

    if ((fx) || (fy))
    {
        if (CurrentEvnt[i].TYPE == NOTOUCH)
        {
		    CurrentEvnt[i].TYPE = POINT_BIRTH;
		}
		else if (CurrentEvnt[i].TYPE == POINT_BIRTH)
		{
            if ((PreviousEvnt[i].TYPE == POINT_BIRTH)
                || (PreviousEvnt[i].TYPE == POINT_MOVE))
            {
		        CurrentEvnt[i].TYPE = POINT_MOVE;
		    }
		}

        // Flush previous points that be keeped.
        if (CurrentEvnt[i].TYPE == POINT_MOVE)
        {
            pcnt2++;
            DispatchTouchPoint(i, &PreviousEvnt[i], TPBuf);
        }

        // Store the event to be played later.
        if (CurrentEvnt[i].TYPE != NOTOUCH)
        {
            PreviousEvnt[i] = CurrentEvnt[i];
        }
    }

#ifdef _DEBUG_PRINT
    fprintf(fptk, "Pick touch event:\n");
    fprintf(fptk, "id_%d: x=%f, y=%f, state=%d.\n",
            CurrentEvnt[i].ID, CurrentEvnt[i].X, CurrentEvnt[i].Y, CurrentEvnt[i].TYPE);
#endif
}