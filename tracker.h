#ifndef _DEFINE_TRACKER
#define _DEFINE_TRACKER
//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// tracker.h
//
// Author:       Chaoban/SiS4315
// Date:         2009-02-17
// Purpose:      SiS810 board support.
// Description:  Implementations of SiS810 Touch Screen.
//
//=========================================================================

extern void TouchPointTrack(int* TPnum, float* TP, float* TPBuf);

bool Tracker(float *Bufin, float *Bufout, unsigned __int64 sz);

#endif
