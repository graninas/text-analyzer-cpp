object AuthoringAnalyserProcess: TAuthoringAnalyserProcess
  Left = 243
  Top = 188
  Width = 578
  Height = 381
  Caption = #1055#1088#1086#1094#1077#1089#1089' '#1072#1085#1072#1083#1080#1079#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object ChkLBProcessedTexts: TCheckListBox
    Left = 8
    Top = 8
    Width = 241
    Height = 249
    Ctl3D = True
    ItemHeight = 13
    ParentCtl3D = False
    TabOrder = 1
    Visible = False
  end
  object PLeftPanel: TPanel
    Left = 8
    Top = 312
    Width = 241
    Height = 113
    BevelOuter = bvLowered
    TabOrder = 2
    Visible = False
    object LKeyTextInfo: TLabel
      Left = 16
      Top = 16
      Width = 120
      Height = 16
      Caption = #1050#1083#1102#1095#1077#1074#1086#1081' '#1090#1077#1082#1089#1090':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LKeyTextAuthor: TLabel
      Left = 17
      Top = 48
      Width = 13
      Height = 13
      Caption = '...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object LKeyTextTitle: TLabel
      Left = 17
      Top = 81
      Width = 13
      Height = 13
      Caption = '...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
  end
  object BtnCloseWindow: TButton
    Left = 8
    Top = 432
    Width = 241
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100' '#1086#1082#1085#1086
    TabOrder = 3
    Visible = False
  end
  object Button1: TButton
    Left = 8
    Top = 272
    Width = 241
    Height = 25
    Caption = #1053#1086#1074#1099#1081' '#1072#1085#1072#1083#1080#1079
    TabOrder = 4
    Visible = False
  end
  object PRightPanel: TPanel
    Left = 8
    Top = 8
    Width = 553
    Height = 337
    BevelOuter = bvLowered
    TabOrder = 0
    object LCurrentOperation: TLabel
      Left = 88
      Top = 16
      Width = 24
      Height = 16
      Caption = '...'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LCurrentOperationInfo: TLabel
      Left = 8
      Top = 16
      Width = 72
      Height = 16
      Caption = #1054#1087#1077#1088#1072#1094#1080#1103':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LCurrentOperationProgressInfo: TLabel
      Left = 8
      Top = 40
      Width = 72
      Height = 16
      Caption = #1055#1088#1086#1075#1088#1077#1089#1089':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label1: TLabel
      Left = 8
      Top = 280
      Width = 160
      Height = 16
      Caption = #1056#1077#1079#1091#1083#1100#1090#1072#1090#1099' '#1072#1085#1072#1083#1080#1079#1086#1074':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
      Visible = False
    end
    object PBCurrentOperationProgress: TProgressBar
      Left = 88
      Top = 40
      Width = 457
      Height = 16
      Min = 0
      Max = 100
      Smooth = True
      Step = 1
      TabOrder = 0
    end
    object MProcessInfo: TMemo
      Left = 8
      Top = 80
      Width = 537
      Height = 249
      Ctl3D = False
      ParentCtl3D = False
      ScrollBars = ssVertical
      TabOrder = 1
    end
    object Memo1: TMemo
      Left = 8
      Top = 304
      Width = 537
      Height = 137
      Ctl3D = False
      ParentCtl3D = False
      ScrollBars = ssVertical
      TabOrder = 2
      Visible = False
    end
  end
end
