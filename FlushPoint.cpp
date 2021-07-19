//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// FlushPoint.cpp
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

void
FlushDeathPoint(float* TPBuf, int* TPnum, TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt)
{
#ifdef _DEBUG_PRINT
//    fprintf(fptk, "Flush all ending points.\n");
#endif

    int ppntcount = 0;
//    *TPnum = LASTATE.Tnum;

    int i = 0;
    for(i = 0; i < MAXTOUCH; i++)
    {
        if ((PreviousEvnt[i].TYPE == POINT_BIRTH)
            || (PreviousEvnt[i].TYPE == POINT_MOVE))
        {
            // It like as Gesture...
	        if (PreviousEvnt[i].TYPE == POINT_BIRTH)
	        {
//	            PreviousEvnt[i].TYPE = POINT_TAP;
// Click: send a birth point when finger down, then with a death point when finger up.
//	            DispatchTouchPoint(i, &PreviousEvnt[i], TPBuf);
                PreviousEvnt[i].X = 0;
                PreviousEvnt[i].Y = 0;
                PreviousEvnt[i].TYPE = NOTOUCH;
	        }
	        else if (PreviousEvnt[i].TYPE == POINT_MOVE)
	        {
	            PreviousEvnt[i].TYPE = POINT_DEATH;
#ifdef _DEBUG_PRINT
//                fprintf(fptk, "FlushDeathPoint: Flush Death points.\n");
#endif
				ppntcount ++;
	        }

//	        PreviousEvnt[i].TYPE = POINT_DEATH;

	        DispatchTouchPoint(i, &PreviousEvnt[i], TPBuf);

//	        CurrentEvnt[i].X = PreviousEvnt[i].X = 0;
//            CurrentEvnt[i].Y = PreviousEvnt[i].Y = 0;
//            CurrentEvnt[i].TYPE = PreviousEvnt[i].TYPE = NOTOUCH;
	    }

	    CurrentEvnt[i].X = PreviousEvnt[i].X = 0;
        CurrentEvnt[i].Y = PreviousEvnt[i].Y = 0;
        CurrentEvnt[i].TYPE = PreviousEvnt[i].TYPE = NOTOUCH;
    }

    *TPnum = ppntcount;
    ppntcount = 0;

    LASTATE.Tnum = CNONE;
    LASTATE.Gcase = CNONE;
    LASTATE.Sstate = CNONE;
    LASTATE.Scase = CNONE;
}
