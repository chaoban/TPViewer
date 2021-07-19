//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// sortpoint.cpp
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
SortTouchPoints(TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt, int* TPnum)
{
    float diff_x = 0, diff_y = 0;

//    fprintf(fptk, "LASTATE.Scase=%d\n", LASTATE.Scase);
//    fprintf(fptk, "LASTATE.Sstate=%d\n", LASTATE.Sstate);

    if ((LASTATE.Tnum) && (*TPnum == 1) && (LASTATE.Sstate))
    {
		int i,j;
        float cmp, x = X_Line, y=Y_Line;
        double distance;

		cmp = pow( x, 2 ) + pow( y, 2 );
		for(int i=0; i<LASTATE.Tnum; i++)
		{
			distance = pow(absf(CurrentEvnt[0].X-PreviousEvnt[i].X), 2) + pow(absf(CurrentEvnt[0].Y-PreviousEvnt[i].Y), 2);
			if( cmp > distance )
			{
				cmp = distance;
				j = i;
			}
		}

		CurrentEvnt[0].ID = PreviousEvnt[j].ID;

		if( j != 0 )
		{
			TOUCHPOINT  TempEvnt;
            TempEvnt = PreviousEvnt[j];
            PreviousEvnt[j] = PreviousEvnt[0];
            PreviousEvnt[0] = TempEvnt;
		}

//        if (LASTATE.Sstate == CASE_VERTICAL)
//        {
//            diff_y = absf(PreviousEvnt[0].Y - CurrentEvnt[0].Y);
//
//            if (diff_y < exact)
//            {
//                CurrentEvnt[0].ID = PreviousEvnt[0].ID;
//            }
//            else
//            {
//                diff_y = absf(PreviousEvnt[1].Y - CurrentEvnt[0].Y);
//
//                if (diff_y < exact)
//                {
//                    CurrentEvnt[0].ID = PreviousEvnt[1].ID;
//
//                    TOUCHPOINT  TempEvnt;
//
//                    TempEvnt = PreviousEvnt[1];
//                    PreviousEvnt[1] = PreviousEvnt[0];
//                    PreviousEvnt[0] = TempEvnt;
//                }
//            }
////#ifdef _DEBUG_PRINT
////fprintf(fptk, "LASTATE.Tnum=%d, TPnum=%d, LASTATE.Sstate=%d\n", LASTATE.Tnum, *TPnum, LASTATE.Sstate);
////Debug_TPInfo(PreviousEvnt, &LASTATE.Tnum);
////Debug_TPInfo(CurrentEvnt, TPnum);
////#endif
//        }
//        else if (LASTATE.Sstate == CASE_HORIZON)
//        {
//            diff_x = absf(PreviousEvnt[0].X - CurrentEvnt[0].X);
//
//            if (diff_x < exact)
//            {
//                CurrentEvnt[0].ID = PreviousEvnt[0].ID;
//            }
//            else
//            {
//                diff_x = absf(PreviousEvnt[1].X - CurrentEvnt[0].X);
//
//                if (diff_x < exact)
//                {
//                    CurrentEvnt[0].ID = PreviousEvnt[1].ID;
//
//                    TOUCHPOINT  TempEvnt;
//
//                    TempEvnt = PreviousEvnt[1];
//                    PreviousEvnt[1] = PreviousEvnt[0];
//                    PreviousEvnt[0] = TempEvnt;
//                }
//            }
////#ifdef _DEBUG_PRINT
////fprintf(fptk, "LASTATE.Tnum=%d, TPnum=%d, LASTATE.Sstate=%d\n", LASTATE.Tnum, *TPnum, LASTATE.Sstate);
////Debug_TPInfo(PreviousEvnt, &LASTATE.Tnum);
////Debug_TPInfo(CurrentEvnt, TPnum);
////#endif
//        }
//        else
//        {
//            int dist_a = pow(absf(PreviousEvnt[0].X - CurrentEvnt[0].X), 2) + pow(absf(PreviousEvnt[0].Y - CurrentEvnt[0].Y), 2);
//            int dist_b = pow(absf(PreviousEvnt[1].X - CurrentEvnt[0].X), 2) + pow(absf(PreviousEvnt[1].Y - CurrentEvnt[0].Y), 2);
//
//            if (dist_a < dist_b)
//            {
//                CurrentEvnt[0].ID = PreviousEvnt[0].ID;
//            }
//            else
//            {
//                CurrentEvnt[0].ID = PreviousEvnt[1].ID;
//
//                TOUCHPOINT  TempEvnt;
//
//                TempEvnt = PreviousEvnt[1];
//                PreviousEvnt[1] = PreviousEvnt[0];
//                PreviousEvnt[0] = TempEvnt;
//            }
//        }
    }

    if ((LASTATE.Tnum) && (*TPnum == 2))
    {
#ifdef _DEBUG_PRINT
        fprintf(fptk, "Before sort touch points:\n");
        Debug_TPInfo(CurrentEvnt, TPnum);
#endif
        diff_x = absf(CurrentEvnt[0].X - CurrentEvnt[1].X);
        diff_y = absf(CurrentEvnt[0].Y - CurrentEvnt[1].Y);

        if (diff_x < exact)
        {
            LASTATE.Sstate = CASE_VERTICAL;
        }
        else if (diff_y < exact)
        {
            LASTATE.Sstate = CASE_HORIZON;
        }
        else
        {
            LASTATE.Sstate = CASE_NONE;
        }

        if (LASTATE.Sstate == CASE_VERTICAL)
        {
            diff_y = absf(PreviousEvnt[0].Y - CurrentEvnt[0].Y);

            if (diff_y < exact) // No switch, do nothing
            {
                LASTATE.Scase = CASE_1;
            }
            else
            {
                diff_y = absf(PreviousEvnt[0].Y - CurrentEvnt[1].Y);

                if (diff_y < exact)
                {
                    LASTATE.Scase = CASE_2;
#ifdef _DEBUG_DRAW
fprintf(fptk, "  _______       _______       _______  \n");
fprintf(fptk, " |       |     |   1   |     |   2   | \n");
fprintf(fptk, " |       | --> |       | --> |       | \n");
fprintf(fptk, " |  (1)  |     |  (2)  |     |  (1)  | \n");
fprintf(fptk, "  ¢w------       ¢w------       ¢w------  \n");
fprintf(fptk, "\n");
#endif
                }
                else
                {
                    float tmp_a = absf(PreviousEvnt[0].Y - CurrentEvnt[0].Y);
                    float tmp_b = absf(PreviousEvnt[0].Y - CurrentEvnt[1].Y);

                    LASTATE.Scase = tmp_a > tmp_b ? CASE_2 : CASE_1;
                }
            }
        }
        else if (LASTATE.Sstate == CASE_HORIZON)
        {
            diff_x = absf(PreviousEvnt[0].X - CurrentEvnt[0].X);

            if (diff_x < exact) // No switch, do nothing
            {
                LASTATE.Scase = CASE_1;
            }
            else
            {
                diff_x = absf(PreviousEvnt[0].X - CurrentEvnt[1].X);

                if (diff_x < exact)
                {
                    LASTATE.Scase = CASE_2;
#ifdef _DEBUG_DRAW
fprintf(fptk, "  _______       _______       _______  \n");
fprintf(fptk, " |       |     |       |     |       | \n");
fprintf(fptk, " |    (1)| --> |1   (2)| --> |2   (1)| \n");
fprintf(fptk, " |       |     |       |     |       | \n");
fprintf(fptk, "  ¢w------       ¢w------       ¢w------  \n");
fprintf(fptk, "\n");
#endif
                }
                else
                {
                    float tmp_a = absf(PreviousEvnt[0].X - CurrentEvnt[0].X);
                    float tmp_b = absf(PreviousEvnt[0].X - CurrentEvnt[1].X);

                    LASTATE.Scase = tmp_a > tmp_b ? CASE_2 : CASE_1;
                }
            }
        }

        if (LASTATE.Scase == CASE_2)
        {
            if (PreviousEvnt[0].ID == 1)
            {
//                CurrentEvnt[0].ID = 2;
//                CurrentEvnt[1].ID = 1;
//                TOUCHPOINT  TempEvnt;
//
//                // Switch this point X, Y, and state.
//                TempEvnt = CurrentEvnt[0];
//                CurrentEvnt[0] = CurrentEvnt[1];
//                CurrentEvnt[1] = TempEvnt;
//                CurrentEvnt[0].ID = 1;
//                CurrentEvnt[1].ID = 2;
            }
            else
            {
                // No switch, do nothing
            }
        }
        else if (LASTATE.Scase == CASE_1)
        {
            // Points in last frame had be switch.
            if (PreviousEvnt[0].ID == 2)
            {
//                CurrentEvnt[0].ID = 2;
//                CurrentEvnt[1].ID = 1;
//                TOUCHPOINT  TempEvnt;
//
//                TempEvnt = CurrentEvnt[0];
//                CurrentEvnt[0] = CurrentEvnt[1];
//                CurrentEvnt[1] = TempEvnt;
//                CurrentEvnt[0].ID = 1;
//                CurrentEvnt[1].ID = 2;
//
//                LASTATE.Scase = CASE_2;
            }
            else
            {
                // No switch, do nothing
            }
        }

		//search the nearest point from previous point
		int i,j,si,sj;
		float x = X_Line, y=Y_Line, cmp;
		double distance;
		cmp = pow( x, 2 ) + pow( y, 2 );

		for(j=0; j<10; j++)
		for(i=0; i<*TPnum; i++)
		{
			distance = pow(absf(PreviousEvnt[j].X-CurrentEvnt[i].X), 2) + pow(absf(PreviousEvnt[j].Y-CurrentEvnt[i].Y), 2);
			if( cmp > distance )
			{
				cmp = distance;
				si = i;
				sj = j;
			}
		}

		CurrentEvnt[si].ID = PreviousEvnt[sj].ID;
		
		if( sj != 0 )
		{
			TOUCHPOINT  TempEvnt;
			TempEvnt = PreviousEvnt[0];
			PreviousEvnt[0] = PreviousEvnt[sj];
			PreviousEvnt[sj] = TempEvnt;
		}

		i = (*TPnum)-si-1;
		cmp = pow( x, 2 ) + pow( y, 2 );

		for(j=1; j<10; j++)
		{
			distance = pow(absf(PreviousEvnt[j].X-CurrentEvnt[i].X), 2) + pow(absf(PreviousEvnt[j].Y-CurrentEvnt[i].Y), 2);
			if( cmp > distance )
			{
				cmp = distance;
				sj = j;
			}
		}

		CurrentEvnt[i].ID = PreviousEvnt[sj].ID;

        if( CurrentEvnt[i].ID == 0 )
        {
        	CurrentEvnt[i].ID = 2;
        }
		else
		    if( sj != 1 )
    		{
    			TOUCHPOINT  TempEvnt;
    			TempEvnt = PreviousEvnt[1];
    			PreviousEvnt[1] = PreviousEvnt[sj];
    			PreviousEvnt[sj] = TempEvnt;				 
    		}
    	
    	if( CurrentEvnt[0].ID != 1 )
    	{
    		TOUCHPOINT  TempEvnt;
    		TempEvnt = CurrentEvnt[0];
    		CurrentEvnt[0] = CurrentEvnt[1];
    		CurrentEvnt[1] = TempEvnt;
    	}

#ifdef _DEBUG_PRINT
        fprintf(fptk, "Sort two points. state: %d, case: 1 -> %d.\n", LASTATE.Sstate, LASTATE.Scase);
        fprintf(fptk, "After sort touch points:\n");
        Debug_TPInfo(CurrentEvnt, TPnum);
#endif
    }
}