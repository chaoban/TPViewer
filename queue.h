#ifndef _DEFINE_QUEUE_H
#define _DEFINE_QUEUE_H
//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// queue.h
//
// Author:       Chaoban/SiS4315
// Date:         2009-04-20
// Purpose:      SiS810 Multi-touch screen board.
// Description:  Implementations of SiS810 Multi-touch screen.
//
//=========================================================================

#include "TP_track.h"

//extern int QueueSize;

#define QueueArraySize   32
#define CircQueue       // Circule Queue or Linear Queue
#define _QUEUE_PNT       // Output Queue information

#define div_X       10
#define div_Y       6
#define vpax        (float)((X_Line-1) / div_X)
#define vpay        (float)((Y_Line-1) / div_Y)
#define Area	    (float)((X_Line-1) / vpax)

typedef struct
{
    int fid;   // frame number
    int pcnt;   // point count
    TOUCHPOINT points[MAXTOUCH];
} QFrame ;

typedef struct
{
    QFrame fm[QueueArraySize];
    int front;
    int rear;
    int tag;
    int RegBuf[div_X * div_Y];
    int AvgPnt;
    int FilterMinNum;
} Queue ;

int enqueue(Queue* qu, QFrame Qframe);

int dequeue(Queue* qu);

int isEmpty(Queue* qu);

void initial_queue(Queue* qu);

#endif // _DEFINE_QUEUE_H
