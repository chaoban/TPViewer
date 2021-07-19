//--------------------------------------------------------------------------
//==========================================================================
//####### DESCRIPTIONBEGIN #######
//
// main.cpp
//
// Author:       Chaoban Wang
// Date:         2014-04-16
// Purpose:
// Description:
//
//===========================================================================

//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "main.h"
#include "Global.h"
#include "Queue.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"
TForm1 *Form1;

float *Buffile = NULL;
float *Bufout = NULL;
//float *tempbuf = (float *)malloc(1);
float tempbuf[1];

extern bool Tracker(float *bufin, float *bufout, unsigned __int64 sz);
bool floaded = false;
bool fmstart = true;
bool fcalc = false;
bool bDeGhost = false, bNsGhost = false, bSmooth = false, bQueue = false;
bool bsetPlay = true;
bool bSwapAxis = false;
int SStart = 1, SEnd = 2;
int start = 1, end = 2;
static int playframe = 1;
int max_frame = 0;
int QueueSize = 1;
int framepersecond = 1;
extern int initialized;

#define _MAXFPS	300 //Max Frame per sec when Play
#define _MINFPS	1	//Min Frame per sec when Play

//---------------------------------------------------------------------------

__fastcall TForm1::TForm1(TComponent* Owner):TForm(Owner)
{
    tempbuf[0] = 0;
}
//---------------------------------------------------------------------------

void
ShowModifyMessage(void)
{
	if (floaded)
    {
        ShowMessage(" 變更選項後需重新開啟檔案。 ");
    }
}

void
InitialGlobal(void)
{
    fmstart = true;
    fcalc = false;
    bsetPlay = true;
    SStart = 1, SEnd = 2;
    start = 1, end = 2;
    max_frame = 0;
    initialized = 1;
}

float *PTBuffer(float *buf, TCanvas *cav, TListBox *info, int nFrame) // nFrame=0 表示全部畫出, 否則只畫指定之Frame
{
    unsigned int i, j, nfrm, count, id, state;
    int ZOOM = 12;      // 畫板放大倍數;
    int grid_space = 1; // 每N點素畫一條虛線
    float x, y;
    char str[256];
    unsigned int state_color[] = {clRed, clBlue, clGreen, clBlack};
    char *state_text[] = {"Birth", "Death", "Move", "Unknow",""};
    TRect pt;

    cav->Pen->Color = clSilver;
    cav->Pen->Width = 1;
    cav->Pen->Style = psDot;
    x= X_Line * ZOOM;
    y= Y_Line * ZOOM;
    cav->Rectangle(0, 0, x, y);

    for(i = 0; i < X_Line; i += grid_space)
    {
        cav->MoveTo(i * ZOOM, 0);
        cav->LineTo(i * ZOOM, y);
    }

    for(i = 0; i < Y_Line; i += grid_space)
    {
        cav->MoveTo(0, i * ZOOM);
        cav->LineTo(x, i * ZOOM);
    }

    i = 0 ;
    cav->Pen->Style = psSolid;
    cav->Brush->Style = bsSolid;
    info->Clear();

    while (true)
    {
        nfrm = buf[i++];

        if(nfrm == 0)
        {
            break;
        }

        count = buf[i++];

        if (fcalc == true)
        {
            if (fmstart == true)
            {
                SStart = nfrm;
                if (count != 0)
                    fmstart = false;
            }
            else if (count != 0)
            {
                SEnd = nfrm;
            }

            max_frame = nfrm;
        }

        if(nFrame == 0 || nFrame == nfrm)
        {
            sprintf(str, "Frame: %d", nfrm);
            info->Items->Add(str);
        }

        for(j = 0; j < count; j++)
        {
            id = buf[i++];
			if (bSwapAxis == false)
			{            
            	x = buf[i++];
            	y = buf[i++];
            }
			else
			{
				y = buf[i++];
				x = buf[i++];
			}
            state = buf[i++];

            if((nFrame == 0) || (nFrame == nfrm))
            {
                // cav->Pixels[x * ZOOM][y * ZOOM] = state_color[state]; //*ZOOM是為了將圖放大ZOOM倍
                pt.Left = x * ZOOM - 4;
                pt.Top = y * ZOOM - 4;
                pt.Right= x * ZOOM + 4;
                pt.Bottom= y * ZOOM + 4;
                cav->Pen->Color = state_color[state];
                cav->Brush->Color = state_color[state];
                cav->Ellipse(pt);
                sprintf(str, "ID: %u", id);
                info->Items->Add(str);
                sprintf(str, "Point: %.4f_%.4f", x, y);
                info->Items->Add(str);
                sprintf(str, "State: %s", state_text[state]);
                info->Items->Add(str);
                info->Items->Add("");
            }
        }

        if((nFrame > 0) && (nFrame == nfrm))
        {
            break;
        }
    }
    return(buf);
}

void __fastcall TForm1::btnOpenFileClick(TObject *Sender)
{
    int handle_file;
    unsigned __int64 file_size = 0, sz = 0;

	btnOpen->Enabled = false;
    if(OpenDialog1->Execute() == false)
    {
        btnOpen->Enabled = true;
        return;
    }

    handle_file = FileOpen(OpenDialog1->FileName, fmOpenRead);

    if(handle_file == -1)
    {
        ShowMessage("Error: Can not open the file!");
        btnOpen->Enabled = true;
        return;
    }

    InitialGlobal();

    file_size = FileSeek(handle_file, 0, 2);
    FileSeek(handle_file, 0, 0);

    Buffile = (float *)malloc(file_size + sizeof(float));
    Bufout = (float *)malloc(file_size + sizeof(float));

    sz = FileRead(handle_file, (void *)Buffile, file_size);
    FileClose(handle_file);
    
    bDeGhost = CheckBoxDeGhost->Checked == true ? true:false;
    bNsGhost = CheckBoxNsGhost->Checked == true ? true:false;
    bSmooth = CheckBoxSmooth->Checked == true ? true:false;

    if (CheckBoxQueue->Checked == true)
    {
        bQueue = true;
        QueueFrameNum->Enabled = true;
        QueueSize = atoi(QueueFrameNum->Text.c_str());
        if (QueueSize > QueueArraySize)
        {
            QueueSize = QueueArraySize;
            QueueFrameNum->Text = QueueArraySize;
        }
    }
    else
    {
        bQueue = false;
        QueueFrameNum->Enabled = false;
    }

    framepersecond = atoi(EditFPS->Text.c_str());

    if (framepersecond < _MINFPS)
    {
        framepersecond = _MINFPS;
        ShowMessage("Min FPS = "+String(framepersecond));
    }
    else if (framepersecond > _MAXFPS)
    {
        framepersecond = _MAXFPS;
        ShowMessage("Max FPS = "+String(framepersecond));
    }
    
    EditFPS->Text = IntToStr(framepersecond);

    floaded = Tracker(Buffile, Bufout, sz);

    if (!floaded)
    {
        ShowMessage("Tracking error !");
        btnOpen->Enabled = true;
        return;
    }

    PTBuffer(Buffile, Image1->Canvas, lstps2Info, 0);   // From phase_2
    fcalc = true;
    PTBuffer(Bufout, Image2->Canvas, lsttrkInfo, 0);    // After tracking
    fcalc = false;;

    TrackBar1->Max = SEnd; // Must sets the "Max" value at first.
    TrackBar1->Position = SStart;
    TrackBar1->SelStart = SStart;
    TrackBar1->SelEnd = SEnd;
    TrackBar1->Frequency = (SEnd / 50) > 0 ? SEnd / 50 : 1;

    PlayFromEdit->Text = IntToStr(SStart);
    PlayEndEdit->Text = IntToStr(SEnd);

    SpinModeEdit->MaxValue = (SEnd);
    SpinFrameEdit->MaxValue = (SEnd);
    
    BtnPlay->Enabled = RadioFrame->Checked == true ? true:false;

//    btnSave->Enabled = true;
    btnOpen->Enabled = true;
    TimerPlay->Interval = 0;

    LabelName->Caption = OpenDialog1->FileName;
    LabelTotalfm->Caption = "Total "+IntToStr(max_frame)+" frames, points from "+IntToStr(SStart)+" to "+IntToStr(SEnd)+" frames";

    ShowMessage("Load the File Successfully!\n\nTotal: "+String(sz)+" Bytes.");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
//    if (tempbuf)
//        free(tempbuf);
    if (Buffile)
        free(Buffile);
    if (Bufout)
        free(Bufout);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnCloseClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
    SpinFrameEdit->Text = IntToStr(TrackBar1->Position);
    if (RadioFrame->Checked == true)
    {
        SpinModeEdit->Text = IntToStr(TrackBar1->Position);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
    if (floaded == false)
    {
        PTBuffer(tempbuf, Image1->Canvas, lstps2Info, 0);
        PTBuffer(tempbuf, Image2->Canvas, lsttrkInfo, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpinFrameEditChange(TObject *Sender)
{
    int v;

    Image1->Picture = NULL;
    Image2->Picture = NULL;
    v = atoi(SpinFrameEdit->Text.c_str());
    TrackBar1->Position = v;

    if (RadioFrame->Checked == true)
    {
        SpinModeEdit->Text = IntToStr(v);
    }

	if (floaded)
	{
        if (SpinFrameEdit->Text != "")
        {
            PTBuffer(Buffile, Image1->Canvas, lstps2Info, v);
            PTBuffer(Bufout, Image2->Canvas, lsttrkInfo, v);
        }
        else
        {
            PTBuffer(Buffile, Image1->Canvas, lstps2Info, 0);
            PTBuffer(Bufout, Image2->Canvas, lsttrkInfo, 0);
        }
	}
    else
    {
        PTBuffer(tempbuf, Image1->Canvas, lstps2Info, 0);
        PTBuffer(tempbuf, Image2->Canvas, lsttrkInfo, 0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btnAboutClick(TObject *Sender)
{
    ShowMessage("\nSIS Tracker Viewer v0.1\nSiS Corp. (C)2009-2014\n");
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpinModeEditChange(TObject *Sender)
{
    if (RadioFrame->Checked == true)
    {
        int v;

        Image1->Picture = NULL;
        Image2->Picture = NULL;
        v = atoi(SpinModeEdit->Text.c_str());
        TrackBar1->Position = v;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BtnPlayClick(TObject *Sender)
{
    int i, v;

    if (TimerPlay->Interval == 0)
    {
        btnOpen->Enabled = false;
        start = atoi(PlayFromEdit->Text.c_str());
        end = atoi(PlayEndEdit->Text.c_str());

        if (start < 1)
        {
            start = 1;
            PlayFromEdit->Text = IntToStr(start);
        }
        else if (start > SEnd)
        {
            start = SEnd;
            PlayFromEdit->Text = IntToStr(start);
        }

        if (end < 1)
        {
            end = SEnd;
            PlayEndEdit->Text = IntToStr(end);
        }
        else if (end > SEnd)
        {
            end = SEnd;
            PlayEndEdit->Text = IntToStr(end);
        }

        if (start > end)
        {
            ShowMessage("起始值錯誤 !");
            return;
        }

        if (bsetPlay)
        {
            playframe = start;
            bsetPlay = false;
        }

        EditFPS->Enabled = false;
        PlayFromEdit->Enabled = false;
        PlayEndEdit->Enabled = false;
        BtnPlay->Caption = "&Stop";
        TrackBar1->Enabled = false;
        v = atoi(EditFPS->Text.c_str());

        if (v < _MINFPS)
        {
            v = _MINFPS;
            ShowMessage("Min FPS = "+String(v));
        }
        else if (v > _MAXFPS)
        {
            v = _MAXFPS;
            ShowMessage("Max FPS = "+String(v));
        }
        
        EditFPS->Text = IntToStr(v);
        framepersecond = v;
        TimerPlay->Interval = (1000 / v);
    }
    else
    {
        TimerPlay->Interval = 0;
        btnOpen->Enabled = true;
        EditFPS->Enabled = true;
        TrackBar1->Enabled = true;
        PlayFromEdit->Enabled = true;
        PlayEndEdit->Enabled = true;
        BtnPlay->Caption = "&Play";
    }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btnSaveClick(TObject *Sender)
{
    ShowMessage("  革命尚未完成!  ");
        return;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxDeGhostClick(TObject *Sender)
{
	bDeGhost = CheckBoxDeGhost->Checked == true ? true:false;
    ShowModifyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxNsGhostClick(TObject *Sender)
{
	bNsGhost = CheckBoxNsGhost->Checked == true ? true:false;
    ShowModifyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxSmoothClick(TObject *Sender)
{
	bSmooth = CheckBoxSmooth->Checked == true ? true:false;
    ShowModifyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBoxQueueClick(TObject *Sender)
{
	bQueue = CheckBoxQueue->Checked == true ? true:false;
	QueueFrameNum->Enabled = CheckBoxQueue->Checked == true ? true:false;
    ShowModifyMessage();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TimerPlayTimer(TObject *Sender)
{
    if (playframe <= end)
    {
        TrackBar1->Position = playframe;
        playframe++;
    }
    else
    {
        TimerPlay->Interval = 0;
        btnOpen->Enabled = true;
        PlayFromEdit->Enabled = true;
        PlayEndEdit->Enabled = true;
        TrackBar1->Enabled = true;
        EditFPS->Enabled = true;
        BtnPlay->Caption = "&Play";
        bsetPlay = true;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SwapAxisClick(TObject *Sender)
{
	bSwapAxis = SwapAxis->Checked == true ? true:false;
}
//---------------------------------------------------------------------------

