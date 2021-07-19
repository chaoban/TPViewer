//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// DeGhost.cpp
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
DetectGhostPoint(TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt, int* TPnum)
{
    float diff_x = 0, diff_y = 0;
    int i = 0;

    if ((LASTATE.Tnum) && (*TPnum == 4))
    {
#ifdef _DEBUG_PRINT
        fprintf(fptk, "Before detect ghost points:\n");
        fprintf(fptk, "Touch points number: %d\n", *TPnum);
        Debug_TPInfo(CurrentEvnt, TPnum);
#endif
/*
        When rotate around through horizon or vertical in CW/CCW,
        detect ghost point will face a difficult choice.

        HORIZONT: 1-2:  CW: 1-1: OK
        HORIZONT: 1-2: CCW: 1-3:
        HORIZONT: 2-1:  CW: 1-4:
        HORIZONT: 2-1: CCW: 1-2: OK

        VERTICAL: 1-2:  CW: 1-2:
        VERTICAL: 1-2: CCW: 1-1: OK
        VERTICAL: 2-1:  CW: 1-3: OK
        VERTICAL: 2-1: CCW: 1-4:
*/
        if (LASTATE.Sstate == CASE_HORIZON)
        {
            if (LASTATE.Scase == CASE_1)
            {
//                if (CCW)
                    LASTATE.Gcase = CASE_3;
            }
            else if (LASTATE.Scase == CASE_2)
            {
//                if (CW)
                    LASTATE.Gcase = CASE_4;
            }
        }
        else if (LASTATE.Sstate == CASE_VERTICAL)
        {
            if (LASTATE.Scase == CASE_1)
            {
//                if (CW)
                    LASTATE.Gcase = CASE_2;
            }
            else if (LASTATE.Scase == CASE_2)
            {
//                if (CCW)
                    LASTATE.Gcase = CASE_4;
            }
        }

        for (i = 0; i < *TPnum; i++)
        {
            if (PreviousEvnt[0].ID == 1)
            {
                diff_x = absf(PreviousEvnt[0].X - CurrentEvnt[i].X);
                diff_y = absf(PreviousEvnt[0].Y - CurrentEvnt[i].Y);
            }
            else if (PreviousEvnt[1].ID == 1)
            {
                diff_x = absf(PreviousEvnt[1].X - CurrentEvnt[i].X);
                diff_y = absf(PreviousEvnt[1].Y - CurrentEvnt[i].Y);
            }

            if ((diff_x < exact) && (diff_y < exact))
            {
                switch ( i )
                {
                    case 0:
//                        CurrentEvnt[0] = CurrentEvnt[0];
                        CurrentEvnt[1] = CurrentEvnt[3];
                        LASTATE.Gcase = CASE_1;

#ifdef _DEBUG_PRINT
                        fprintf(fptk, "Detect-ghost case: 1 -> %d.\n", LASTATE.Gcase);
#ifdef _DEBUG_DRAW
fprintf(fptk, "  _______       _______       _______  \n");
fprintf(fptk, " |(1)    |     |(1)  2 |     |(1)    | \n");
fprintf(fptk, " |       | --> |       | --> |       | \n");
fprintf(fptk, " |       |     | 3  (4)|     |    (2)| \n");
fprintf(fptk, "  ¢w------       ¢w------       ¢w------  \n");
fprintf(fptk, "\n");
#endif
#endif
                        break;

                    case 1:
                        CurrentEvnt[0] = CurrentEvnt[1];
                        CurrentEvnt[1] = CurrentEvnt[2];
                        LASTATE.Gcase = CASE_2;

#ifdef _DEBUG_PRINT
                        fprintf(fptk, "Detect-ghost case: 1 -> %d.\n", LASTATE.Gcase);
#ifdef _DEBUG_DRAW
fprintf(fptk, "  _______       _______       _______  \n");
fprintf(fptk, " |    (1)|     | 1  (2)|     |    (1)| \n");
fprintf(fptk, " |       | --> |       | --> |       | \n");
fprintf(fptk, " |       |     |(3)  4 |     |(2)    | \n");
fprintf(fptk, "  ¢w------       ¢w------       ¢w------  \n");
fprintf(fptk, "\n");
#endif
#endif
                        break;

                    case 2:
                        CurrentEvnt[0] = CurrentEvnt[2];
//                        CurrentEvnt[1] = CurrentEvnt[1];
                        LASTATE.Gcase = CASE_3;

#ifdef _DEBUG_PRINT
                        fprintf(fptk, "Detect-ghost case: 1 -> %d.\n", LASTATE.Gcase);
#ifdef _DEBUG_DRAW
fprintf(fptk, "  _______       _______       _______  \n");
fprintf(fptk, " |       |     | 1  (2)|     |    (2)| \n");
fprintf(fptk, " |       | --> |       | --> |       | \n");
fprintf(fptk, " |(1)    |     |(3)  4 |     |(1)    | \n");
fprintf(fptk, "  ¢w------       ¢w------       ¢w------  \n");
fprintf(fptk, "\n");
#endif
#endif
                        break;

                    case 3:
                        CurrentEvnt[1] = CurrentEvnt[0];
                        CurrentEvnt[0] = CurrentEvnt[3];
                        LASTATE.Gcase = CASE_4;

#ifdef _DEBUG_PRINT
                        fprintf(fptk, "Detect-ghost case: 1 -> %d.\n", LASTATE.Gcase);
#ifdef _DEBUG_DRAW
fprintf(fptk, "  _______       _______       _______  \n");
fprintf(fptk, " |       |     |(1)  2 |     |(2)    | \n");
fprintf(fptk, " |       | --> |       | --> |       | \n");
fprintf(fptk, " |    (1)|     | 3  (4)|     |    (1)| \n");
fprintf(fptk, "  ¢w------       ¢w------       ¢w------  \n");
fprintf(fptk, "\n");
#endif
#endif
                        break;

                    default:
                        break;
                }

                CurrentEvnt[0].ID = 1;
                CurrentEvnt[1].ID = 2;

                // Ignor Point 3 & 4.
                CurrentEvnt[2].TYPE = NOTOUCH;
                CurrentEvnt[3].TYPE = NOTOUCH;
                *TPnum = 2;
            }
        }

#ifdef _DEBUG_PRINT
        fprintf(fptk, "After detect ghost points:\n");
        fprintf(fptk, "Touch points number: %d\n", *TPnum);
        Debug_TPInfo(CurrentEvnt, TPnum);
#endif
    }
    else
    {
    // TODO:
#ifdef _DEBUG_PRINT
//        fprintf(fptk, "No detect ghost points.\n");
#endif
    }
}

void
PatchGhostPoint(TOUCHPOINT* CurrentEvnt, int* TPnum)
{
    if (*TPnum == 4)
    {
        CurrentEvnt[0] = CurrentEvnt[2];
        CurrentEvnt[0].ID = 1;
        CurrentEvnt[1] = CurrentEvnt[1];
        *TPnum = 2;
    }
}
