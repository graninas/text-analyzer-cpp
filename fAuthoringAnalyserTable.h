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

#ifndef fAuthoringAnalyserTableH
#define fAuthoringAnalyserTableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <CheckLst.hpp>
#include <Menus.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

#include "UTypes.h"

class TAuthoringAnalyserTable : public TForm
{
__published:	// IDE-managed Components
    TPanel *PMainPanel;
    TPanel *PLeftMainPanel;
	TPanel *PCommonTextsInfo;
    TPanel *PLeftMiddlePanel;
    TPanel *PLeftBottomPanel;
    TLabel *LTotalTextsInfo;
    TLabel *LKeyTextInfo;
	TLabel *LTotalTextsLoaded;
    TLabel *LLoadedTexts;
	TLabel *LTotalTextsSelectedInfo;
	TLabel *LTotalTextsActivated;
    TLabel *LKeyTextNotDefined;
    TLabel *LKeyTextDefined;
    TCheckListBox *CLBTextsListBox;
    TGroupBox *GBCurrentTextInfo;
    TLabel *LCurrentTextAuthor;
    TLabel *LCurrentTextTitle;
    TLabel *LCurrentTextAuthorInfo;
    TLabel *LCurrentTextTitleInfo;
	TButton *BtnDeleteCurrentText;
	TButton *BtnCurrentTextResoundingMap;
	TButton *BtnMakeCurrentTextKeyText;
    TPanel *PCurrentTextOperationsPanel;
	TButton *BtnCurrentTextAuthorAndTitle;
    TMainMenu *MainMenu1;
    TMenuItem *N1;
    TMenuItem *N2;
    TMenuItem *N3;
	TStatusBar *SBMainStatusBar;
    TPanel *PRightMainPanel;
    TPanel *PLeftTopPanel;
    TPanel *PRightMiddlePanel;
    TPanel *PRightMiddleTopPanel;
    TPanel *PLeftSubMiddlePanel;
    TLabel *LKeyText;
    TPanel *PKeyTextInfoPanel;
    TLabel *LKeyTextAuthorInfo;
    TLabel *LKeyTextTitleInfo;
    TLabel *LKeyTextAuthor;
    TLabel *LKeyTextTitle;
    TPanel *PKeyTextOperationsPanel;
    TButton *BtnDeleteKeyText;
	TButton *BtnMakeKeyTextPrototypeText;
    TButton *BtnKeyTextResoundingMap;
    TButton *BtnKeyTextAuthorAndTitle;
    TButton *BtnLoadPrototype;
    TButton *BtnLoadKeyText;
    TButton *BtnDeletePrototypes;
    TPanel *PRightMiddleBottomPanel;
    TCheckBox *ChkSelectAll;
    TLabel *LKeyTextNumberInfo;
    TLabel *LKeyTextNumber;
	TLabel *LCurrentTextNumberInfo;
	TLabel *LCurrentTextNumber;
    TMemo *MSelectedTextPreview;
    TCheckBox *ChkShowPreview;
	TOpenDialog *ODOpenText;
        TBitBtn *BtnDoAnalysis;
        TMenuItem *N4;
        TMenuItem *N5;
	void __fastcall BtnLoadPrototypeClick(TObject *Sender);
	void __fastcall BtnLoadKeyTextClick(TObject *Sender);
	void __fastcall BtnDeletePrototypesClick(TObject *Sender);
	void __fastcall BtnDeleteAllClick(TObject *Sender);
	void __fastcall CLBTextsListBoxClick(TObject *Sender);
	void __fastcall ChkSelectAllClick(TObject *Sender);
	void __fastcall ChkShowPreviewClick(TObject *Sender);
	void __fastcall BtnCurrentTextAuthorAndTitleClick(TObject *Sender);
	void __fastcall BtnMakeCurrentTextKeyTextClick(TObject *Sender);
	void __fastcall BtnDeleteCurrentTextClick(TObject *Sender);
	void __fastcall BtnCurrentTextResoundingMapClick(TObject *Sender);
	void __fastcall BtnKeyTextAuthorAndTitleClick(TObject *Sender);
	void __fastcall BtnMakeKeyTextPrototypeTextClick(TObject *Sender);
	void __fastcall BtnDeleteKeyTextClick(TObject *Sender);
	void __fastcall BtnKeyTextResoundingMapClick(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
        void __fastcall BtnDoAnalysisClick(TObject *Sender);
	void __fastcall N5Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
    __fastcall TAuthoringAnalyserTable(TComponent* Owner);


    TCheckListBox * TextsCheckListBox() { return CLBTextsListBox; }

    void SetCurrentTextInfo(const TSInt & tIndex, const TTextString & tAuthor, const TTextString & tTitle);
    void SetKeyTextInfo(const TSInt & tIndex, const TTextString & tAuthor, const TTextString & tTitle);
    void SetKeyTextDefined(const TBool & tDefined);
    void SetTotalTextsLoaded(const TUInt & tCount);
    void SetTotalTextsActivated(const TUInt & tCount);
    void SetTextPreview(const TTextString & tText);


};
//---------------------------------------------------------------------------
extern PACKAGE TAuthoringAnalyserTable *AuthoringAnalyserTable;
//---------------------------------------------------------------------------
#endif
