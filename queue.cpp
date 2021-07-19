//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// queue.c
//
// Author:       Chaoban/SiS4315
// Date:         2009-04-20
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
#include "DetectNoisePoints.h"

#ifndef _QUEUE_FRAME
#undef _QUEUE_PNT
#endif

#ifdef _QUEUE_PNT
extern FILE *QFILE;
#endif

extern int QueueSize;

int
enqueue(Queue* qu, QFrame Qframe)
{
#ifdef CircQueue
// circule queue
    if ((qu->rear == qu->front) && (qu->tag == 1))
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "Queue is Full.\n");
#endif
        return 0;
    }
    else
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "\nAdd queue...\n");
        fprintf(QFILE, "Qframe.fid=%d, pcnt=%d\n", Qframe.fid, Qframe.pcnt);
        int i = 0;
        for (i = 0; i < Qframe.pcnt; i++)
        {
            fprintf(QFILE, "Qframe.points[%d].X=%f, Y=%f\n", i, Qframe.points[i].X, Qframe.points[i].Y);
        }
#endif
        qu->rear = (qu->rear + 1) % QueueSize;
        qu->fm[qu->rear] = Qframe;

        if (qu->rear == qu->front)
        {
            qu->tag = 1;
        }
    }
#else
// Linear queue
    if (qu->rear == QueueSize - 1)
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "Queue is Full.\n");
#endif
        return 0;
    }
    else
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "\nAdd queue...\n");
        fprintf(QFILE, "Qframe.fid=%d, pcnt=%d\n", Qframe.fid, Qframe.pcnt);
        int i = 0;
        for (i = 0; i < Qframe.pcnt; i++)
        {
            fprintf(QFILE, "Qframe.points[%d].X=%f, Y=%f\n", i, Qframe.points[i].X, Qframe.points[i].Y);
        }
#endif
        qu->rear = (qu->rear) + 1;
        qu->fm[qu->rear] = Qframe;
    }
#endif

#ifdef _QUEUE_PNT
    fprintf(QFILE, "qu->front=%d, rear=%d\n", qu->front, qu->rear);
    fprintf(QFILE, "\n");
#endif

    // If Queue is full. Now to process those frames.
    if ((qu->rear == (QueueSize - 1)) && (qu->front == (QueueSize - 1)))
    {
        DetectNoiseOfFrame(qu);
    }

    return 1;
}

int
dequeue(Queue* qu)
{
#ifdef CircQueue
// circule queue
    if (isEmpty(qu))
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "Queue is empty.\n");
#endif
        return 0;
    }
    else
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "\nDel queue.\n");
#endif
        qu->front = (qu->front + 1) % QueueSize;

        if (qu->rear == qu->front)
        {
            qu->tag = 0;
        }
    }
#else
// Linear queue
    if (isEmpty(qu))
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "Queue is empty.\n");
#endif
        return 0;
    }
    else
    {
#ifdef _QUEUE_PNT
        fprintf(QFILE, "\nDel queue.\n");
#endif
        qu->front = (qu->front + 1);
    }
#endif

#ifdef _QUEUE_PNT
    fprintf(QFILE, "qu->front=%d, rear=%d\n", qu->front, qu->rear);
//   fprintf(QFILE, "\n");
#endif
    return 1;
}

int
isEmpty(Queue* qu)
{
#ifdef CircQueue
// circule queue
    if ((qu->front == qu->rear) && (qu->tag == 0))
    {
        qu->front = QueueSize - 1;
        qu->rear = QueueSize - 1;
        return 1;
    }
#else
// Linear queue
    if (qu->front == qu->rear)
    {
        qu->front = -1;
        qu->rear = -1;
        return 1;
    }
#endif
    else
    {
        return 0;
    }
}

void
initial_queue(Queue* qu)
{
#ifdef CircQueue
// circule queue
    qu->front = QueueSize - 1;
    qu->rear = QueueSize - 1;
#else
// Linear queue
    qu->front = -1;
    qu->rear = -1;
#endif
    qu->tag = 0;
}
