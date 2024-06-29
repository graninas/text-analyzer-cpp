/****************************************************************************
** TextAnalyser 0.4 alpha
** Copyright (C) 2011 Granin A.S.
** Contact: Granin A.S. (graninas@gmail.com)
**
** This file is part of the TextAnalyser project.
**
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/licenses/gpl.html.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** If you have questions regarding the use of this file, please contact
** author (graninas@gmail.com).
**
****************************************************************************/

//---------------------------------------------------------------------------

#ifndef fWorkingTableH
#define fWorkingTableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include "PERFGRAP.h"
//---------------------------------------------------------------------------
class TResoundingMapTableOld : public TForm
{
__published:	// IDE-managed Components
    TPanel *PMainPanel;
    TMainMenu *MainMenu1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
    TMenuItem *N4;
    TActionList *ActionList1;
    TAction *AOpenText;
    TAction *ACloseProgram;
    TOpenDialog *ODOpenText;
    TPanel *PMainTopPanel;
    TPanel *PMainBottomPanel;
    TPanel *PLeftTextPanel;
    TPanel *PRightMapPanel;
    TPanel *PLeftInfoPanel;
    TPanel *PRightInfoPanel;
    TSplitter *STopVerticalSplitter;
    TSplitter *SBottomVerticalSplitter;
    TAction *AFormResize;
    TPageControl *PCMapModePages;
    TTabSheet *TSResoundingMap;
    TTabSheet *TSAssonanses;
    TTabSheet *TSFlesch;
    TPanel *PMapDrawingPanel1;
    TPanel *PMapDrawingPanel2;
    TPanel *PMapDrawingPanel3;
    TPageControl *PCMainPages;
    TTabSheet *TSText;
    TTabSheet *TSRulesList;
    TTabSheet *TSAssonances;
    TToolBar *TBPageNavigation;
    TSplitter *SMainHorizontalSplitter;
    TToolButton *TBPageLeftEnd;
    TToolButton *TBPageRight;
    TComboBox *CBPagesList;
    TImageList *ILPageNavigationIcons;
    TToolButton *TBPageRightEnd;
    TToolButton *TBPageLeft;
    TAction *AFirstPage;
    TAction *APrevPage;
    TAction *ANextPage;
    TAction *ALastPage;
    TPanel *PTextPanel;
    TAction *ATextPanelResize;
    TAction *AHorizontalPanelsResize;
    TPanel *PResoundingMapRulesListPanel;
    TCheckBox *ChkRule1;
    TCheckBox *ChkRule2;
    TCheckBox *ChkRule3;
    TCheckBox *ChkRule4;
    TCheckBox *ChkRule5;
    TCheckBox *ChkRule6;
    TAction *AResoundingMapRulesChange;
    TButton *BtnApplyResoundingMapRules;
    TAction *AResoundingMapRulesLoad;
    TAction *AAssonancesMapRulesLoad;
    TPanel *PAssonancesReulesListPanel;
    TCheckBox *ChkAR6;
    TCheckBox *ChkAR5;
    TCheckBox *ChkAR4;
    TCheckBox *ChkAR3;
    TCheckBox *ChkAR2;
    TCheckBox *ChkAR1;
    TButton *BtnApplyAssonancesMapRules;
    TAction *AAssonancesMapRulesChange;
    TToolBar *TBRulesNavigation;
    TToolButton *TBNextRulePage;
    TToolButton *TBPrevRulePage;
    TImageList *ILRuleNavigationIcons;
    TAction *ANextRulePage;
    TAction *APrevRulePage;
    TAction *AEnablePagesNavigation;
    TAction *ADisablePagesNavigation;
    TCheckBox *ChkAR7;
    TCheckBox *ChkRule7;
    TPageControl *PCRules;
    TTabSheet *TSMapRules;
    TTabSheet *TSAssonancesRules;
    TAction *AOnResoundingMapPanelClick;
    TMemo *MMapRules;
    TMemo *MAssonancesRules;
    TAction *AOnAssonancesMapPanelClick;
    void __fastcall AOpenTextExecute(TObject *Sender);
    void __fastcall ACloseProgramExecute(TObject *Sender);
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall AResoundingMapRulesChangeExecute(TObject *Sender);
    void __fastcall AResoundingMapRulesLoadExecute(TObject *Sender);
    void __fastcall AAssonancesMapRulesLoadExecute(TObject *Sender);
    void __fastcall AAssonancesMapRulesChangeExecute(TObject *Sender);
    void __fastcall AEnablePagesNavigationExecute(TObject *Sender);
    void __fastcall ADisablePagesNavigationExecute(TObject *Sender);
    void __fastcall AFirstPageExecute(TObject *Sender);
    void __fastcall APrevPageExecute(TObject *Sender);
    void __fastcall ANextPageExecute(TObject *Sender);
    void __fastcall ALastPageExecute(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall AOnResoundingMapPanelClickExecute(TObject *Sender);
    void __fastcall PMapDrawingPanel1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall AOnAssonancesMapPanelClickExecute(TObject *Sender);
    void __fastcall PMapDrawingPanel2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations


    int  _MouseX,  _MouseY;

public:		// User declarations
    __fastcall TResoundingMapTableOld(TComponent* Owner);


    void __fastcall SetResoundingRulesList(const AnsiString & tList);
    void __fastcall SetAssonancesRulesList(const AnsiString & tList);
};
//---------------------------------------------------------------------------
extern PACKAGE TResoundingMapTableOld *ResoundingMapTableOld;
//---------------------------------------------------------------------------
#endif
