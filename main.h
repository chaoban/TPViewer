//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "CSPIN.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <ToolWin.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
    TImage *Image1;
    TListBox *lstps2Info;
    TOpenDialog *OpenDialog1;
    TTrackBar *TrackBar1;
    TStatusBar *StatusBar1;
    TCSpinEdit *SpinFrameEdit;
    TListBox *lsttrkInfo;
    TImage *Image2;
    TPanel *Panel1;
    TRadioButton *RadioFrame;
    TRadioButton *RadioPoint;
    TCSpinEdit *SpinModeEdit;
    TLabel *Label4;
    TPanel *Panel2;
    TLabel *Label1;
    TToolBar *ToolBar1;
    TButton *btnOpen;
    TButton *btnExit;
    TButton *btnAbout;
    TPanel *Panel3;
    TPanel *Panel4;
    TLabel *Label2;
    TLabel *Label5;
    TLabel *Label3;
    TLabel *Label6;
    TPanel *Panel5;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Mark;
    TEdit *PlayFromEdit;
    TEdit *PlayEndEdit;
    TButton *btnSave;
    TTimer *TimerPlay;
    TButton *BtnPlay;
    TEdit *EditFPS;
    TLabel *Label10;
    TGroupBox *GBxOption;
    TCheckBox *CheckBoxDeGhost;
    TCheckBox *CheckBoxNsGhost;
    TCheckBox *CheckBoxSmooth;
    TGroupBox *GBxState;
    TLabel *Label15;
    TLabel *Label18;
    TLabel *Label16;
    TLabel *Label19;
    TLabel *Label17;
    TLabel *Label20;
    TLabel *LabelTotalfm;
    TLabel *LabelFileName;
    TLabel *LabelName;
    TLabel *Label9;
    TLabel *Label11;
    TLabel *Label12;
    TCheckBox *CheckBoxQueue;
    TEdit *QueueFrameNum;
    TLabel *Label13;
        TCheckBox *SwapAxis;
    void __fastcall btnOpenFileClick(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall btnCloseClick(TObject *Sender);
    void __fastcall TrackBar1Change(TObject *Sender);
    void __fastcall FormActivate(TObject *Sender);
    void __fastcall SpinFrameEditChange(TObject *Sender);
    void __fastcall btnAboutClick(TObject *Sender);
    void __fastcall SpinModeEditChange(TObject *Sender);
    void __fastcall BtnPlayClick(TObject *Sender);
    void __fastcall btnSaveClick(TObject *Sender);
        void __fastcall CheckBoxDeGhostClick(TObject *Sender);
    void __fastcall CheckBoxNsGhostClick(TObject *Sender);
    void __fastcall CheckBoxSmoothClick(TObject *Sender);
    void __fastcall TimerPlayTimer(TObject *Sender);
    void __fastcall CheckBoxQueueClick(TObject *Sender);
        void __fastcall SwapAxisClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
