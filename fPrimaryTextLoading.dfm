object PrimaryTextLoading: TPrimaryTextLoading
  Left = 306
  Top = 373
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = #1047#1072#1075#1088#1091#1079#1082#1072' '#1090#1077#1082#1089#1090#1072
  ClientHeight = 205
  ClientWidth = 442
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object PTextDataEntering: TPanel
    Left = 8
    Top = 80
    Width = 425
    Height = 89
    BevelOuter = bvLowered
    TabOrder = 0
    object LDataEnteringInfo: TLabel
      Left = 16
      Top = 8
      Width = 383
      Height = 13
      Caption = #1042#1099' '#1084#1086#1078#1077#1090#1077' '#1074#1086#1089#1087#1086#1083#1100#1079#1086#1074#1072#1090#1100#1089#1103' '#1087#1072#1091#1079#1086#1081' '#1080' '#1074#1074#1077#1089#1090#1080' '#1076#1072#1085#1085#1099#1077' '#1086' '#1090#1077#1082#1089#1090#1077'.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LAuthorName: TLabel
      Left = 16
      Top = 34
      Width = 63
      Height = 13
      Caption = #1048#1084#1103' '#1072#1074#1090#1086#1088#1072':'
    end
    object LTextTitle: TLabel
      Left = 16
      Top = 59
      Width = 53
      Height = 13
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
    end
    object EAuthorName: TEdit
      Left = 104
      Top = 32
      Width = 305
      Height = 19
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
    end
    object ETitle: TEdit
      Left = 104
      Top = 56
      Width = 305
      Height = 19
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 1
    end
  end
  object PPrimapyProcess: TPanel
    Left = 8
    Top = 8
    Width = 425
    Height = 73
    TabOrder = 1
    object LPrimaryProcessInfo: TLabel
      Left = 64
      Top = 16
      Width = 177
      Height = 13
      Caption = #1048#1076#1077#1090' '#1087#1077#1088#1074#1080#1095#1085#1072#1103' '#1086#1073#1088#1072#1073#1086#1090#1082#1072' '#1090#1077#1082#1089#1090#1072'.'
    end
    object IPrimaryProcessDemo: TImage
      Left = 8
      Top = 8
      Width = 49
      Height = 49
    end
    object PBPrimaryProcessProgress: TProgressBar
      Left = 64
      Top = 40
      Width = 345
      Height = 16
      Min = 0
      Max = 100
      TabOrder = 0
    end
    object PPrimaryProcessInfoAlign: TPanel
      Left = 280
      Top = 16
      Width = 129
      Height = 17
      BevelOuter = bvNone
      TabOrder = 1
      object LPrimaryProcessPercent: TLabel
        Left = 126
        Top = 0
        Width = 3
        Height = 17
        Align = alRight
      end
    end
  end
  object PReadyBtn: TPanel
    Left = 8
    Top = 170
    Width = 425
    Height = 33
    BevelOuter = bvNone
    TabOrder = 2
    object BtnReady: TButton
      Left = 304
      Top = 3
      Width = 107
      Height = 25
      Action = AReadyClick
      Enabled = False
      ModalResult = 1
      TabOrder = 0
    end
    object Button1: TButton
      Left = 16
      Top = 3
      Width = 113
      Height = 25
      Action = ACalcel
      TabOrder = 1
      Visible = False
    end
  end
  object PrimaryTextLoadingActions: TActionList
    Left = 408
    Top = 8
    object AReadyClick: TAction
      Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1100
      OnExecute = AReadyClickExecute
    end
    object AEnableReady: TAction
      Caption = #1055#1088#1086#1076#1086#1083#1078#1080#1090#1100
      OnExecute = AEnableReadyExecute
    end
    object ACalcel: TAction
      Caption = #1054#1090#1084#1077#1085#1080#1090#1100
    end
  end
  object ILProcess: TImageList
    Left = 48
    Top = 32
  end
end
