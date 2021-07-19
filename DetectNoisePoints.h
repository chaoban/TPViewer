#ifndef _DEFINE_DETECTNOISE_H
#define _DEFINE_DETECTNOISE_H
//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// DetectNoisePoints.h
//
// Author:       Chaoban/SiS4315
// Date:         2009-05-10
// Purpose:      SiS810 board support.
// Description:  Implementations of SiS810 Touch Screen.
//
//=========================================================================

#include "queue.h"

int DetectNoiseOfFrame(Queue* qu);

int PointWegiht(Queue* qu);

#endif // _DEFINE_DETECTNOISE_H
