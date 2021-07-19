//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// parse.cpp
//
// Author:       Chaoban Wang
// Date:         2009-04-01
// Purpose:
// Description:
//
//=========================================================================

#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

void
Parsefile(FILE *fpin, FILE *fpout)
{
    int ch;
    unsigned int state = _HEADID;
    static unsigned short pnum = 0;
    unsigned short tempH, tempL;
    unsigned int tick_time;

    while ((ch = getc(fpin)) != EOF)
    {
        switch (state)
        {
            case _HEADID:
                if (ch == 0x50) // 'P'
                {
                    if ((ch = getc(fpin)) == 0x38)  // '8'
                    {
                        if ((ch = getc(fpin)) == 0x31)  // '1'
                        {
                            if ((ch = getc(fpin)) == 0x30) // '0'
                            {
                                tempH = GetDate(fpin);  //High-2Bytes.
                                tempL = GetDate(fpin);  //Low-2Bytes.
                                tick_time = ((tempH << 16) | tempL);

                                state = _COMMAND;
                            }
                        }
                    }
                }
                break;

            case _COMMAND:
                state = _HEADID;

                if (ch == 0xA0)
                {
                    ch = getc(fpin);

                    if (ch == 0x01)
                    {
                        state = _FLAG1;
                    }
                    else if (ch == 0x02)
                    {
                        state = _FLAG2;

                        pnum++;

                        ReceiveData(state, fpin, fpout);
                    }
                    else if (ch == 0x03)
                    {
                        state = _FLAG3;
                    }
                    else
                    {
                    }
                }
                else
                {
                }
                break;

            case _FLAG1:
                // TODO:
                state = _HEADID;
                break;

            case _FLAG2:
                // TODO:
                state = _HEADID;
                break;

            case _FLAG3:
                // TODO:
                state = _HEADID;
                break;

            default:
                break;
        }
    }
}

void
ReceiveData(int state, FILE *fpin, FILE *fpout)
{
    unsigned short rcvbuf[36] = {0};
    unsigned short datalen;   // Read counts of DWORD.
    unsigned short tempH, tempL;
    int i;

    datalen = GetDate(fpin);

    if (state == _FLAG2)
    {
        for (i = 0; i < datalen; i++)
        {
            tempH = GetDate(fpin) & (~0x8000);  //High-2Bytes, 15 bits data.
            tempL = GetDate(fpin) & (~0x8000);  //Low-2Bytes, 15 bits data.

            rcvbuf[i*2] =  tempL;
            rcvbuf[i*2+1] =  tempH;
        }
    }

    for (i = 0; i < (datalen*2 - 1); i++)
    {

    }
}

int
GetDate(FILE *fpin)
{
    unsigned short temp;

    temp = (getc(fpin) << 8) | getc(fpin);

    return temp;
}
