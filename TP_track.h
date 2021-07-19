#ifndef _DEFINE_TPTRACK
#define _DEFINE_TPTRACK
//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// TP_track.h
//
// Author:       Chaoban/SiS4315
// Date:         2009-02-17
// Purpose:      SiS810 board support.
// Description:  Implementations of SiS810 Touch Screen.
//
//=========================================================================

#include "Global.h"

/********************/
/*   Options Keys   */
/********************/
#define _SMOOTHP
#define _SORT_POINTS
//#define _PATCH_GHOST
#define _DEL_GHOST
#define _FILTERGHOST
//#define _NORM_COORD     // Normalized, for sparsh-ui.

/********************/
/*  General define  */
/********************/
#define MAXTOUCH    100  // Max Touch points.
#define X_Line      38
#define Y_Line      20
//#define PPS                100  // Points per second.
#define death_sec  (float)0.15
//#define death_delay     (int)(PPS * death_sec)
#define exact       (float)1.0
#define gexact      (float)0.07


typedef struct
{
    int Tnum;
    unsigned char Sstate;
    unsigned char Scase;
    unsigned char Gcase;
} LSTATE ;

typedef struct
{
    int     ID;
	float	X;
	float	Y;
	unsigned char	TYPE;
} TOUCHPOINT ;

enum TouchPointType
{
    POINT_BIRTH,    // 0
    POINT_DEATH,    // 1
    POINT_MOVE,     // 2
    POINT_TAP,      // 3
    NOTOUCH         // 4
};

enum GhostCase
{
    CNONE = 0,
    CASE_1 = 1,
    CASE_2 = 2,
    CASE_3 = 3,
    CASE_4 = 4
};

enum MultiTouchEvnt
{
    CASE_NONE = 0,
    CASE_HORIZON = 1,
    CASE_VERTICAL = 2
};

float absf(float a);

void Debug_TPInfo(TOUCHPOINT* CurrentEvnt, int* TPnum);

void DetectGhostPoint(TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt, int* TPnum);

void DispatchTouchNumbers(int* TPnum);

void DispatchTouchPoint(int i, TOUCHPOINT* TPEvnt, float* TPBuf);

void FlushDeathPoint(float* TPBuf, int* TPnum, TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt);

void InitialTrack(void);

void PatchGhostPoint(TOUCHPOINT* CurrentEvnt, int* TPnum);

void PickTouchEvent(int i, TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt, float* TPBuf);

void SortTouchPoints(TOUCHPOINT* CurrentEvnt, TOUCHPOINT* PreviousEvnt, int* TPnum);

void TouchPointTrack(int* TPnum, float* TP, float* TPBuf);

#endif  //_DEFINE_TPTRACK

