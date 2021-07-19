#ifndef SIS810_PARSE_H
#define SIS810_PARSE_H
//-------------------------------------------------------------------------
//=========================================================================
//####### DESCRIPTIONBEGIN #######
//
// parse.h
//
// Author:       Chaoban Wang
// Date:         2009-03-30
// Purpose:
// Description:
//
//=========================================================================


enum ParseState
{
    _HEADID,
    _COMMAND,
    _FLAG1,
    _FLAG2,
    _FLAG3,
    _DATA,
};


void Parsefile(FILE *fpin, FILE *fpout);

int Ascii2Int(int ch);

int GetDate(FILE *fpin);

void ReceiveData(int state, FILE *fpin, FILE *fpout);

#endif // SIS810_PARSE_H
 