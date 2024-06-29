object TestingTable: TTestingTable
  Left = 256
  Top = 211
  Width = 810
  Height = 543
  Caption = 'MainFrm'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 72
    Width = 32
    Height = 13
    Caption = 'Label1'
  end
  object Label2: TLabel
    Left = 8
    Top = 424
    Width = 674
    Height = 13
    Caption = 
      #1057#1080#1089#1090#1077#1084#1072' TTextDataProvider '#1087#1088#1077#1082#1088#1072#1089#1085#1086' '#1088#1072#1073#1086#1090#1072#1077#1090'. '#1053#1077#1086#1073#1093#1086#1076#1080#1084#1086' '#1087#1077#1088#1077#1074#1077#1089 +
      #1090#1080' '#1074#1089#1077' '#1082#1086#1085#1082#1088#1077#1090#1085#1086' '#1086#1087#1088#1077#1076#1077#1083#1077#1085#1085#1099#1077' '#1082#1083#1072#1089#1089#1099' '#1085#1072' TTextDataProvider.'
  end
  object Button1: TButton
    Left = 8
    Top = 200
    Width = 121
    Height = 25
    Caption = 'BaseCoverProcessor'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 8
    Top = 88
    Width = 121
    Height = 25
    Caption = 'ParSentWord'
    TabOrder = 1
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 136
    Top = 8
    Width = 265
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
  end
  object Button3: TButton
    Left = 8
    Top = 168
    Width = 121
    Height = 25
    Caption = 'RuleProcessorTesting'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Edit2: TEdit
    Left = 408
    Top = 8
    Width = 385
    Height = 21
    TabOrder = 5
    Text = 'Edit2'
  end
  object Button4: TButton
    Left = 8
    Top = 8
    Width = 121
    Height = 25
    Caption = 'LoadText'
    TabOrder = 6
    OnClick = Button4Click
  end
  object Memo2: TMemo
    Left = 8
    Top = 240
    Width = 121
    Height = 25
    TabOrder = 7
  end
  object Memo3: TMemo
    Left = 408
    Top = 40
    Width = 185
    Height = 369
    ScrollBars = ssVertical
    TabOrder = 8
  end
  object Button5: TButton
    Left = 0
    Top = 128
    Width = 137
    Height = 25
    Caption = 'Button 5 Syllables, Flesch'
    TabOrder = 9
    OnClick = Button5Click
  end
  object Memo1: TMemo
    Left = 144
    Top = 40
    Width = 257
    Height = 265
    TabOrder = 2
  end
  object Memo4: TMemo
    Left = 600
    Top = 40
    Width = 193
    Height = 369
    ScrollBars = ssVertical
    TabOrder = 10
  end
  object Button6: TButton
    Left = 8
    Top = 304
    Width = 121
    Height = 25
    Caption = 'Button6'
    TabOrder = 11
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 8
    Top = 272
    Width = 121
    Height = 25
    Caption = 'DocumentPaging'
    TabOrder = 12
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 8
    Top = 376
    Width = 121
    Height = 25
    Caption = 'Button8'
    TabOrder = 13
    OnClick = Button8Click
  end
  object BtnSetAuthorAndTitle: TButton
    Left = 8
    Top = 40
    Width = 121
    Height = 25
    Caption = 'SetAuthor and Title'
    TabOrder = 14
    OnClick = BtnSetAuthorAndTitleClick
  end
  object LBTitles: TListBox
    Left = 144
    Top = 312
    Width = 257
    Height = 97
    ItemHeight = 13
    TabOrder = 15
  end
  object Button9: TButton
    Left = 8
    Top = 456
    Width = 121
    Height = 25
    Caption = 'RangeMapsEqualifier'
    TabOrder = 16
    OnClick = Button9Click
  end
  object Button10: TButton
    Left = 144
    Top = 456
    Width = 75
    Height = 25
    Caption = 'Button10'
    TabOrder = 17
  end
  object OpenDialog1: TOpenDialog
    Filter = 'TextFiles|*.txt'
    Left = 8
    Top = 8
  end
end
