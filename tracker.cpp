//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// tracker.cpp
//
// Author:       Chaoban/SiS4315
// Date:         2009-02-17
// Purpose:      SiS810 Multi-touch screen board.
// Description:  Implementations of SiS810 Multi-touch screen.
//
//=========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <alloc.h>
#include "Global.h"
#include "tracker.h"

#ifdef _OUTPUTF_TRACK
FILE *fptrack = NULL;
FILE *fpp3 = NULL;
#endif

#ifdef _DEBUG_PRINT
extern FILE *fptk;
#endif


bool
Tracker(float *Bufin, float *Bufout, unsigned __int64 sz)
{
    int const MAX_POINTS = 100; // max points per frame

    float memTP[4*MAX_POINTS] = {0};
    float TPBuf[4*MAX_POINTS] = {0};
    unsigned int i = 0, j = 0, y = 0;
    unsigned int frame = 0, temp = 0;
    int count = 0;
    bool bkeep = false;

#ifdef _OUTPUTF_TRACK
    fpp3  = fopen("Track_ListInfo.p3", "wb");
    fptrack = fopen("Track_ListInfo.txt", "w");
    fprintf(fptrack, "Tracking List Information.\n");
    fprintf(fptrack, "\n");
#endif

    while (true)
    {
        if (j > ((sz/4)-1))
        {
            break;
        }

        frame = Bufin[j++];

        if(frame == 0)
        {
            break;
        }

        count = Bufin[j++];

        for(i = 0; i < count; i++)
        {
            memTP[i*4+0] = Bufin[j++];    // id
            memTP[i*4+1] = Bufin[j++];    // x
            memTP[i*4+2] = Bufin[j++];    // y
            memTP[i*4+3] = Bufin[j++];    // state
        }

        TouchPointTrack(&count, memTP, TPBuf);

        Bufout[y++] = frame;
        Bufout[y++] = count;

#ifdef _OUTPUTF_TRACK
        fprintf(fptrack, "frame=%d\n", frame);
        fprintf(fptrack, "count=%d\n", count);

        float ffrm = frame;
        float fcnt = count;
        fwrite(&ffrm, sizeof(float), 1, fpp3);
        fwrite(&fcnt, sizeof(float), 1, fpp3);
#endif
        for (i = 0; i < count; i++)
        {
            Bufout[y++] = TPBuf[i*4+0];   // id
            Bufout[y++] = TPBuf[i*4+1];   // x
            Bufout[y++] = TPBuf[i*4+2];   // y
            Bufout[y++] = TPBuf[i*4+3];   // state

#ifdef _OUTPUTF_TRACK
        fprintf(fptrack, "id=%d\n", (unsigned int)TPBuf[i*4+0]);
        fprintf(fptrack, "x=%f\n", TPBuf[i*4+1]);
        fprintf(fptrack, "y=%f\n", TPBuf[i*4+2]);
        fprintf(fptrack, "state=%d\n", (unsigned int)TPBuf[i*4+3]);

        float fid = (unsigned int)TPBuf[i*4+0];
        float fx = TPBuf[i*4+1];
        float fy = TPBuf[i*4+2];
        float ft = (unsigned int)TPBuf[i*4+3];

        fwrite(&fid, sizeof(float), 1, fpp3);
        fwrite(&fx, sizeof(float), 1, fpp3);
        fwrite(&fy, sizeof(float), 1, fpp3);
        fwrite(&ft, sizeof(float), 1, fpp3);
#endif
        }
    }

#ifdef _OUTPUTF_TRACK
    fclose(fptrack);
#endif
#ifdef _DEBUG_PRINT
    fclose(fptk);
    fclose(fpp3);
#endif

    return true;
}
