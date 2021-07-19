object Form1: TForm1
  Left = 65
  Top = 159
  BorderStyle = bsSingle
  Caption = 'SiS Track Viewer'
  ClientHeight = 675
  ClientWidth = 1190
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010002002020100000000000E80200002600000010101000000000002801
    00000E0300002800000020000000400000000100040000000000800200000000
    0000000000000000000000000000000000000000800000800000008080008000
    00008000800080800000C0C0C000808080000000FF0000FF000000FFFF00FF00
    0000FF00FF00FFFF0000FFFFFF00000000000000000000000000000000000000
    000800000000000080808080000000080000BBBBFFFFFBFB0000887808000800
    B3B3B8BBBFBFBFB3B3B30087878000FBBBBBBBBBFFFFFBFB3B3B3B08787800F3
    B3B3B8BBBFBFBFB3B3B3B307878700FBBBBB0000000000003B3B3B08787800F3
    0000BBBBFFFFFBFB0000B30787800000B3B3B8BBBFBFBFB3B3B30008080000FB
    BBBBBBBBFFFFFBFB3B3B3B00000000F3B3B3B8BBBFBFBFB3B3B3B300000000FB
    BBBB0000000000003B3B3B00000000F30000BBBBFFFFFBFB0000B30000000000
    B3B3B8BBBFBFBFB3B3B30000000000FBBBBBBBBBFFFFFBFB3B3B3B00000000F3
    B3B3B8BBBFBFBFB3B3B3B300000000FBBBBB0000000000003B3B3B00000000F3
    0000BBBBFFFFFBFB0000B30000000000B3B3B8BBBFBFBFB3B3B30000000000FB
    BBBBBBBBFFFFFBFB3B3B3B00000000F3B3B3B8BBBFBFBFB3B3B3B300000000FB
    BBBB0000000000003B3B3B00000000F30000FBFBFBFBFBFB0000B30000000000
    BFBFBFBFBFBFBFBFBFBF0000000000FBFBFBFBFBFBFBFBFBFBFBFB00000000FF
    BFBFBFBFBFBFBFBFBFBFBF00000000FFFBFBFBFBFBFBFBFBFBFBFF0000000800
    FFFFBFBFBFBFBFBFFFFF0080000000080000FFFFFFFFFFFF0000800000000000
    0008000000000000800000000000000000000000000000000000000000000000
    0000000000000000000000000000FFFFFFFFFE00055FE000000B800000018000
    00008000000080000000800000018000000B8000001F8000001F8000001F8000
    001F8000001F8000001F8000001F8000001F8000001F8000001F8000001F8000
    001F8000001F8000001F8000001F8000001F8000001F8000001F8000001FE000
    007FFE0007FFFFFFFFFFFFFFFFFF280000001000000020000000010004000000
    0000C00000000000000000000000000000000000000000000000000080000080
    000000808000800000008000800080800000C0C0C000808080000000FF0000FF
    000000FFFF00FF000000FF00FF00FFFF0000FFFFFF0000080000008887870800
    BBFBFB008878803B3BFFF3B3088703B3BBFBFB3B30780B3B000000B3B0800300
    3BFFF300300000B3BBFBFB3B00000B3B000000B3B00003003BFFF300300000B3
    BBFBFB3B00000B3B000000B3B0000300BFBFBF00300000FBFBFBFBFB000080FF
    BFBFBFFF08000800FFFFFF0080000008000000800000E0000000800000000000
    0000000000000001000000030000000300000003000000030000000300000003
    000000030000000300000003000080070000E01F0000}
  OldCreateOrder = False
  Position = poScreenCenter
  Visible = True
  OnActivate = FormActivate
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 10
    Top = 296
    Width = 460
    Height = 250
  end
  object Image2: TImage
    Left = 602
    Top = 296
    Width = 460
    Height = 250
  end
  object Mark: TLabel
    Left = 470
    Top = 32
    Width = 255
    Height = 24
    Caption = 'Phase II and Tracker Viewer'
    Font.Charset = ANSI_CHARSET
    Font.Color = clNavy
    Font.Height = -21
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object LabelFileName: TLabel
    Left = 16
    Top = 214
    Width = 70
    Height = 19
    Caption = 'File Name: '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
  end
  object LabelName: TLabel
    Left = 82
    Top = 216
    Width = 4
    Height = 16
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Arial'
    Font.Style = []
    ParentFont = False
  end
  object Panel2: TPanel
    Left = 600
    Top = 560
    Width = 579
    Height = 73
    Color = clActiveBorder
    TabOrder = 2
    object Label1: TLabel
      Left = 10
      Top = 6
      Width = 71
      Height = 31
      Caption = 'Track'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -27
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LabelTotalfm: TLabel
      Left = 122
      Top = 12
      Width = 94
      Height = 16
      Caption = 'Total 0 frames.'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label9: TLabel
      Left = 10
      Top = 41
      Width = 94
      Height = 15
      Caption = 'Show all orbit >>'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
    end
  end
  object lstps2Info: TListBox
    Left = 476
    Top = 296
    Width = 110
    Height = 250
    TabStop = False
    Color = clInfoBk
    Ctl3D = False
    ItemHeight = 13
    ParentCtl3D = False
    TabOrder = 5
  end
  object TrackBar1: TTrackBar
    Left = 704
    Top = 592
    Width = 393
    Height = 35
    Max = 1
    Orientation = trHorizontal
    PageSize = 1
    Frequency = 50
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    ThumbLength = 25
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 648
    Width = 1190
    Height = 27
    Panels = <>
    SimplePanel = False
  end
  object SpinFrameEdit: TCSpinEdit
    Left = 1106
    Top = 594
    Width = 60
    Height = 22
    EditorEnabled = False
    MaxValue = 1
    TabOrder = 1
    OnChange = SpinFrameEditChange
  end
  object lsttrkInfo: TListBox
    Left = 1068
    Top = 296
    Width = 110
    Height = 250
    TabStop = False
    Color = clInfoBk
    ItemHeight = 13
    TabOrder = 6
  end
  object Panel1: TPanel
    Left = 10
    Top = 560
    Width = 279
    Height = 73
    Color = clActiveBorder
    TabOrder = 4
    object Label4: TLabel
      Left = 8
      Top = 37
      Width = 44
      Height = 21
      Caption = 'Mode'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object RadioFrame: TRadioButton
      Left = 64
      Top = 41
      Width = 81
      Height = 17
      Caption = 'Frame'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      TabStop = True
    end
    object RadioPoint: TRadioButton
      Left = 136
      Top = 41
      Width = 65
      Height = 17
      Caption = 'Point'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object SpinModeEdit: TCSpinEdit
      Left = 206
      Top = 38
      Width = 60
      Height = 22
      EditorEnabled = False
      MaxValue = 1
      TabOrder = 2
      OnChange = SpinModeEditChange
    end
  end
  object ToolBar1: TToolBar
    Left = 0
    Top = 0
    Width = 1190
    Height = 33
    ButtonHeight = 25
    Caption = 'ToolBar1'
    Color = clActiveBorder
    ParentColor = False
    TabOrder = 8
    object btnOpen: TButton
      Left = 0
      Top = 2
      Width = 75
      Height = 25
      Caption = '&Open...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      TabStop = False
      OnClick = btnOpenFileClick
    end
    object btnSave: TButton
      Left = 75
      Top = 2
      Width = 75
      Height = 25
      Caption = '&Save'
      Enabled = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      TabStop = False
      OnClick = btnSaveClick
    end
    object btnExit: TButton
      Left = 150
      Top = 2
      Width = 75
      Height = 25
      Caption = '&Exit'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      TabStop = False
      OnClick = btnCloseClick
    end
    object btnAbout: TButton
      Left = 225
      Top = 2
      Width = 75
      Height = 25
      Caption = '&About'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      TabStop = False
      OnClick = btnAboutClick
    end
  end
  object Panel3: TPanel
    Left = 10
    Top = 240
    Width = 575
    Height = 41
    Color = clSilver
    TabOrder = 9
    object Label2: TLabel
      Left = 15
      Top = 8
      Width = 231
      Height = 24
      Caption = 'Phase II points coordinate'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label5: TLabel
      Left = 478
      Top = 20
      Width = 74
      Height = 18
      Caption = 'Frame Info'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel4: TPanel
    Left = 602
    Top = 240
    Width = 575
    Height = 41
    Color = clSilver
    TabOrder = 10
    object Label3: TLabel
      Left = 15
      Top = 8
      Width = 297
      Height = 24
      Caption = 'Track points coordinate and state'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -21
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label6: TLabel
      Left = 478
      Top = 20
      Width = 74
      Height = 18
      Caption = 'Frame Info'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = []
      ParentFont = False
    end
  end
  object Panel5: TPanel
    Left = 296
    Top = 560
    Width = 289
    Height = 73
    TabOrder = 3
    object Label7: TLabel
      Left = 8
      Top = 37
      Width = 41
      Height = 21
      Caption = 'From'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 108
      Top = 37
      Width = 15
      Height = 21
      Caption = 'to'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 8
      Top = 8
      Width = 86
      Height = 21
      Caption = 'Frame Rate'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -19
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 150
      Top = 10
      Width = 18
      Height = 16
      Caption = 'fps'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label12: TLabel
      Left = 178
      Top = 40
      Width = 18
      Height = 16
      Caption = 'frm'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object PlayFromEdit: TEdit
      Left = 58
      Top = 38
      Width = 45
      Height = 21
      TabOrder = 0
      Text = '0'
    end
    object PlayEndEdit: TEdit
      Left = 130
      Top = 38
      Width = 45
      Height = 21
      TabOrder = 1
      Text = '0'
    end
    object BtnPlay: TButton
      Left = 205
      Top = 8
      Width = 75
      Height = 55
      Caption = '&Play'
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clNavy
      Font.Height = -27
      Font.Name = 'Times New Roman'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = BtnPlayClick
    end
    object EditFPS: TEdit
      Left = 102
      Top = 8
      Width = 45
      Height = 21
      TabOrder = 2
      Text = '80'
    end
  end
  object GBxOption: TGroupBox
    Left = 1008
    Top = 48
    Width = 169
    Height = 177
    Caption = '  Tracker Optimal  '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 11
    object Label13: TLabel
      Left = 34
      Top = 120
      Width = 73
      Height = 16
      Caption = 'Fames Num'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object CheckBoxDeGhost: TCheckBox
      Left = 16
      Top = 24
      Width = 145
      Height = 17
      Caption = 'Delete Ghost points'
      Checked = True
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 0
      OnClick = CheckBoxDeGhostClick
    end
    object CheckBoxNsGhost: TCheckBox
      Left = 16
      Top = 48
      Width = 145
      Height = 17
      Caption = 'Delete Noise ghost'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = CheckBoxNsGhostClick
    end
    object CheckBoxSmooth: TCheckBox
      Left = 16
      Top = 72
      Width = 145
      Height = 17
      Caption = 'Smooth points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = CheckBoxSmoothClick
    end
    object CheckBoxQueue: TCheckBox
      Left = 16
      Top = 96
      Width = 145
      Height = 17
      Caption = 'Queue Frames'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = CheckBoxQueueClick
    end
    object QueueFrameNum: TEdit
      Left = 113
      Top = 118
      Width = 45
      Height = 23
      Enabled = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Times New Roman'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      Text = '8'
    end
    object SwapAxis: TCheckBox
      Left = 16
      Top = 144
      Width = 97
      Height = 17
      Caption = 'Swap Axis'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Microsoft Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = SwapAxisClick
    end
  end
  object GBxState: TGroupBox
    Left = 888
    Top = 120
    Width = 105
    Height = 105
    Caption = '  Point state  '
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 12
    object Label15: TLabel
      Left = 16
      Top = 16
      Width = 15
      Height = 29
      Caption = #9679
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label18: TLabel
      Left = 40
      Top = 24
      Width = 26
      Height = 16
      Caption = 'Birth'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label16: TLabel
      Left = 16
      Top = 40
      Width = 15
      Height = 29
      Caption = #9679
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label19: TLabel
      Left = 40
      Top = 48
      Width = 34
      Height = 16
      Caption = 'Move'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label17: TLabel
      Left = 16
      Top = 64
      Width = 15
      Height = 29
      Caption = #9679
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -24
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label20: TLabel
      Left = 40
      Top = 72
      Width = 36
      Height = 16
      Caption = 'Death'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  object OpenDialog1: TOpenDialog
    Filter = #20108#36914#20301#21450#25991#23383#27284'(*.p2;*.txt; *.bin)|*.txt;*.bin;*.p2|All File(*.*)|*.*'
    Title = 'Open File ...'
    Top = 32
  end
  object TimerPlay: TTimer
    Interval = 0
    OnTimer = TimerPlayTimer
    Left = 32
    Top = 32
  end
end
