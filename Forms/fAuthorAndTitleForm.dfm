object fAuthorAndTitle: TfAuthorAndTitle
  Left = 289
  Top = 278
  BorderStyle = bsDialog
  Caption = #1040#1074#1090#1086#1088' '#1080' '#1085#1072#1079#1074#1072#1085#1080#1077
  ClientHeight = 180
  ClientWidth = 392
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 8
    Top = 8
    Width = 377
    Height = 129
    TabOrder = 0
    object LCurrentTextNumberInfo: TLabel
      Left = 16
      Top = 24
      Width = 48
      Height = 16
      Caption = #1040#1074#1090#1086#1088':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label1: TLabel
      Left = 16
      Top = 56
      Width = 72
      Height = 16
      Caption = #1053#1072#1079#1074#1072#1085#1080#1077':'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Courier New'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object EAuthor: TEdit
      Left = 104
      Top = 20
      Width = 257
      Height = 19
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 0
      OnChange = EAuthorChange
      OnKeyPress = EAuthorKeyPress
    end
    object ETitle: TEdit
      Left = 104
      Top = 52
      Width = 257
      Height = 19
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 1
      OnChange = ETitleChange
      OnKeyPress = ETitleKeyPress
    end
    object ChkKeyText: TCheckBox
      Left = 16
      Top = 88
      Width = 345
      Height = 17
      Caption = #1050#1083#1102#1095#1077#1074#1086#1081' '#1090#1077#1082#1089#1090', '#1072#1074#1090#1086#1088' '#1082#1086#1090#1086#1088#1086#1075#1086' '#1085#1077#1080#1079#1074#1077#1089#1090#1077#1085
      Enabled = False
      TabOrder = 2
      OnClick = ChkKeyTextClick
    end
  end
  object BtnOK: TBitBtn
    Left = 112
    Top = 144
    Width = 161
    Height = 25
    Caption = #1054#1050
    ModalResult = 1
    TabOrder = 1
  end
  object BtnCancel: TBitBtn
    Left = 296
    Top = 144
    Width = 91
    Height = 25
    Caption = #1054#1090#1084#1077#1085#1072
    ModalResult = 2
    TabOrder = 2
  end
end
