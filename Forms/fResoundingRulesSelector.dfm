object ResoundingRulesSelector: TResoundingRulesSelector
  Left = 204
  Top = 177
  BorderStyle = bsDialog
  Caption = #1042#1099#1073#1086#1088' '#1087#1088#1072#1074#1080#1083
  ClientHeight = 415
  ClientWidth = 641
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  PixelsPerInch = 96
  TextHeight = 13
  object PRulesListPanel: TPanel
    Left = 9
    Top = 8
    Width = 624
    Height = 369
    BevelOuter = bvLowered
    Ctl3D = True
    ParentCtl3D = False
    TabOrder = 0
    object LTotalTextsInfo: TLabel
      Left = 16
      Top = 8
      Width = 328
      Height = 16
      Caption = #1055#1086#1078#1072#1083#1091#1081#1089#1090#1072', '#1074#1099#1073#1077#1088#1080#1090#1077' '#1087#1088#1072#1074#1080#1083#1072' '#1076#1083#1103' '#1072#1085#1072#1083#1080#1079#1072':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object LPlusInfo: TLabel
      Left = 32
      Top = 280
      Width = 127
      Height = 13
      Caption = '(+n)   "'#1061#1086#1088#1086#1096#1077#1077'" '#1087#1088#1072#1074#1080#1083#1086
    end
    object LMinusInfo: TLabel
      Left = 32
      Top = 296
      Width = 112
      Height = 13
      Caption = '(-n)    "'#1055#1083#1086#1093#1086#1077'" '#1087#1083#1086#1093#1086#1077
    end
    object Label1: TLabel
      Left = 192
      Top = 296
      Width = 199
      Height = 13
      Caption = '(B)    '#1054#1076#1085#1086#1089#1090#1086#1088#1086#1085#1085#1077#1077' '#1086#1073#1088#1072#1090#1085#1086#1077' '#1087#1088#1072#1074#1080#1083#1086
    end
    object Label3: TLabel
      Left = 408
      Top = 280
      Width = 154
      Height = 13
      Caption = '(BF)    '#1044#1074#1091#1093#1089#1090#1086#1088#1086#1085#1085#1077#1077' '#1087#1088#1072#1074#1080#1083#1086
    end
    object Label2: TLabel
      Left = 192
      Top = 280
      Width = 189
      Height = 13
      Caption = '(F)    '#1054#1076#1085#1086#1089#1090#1086#1088#1086#1085#1085#1077#1077' '#1087#1088#1103#1084#1086#1077' '#1087#1088#1072#1074#1080#1083#1086
    end
    object Label4: TLabel
      Left = 56
      Top = 320
      Width = 539
      Height = 13
      Caption = 
        #1055#1088#1080#1084#1077#1095#1072#1085#1080#1077'. '#1044#1072#1085#1085#1099#1077' '#1087#1088#1072#1074#1080#1083#1072' '#1089#1086#1079#1076#1072#1085#1099' '#1074' '#1076#1077#1084#1086#1085#1089#1090#1088#1072#1094#1080#1086#1085#1085#1099#1093' '#1094#1077#1083#1103#1093' '#1080' '#1084#1086 +
        #1075#1091#1090' '#1073#1099#1090#1100' '#1085#1077#1076#1086#1089#1090#1072#1090#1086#1095#1085#1086' '#1093#1086#1088#1086#1096#1080#1084#1080
    end
    object Label5: TLabel
      Left = 56
      Top = 336
      Width = 517
      Height = 13
      Caption = 
        #1082#1088#1080#1090#1077#1088#1080#1103#1084#1080' '#1076#1083#1103' '#1086#1094#1077#1085#1082#1080' '#1073#1083#1072#1075#1086#1079#1074#1091#1095#1080#1103'. '#1057#1087#1080#1089#1086#1082' '#1087#1088#1072#1074#1080#1083' '#1085#1077' '#1080' '#1089#1095#1077#1088#1087#1099#1074#1072#1077#1090 +
        #1089#1103' '#1090#1086#1083#1100#1082#1086' '#1076#1072#1085#1085#1099#1084#1080' '#1087#1088#1072#1074#1080#1083#1072#1084#1080'.'
    end
    object Label6: TLabel
      Left = 56
      Top = 352
      Width = 542
      Height = 13
      Caption = 
        #1042' '#1089#1083#1077#1076#1091#1102#1097#1080#1093' '#1074#1077#1088#1089#1080#1103#1093' '#1087#1083#1072#1085#1080#1088#1091#1077#1090#1089#1103' '#1089#1086#1079#1076#1072#1090#1100' '#1088#1077#1076#1072#1082#1090#1086#1088' '#1087#1088#1072#1074#1080#1083' '#1076#1083#1103' '#1088#1072#1089#1096 +
        #1080#1088#1077#1085#1085#1086#1075#1086' '#1103#1079#1099#1082#1072' RRL ('#1089#1084'. '#1057#1087#1088#1072#1074#1082#1091').'
    end
    object CLBRulesListBox: TCheckListBox
      Left = 8
      Top = 32
      Width = 609
      Height = 241
      Ctl3D = False
      ItemHeight = 13
      ParentCtl3D = False
      TabOrder = 0
    end
  end
  object BtnMakeResoundingMap: TButton
    Left = 440
    Top = 384
    Width = 187
    Height = 25
    Caption = #1055#1086#1089#1090#1088#1086#1080#1090#1100' '#1082#1072#1088#1090#1091' '#1073#1083#1072#1075#1086#1079#1074#1091#1095#1080#1103
    ModalResult = 1
    TabOrder = 1
  end
  object BtnCancel: TButton
    Left = 16
    Top = 384
    Width = 185
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
end
