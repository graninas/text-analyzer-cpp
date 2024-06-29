object AnalysisProcess: TAnalysisProcess
  Left = 243
  Top = 188
  BorderStyle = bsDialog
  Caption = #1055#1088#1086#1094#1077#1089#1089' '#1072#1085#1072#1083#1080#1079#1072
  ClientHeight = 383
  ClientWidth = 570
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnHide = FormHide
  OnShow = FormShow
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
  end
  object BtnShowResults: TButton
    Left = 304
    Top = 352
    Width = 235
    Height = 25
    Caption = #1042#1099#1074#1077#1089#1090#1080' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1099
    Enabled = False
    TabOrder = 2
    OnClick = BtnShowResultsClick
  end
  object BtnClose: TButton
    Left = 32
    Top = 352
    Width = 233
    Height = 25
    Caption = #1047#1072#1082#1088#1099#1090#1100
    ModalResult = 2
    TabOrder = 3
    OnClick = BtnCloseClick
  end
end
