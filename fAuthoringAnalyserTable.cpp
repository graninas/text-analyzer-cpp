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

#include <vcl.h>
#pragma hdrstop

#include "fAuthorAndTitleForm.h"

#include "fAuthoringAnalyserTable.h"
#include "fAnalysisProcess.h"

#include "fResoundingRulesSelector.h"
#include "fResoundingMapTable.h"

#include "fAuthoringAnalysisResults.h"

#include "CVCLControllersFasade.h"
#include "VVCLViewsContainer.h"

#include "UConstants.h"

#include "fAbout.h"

TVCLControllersFasade       VCLFasade;
TAnalyserControllersFasade  AnalyserFasade;
TVCLViewsContainer  		ViewsContainer;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuthoringAnalyserTable *AuthoringAnalyserTable;
//---------------------------------------------------------------------------
__fastcall TAuthoringAnalyserTable::TAuthoringAnalyserTable(TComponent* Owner)
    : TForm(Owner)
{
VCLFasade.SetAnalyserControllersFasade(&AnalyserFasade);
VCLFasade.SetViewsContainer(&ViewsContainer);
VCLFasade.SetAuthoringAnalyserTable(this);
//VCLFasade.SetResoundingMapTable(ResoundingMapTable);
AnalyserFasade.SetAuthoringAnalysisReporter(&AnalysisReporter);
AnalyserFasade.SetResoundingAnalysisReporter(&AnalysisReporter);

    TVCLViewsContainer * vc = &ViewsContainer;

    vc->AddViewsGroup(cCurrentTextInfo);
    vc->AddView(cCurrentTextInfo, LCurrentTextNumber);
    vc->AddView(cCurrentTextInfo, LCurrentTextAuthor);
    vc->AddView(cCurrentTextInfo, LCurrentTextTitle);
    vc->AddView(cCurrentTextInfo, CLBTextsListBox);
    vc->AddView(cCurrentTextInfo, MSelectedTextPreview);

    vc->AddViewsGroup(cKeyTextInfo);
    vc->AddView(cKeyTextInfo, LKeyTextNumber);
    vc->AddView(cKeyTextInfo, LKeyTextAuthor);
    vc->AddView(cKeyTextInfo, LKeyTextTitle);
    vc->AddView(cKeyTextInfo, CLBTextsListBox);

    vc->AddViewsGroup(cCurrentTextControls);
    vc->AddView(cCurrentTextControls, LCurrentTextNumber);
    vc->AddView(cCurrentTextControls, LCurrentTextAuthor);
    vc->AddView(cCurrentTextControls, LCurrentTextTitle);
   		vc->AddView(cCurrentTextControls, BtnCurrentTextAuthorAndTitle);
	    vc->AddView(cCurrentTextControls, BtnMakeCurrentTextKeyText);
    	vc->AddView(cCurrentTextControls, BtnDeleteCurrentText);
   		vc->AddView(cCurrentTextControls, BtnCurrentTextResoundingMap);

    vc->AddViewsGroup(cKeyTextControls);
    vc->AddView(cKeyTextControls, LKeyTextNumber);
    vc->AddView(cKeyTextControls, LKeyTextAuthor);
    vc->AddView(cKeyTextControls, LKeyTextTitle);
   		vc->AddView(cKeyTextControls, BtnKeyTextAuthorAndTitle);
	    vc->AddView(cKeyTextControls, BtnMakeKeyTextPrototypeText);
    	vc->AddView(cKeyTextControls, BtnDeleteKeyText);
   		vc->AddView(cKeyTextControls, BtnKeyTextResoundingMap);

    vc->AddViewsGroup(cKeyTextDefinedLabel);
    vc->AddView(cKeyTextDefinedLabel, LKeyTextDefined);

    vc->AddViewsGroup(cKeyTextNotDefinedLabel);
    vc->AddView(cKeyTextNotDefinedLabel, LKeyTextNotDefined);

    vc->AddViewsGroup(cSelectedTextPreview);
    vc->AddView(cSelectedTextPreview, MSelectedTextPreview);

    vc->AddViewsGroup(cSelectedTextInfo);
    vc->AddView(cSelectedTextInfo, LKeyTextNumber);
    vc->AddView(cSelectedTextInfo, LKeyTextAuthor);
    vc->AddView(cSelectedTextInfo, LKeyTextTitle);
    vc->AddView(cSelectedTextInfo, LCurrentTextNumber);
    vc->AddView(cSelectedTextInfo, LCurrentTextAuthor);
    vc->AddView(cSelectedTextInfo, LCurrentTextTitle);
    vc->AddView(cSelectedTextInfo, MSelectedTextPreview);
    vc->AddView(cSelectedTextInfo, LTotalTextsLoaded);
    vc->AddView(cSelectedTextInfo, LTotalTextsActivated);
    vc->AddView(cSelectedTextInfo, LKeyTextDefined);
    vc->AddView(cSelectedTextInfo, LKeyTextNotDefined);

    vc->AddViewsGroup(cAllViews);
    vc->AddView(cAllViews, LKeyTextNumber);
    vc->AddView(cAllViews, LKeyTextAuthor);
    vc->AddView(cAllViews, LKeyTextTitle);
    vc->AddView(cAllViews, LCurrentTextNumber);
    vc->AddView(cAllViews, LCurrentTextAuthor);
    vc->AddView(cAllViews, LCurrentTextTitle);
    vc->AddView(cAllViews, MSelectedTextPreview);
    vc->AddView(cAllViews, LTotalTextsLoaded);
    vc->AddView(cAllViews, LTotalTextsActivated);
    vc->AddView(cAllViews, LKeyTextDefined);
    vc->AddView(cAllViews, LKeyTextNotDefined);
    vc->AddView(cAllViews, CLBTextsListBox);
    vc->AddView(cAllViews, CLBTextsListBox);
    vc->AddView(cAllViews, MSelectedTextPreview);

}
//---------------------------------------------------------------------------


void __fastcall TAuthoringAnalyserTable::BtnLoadPrototypeClick(
      TObject *Sender)
{
	if (ODOpenText->Execute())
    {
    	if (ODOpenText->FileName != "")
        {
        fAuthorAndTitle->Init(im_Prototype, "", "");
            if (fAuthorAndTitle->ShowModal() == mrOk)
            {
        		VCLFasade.LoadAsPrototypeText(ODOpenText->FileName, fAuthorAndTitle->Author(), fAuthorAndTitle->Title());
            }
        }
    };
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnLoadKeyTextClick(
      TObject *Sender)
{
	if (ODOpenText->Execute())
    {
    	if (ODOpenText->FileName != "")
        {
        fAuthorAndTitle->Init(im_KeyText, "", "");
            if (fAuthorAndTitle->ShowModal() == mrOk)
            {
        		VCLFasade.LoadAsKeyText(ODOpenText->FileName, fAuthorAndTitle->Author(), fAuthorAndTitle->Title());
            }
        }
    };
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnDeletePrototypesClick(
      TObject *Sender)
{
     VCLFasade.DeleteAllTexts();
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnDeleteAllClick(TObject *Sender)
{
	 VCLFasade.DeleteAllTexts();
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::CLBTextsListBoxClick(
      TObject *Sender)
{
	 VCLFasade.SelectText(CLBTextsListBox->ItemIndex, CLBTextsListBox->Checked[CLBTextsListBox->ItemIndex]);
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::ChkSelectAllClick(TObject *Sender)
{
     VCLFasade.SetActivatedAll(ChkSelectAll->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::ChkShowPreviewClick(
      TObject *Sender)
{
     VCLFasade.ShowPreview(ChkShowPreview->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnCurrentTextAuthorAndTitleClick(
      TObject *Sender)
{
if (!VCLFasade.TotalTextsLoaded()) return;
    fAuthorAndTitle->Init(im_Editing, AnalyserFasade.PTextsController()->CurrentAuthor(), AnalyserFasade.PTextsController()->CurrentTitle());
	if (fAuthorAndTitle->ShowModal() == mrOk)
    {
    	VCLFasade.SetCurrentTextAuthorAndTitle(fAuthorAndTitle->Author(), fAuthorAndTitle->Title());
    }
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnMakeCurrentTextKeyTextClick(
      TObject *Sender)
{
	VCLFasade.SetCurrentTextAsKeyText();
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnDeleteCurrentTextClick(
      TObject *Sender)
{
   	 VCLFasade.DeleteCurrentText();
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnCurrentTextResoundingMapClick(
      TObject *Sender)
{
/*Забил на модель MVC. Надо было срочно доделывать.*/
if (!VCLFasade.TotalTextsLoaded()) return;

	ResoundingRulesSelector->Init();
    	if (ResoundingRulesSelector->ShowModal() == mrOk)
        {
        	VCLFasade.SetResoundingMapRules(ResoundingRulesSelector->GetRules());
            VCLFasade.SetPrototypeTextToResoundingAnalysis();

		    AnalysisProcess->Init(&AnalyserFasade, cResoundingAnalysisName);

			if (AnalysisProcess->ShowModal() == mrOk)
    		{
		    	ResoundingMapTable->Init(
        		AnalyserFasade.PResoundingMapAnalyser()->PTextDataProvider(),
            	AnalyserFasade.PResoundingMapAnalyser()->PResoundingCover()->MergedCover(),
	            AnalyserFasade.PResoundingMapAnalyser()->PResoundingCover(),
    	        ResoundingRulesSelector->GetRules());
		    }
        }
}
//---------------------------------------------------------------------------


void __fastcall TAuthoringAnalyserTable::BtnKeyTextAuthorAndTitleClick(
      TObject *Sender)
{
if (!VCLFasade.KeyTextDefined()) return;
    fAuthorAndTitle->Init(im_Editing, AnalyserFasade.PTextsController()->KeyTextAuthor(), AnalyserFasade.PTextsController()->KeyTextTitle());
	if (fAuthorAndTitle->ShowModal() == mrOk)
    {
    	VCLFasade.SetKeyTextAuthorAndTitle(fAuthorAndTitle->Author(), fAuthorAndTitle->Title());
    }
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnMakeKeyTextPrototypeTextClick(
      TObject *Sender)
{
     VCLFasade.SetKeyTextAsPrototypeText();
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnDeleteKeyTextClick(
      TObject *Sender)
{
     VCLFasade.DeleteKeyText();
}
//---------------------------------------------------------------------------

void __fastcall TAuthoringAnalyserTable::BtnKeyTextResoundingMapClick(
      TObject *Sender)
{
/*Забил на модель MVC. Надо было срочно доделывать.*/
if (!VCLFasade.KeyTextDefined()) return;

	ResoundingRulesSelector->Init();
    	if (ResoundingRulesSelector->ShowModal() == mrOk)
        {
        	VCLFasade.SetResoundingMapRules(ResoundingRulesSelector->GetRules());
            VCLFasade.SetKeyTextToResoundingAnalysis();


		    AnalysisProcess->Init(&AnalyserFasade, cResoundingAnalysisName);

   			if (AnalysisProcess->ShowModal() == mrOk)
		    {
    		ResoundingMapTable->Init(
        		AnalyserFasade.PResoundingMapAnalyser()->PTextDataProvider(),
	            AnalyserFasade.PResoundingMapAnalyser()->PResoundingCover()->MergedCover(),
    	        AnalyserFasade.PResoundingMapAnalyser()->PResoundingCover(),
        	    ResoundingRulesSelector->GetRules());
		    }
        }
}
//---------------------------------------------------------------------------


void TAuthoringAnalyserTable::SetCurrentTextInfo(const TSInt & tIndex, const TTextString & tAuthor, const TTextString & tTitle)
{
    if (tIndex != -1) LCurrentTextNumber->Caption = IntToStr(tIndex);
    else              LCurrentTextNumber->Caption = "";
    LCurrentTextAuthor->Caption = tAuthor;
    LCurrentTextTitle->Caption  = tTitle;
};

void TAuthoringAnalyserTable::SetKeyTextInfo(const TSInt & tIndex, const TTextString & tAuthor, const TTextString & tTitle)
{
    if (tIndex != -1) LKeyTextNumber->Caption = IntToStr(tIndex);
    else              LKeyTextNumber->Caption = "";
    LKeyTextAuthor->Caption = tAuthor;
    LKeyTextTitle->Caption  = tTitle;
};

void TAuthoringAnalyserTable::SetKeyTextDefined(const TBool & tDefined)
{
	LKeyTextDefined->Visible  = tDefined;
	LKeyTextNotDefined->Visible = !tDefined;
};

    void TAuthoringAnalyserTable::SetTotalTextsLoaded(const TUInt & tCount)
    {
        LTotalTextsLoaded->Caption = IntToStr(tCount);
    };

    void TAuthoringAnalyserTable::SetTotalTextsActivated(const TUInt & tCount)
    {
        LTotalTextsActivated->Caption = IntToStr(tCount);
    };


void TAuthoringAnalyserTable::SetTextPreview(const TTextString & tText)
{
	MSelectedTextPreview->Text = tText;
};


void __fastcall TAuthoringAnalyserTable::N3Click(TObject *Sender)
{
	Application->Terminate();	
}
//---------------------------------------------------------------------------


void __fastcall TAuthoringAnalyserTable::BtnDoAnalysisClick(TObject *Sender)
{
if (!AnalyserFasade.PAuthoringAnalyser()->IsReady()) return;
    AnalysisProcess->Init(&AnalyserFasade, cAuthoringAnalysisName);

    if (AnalysisProcess->ShowModal() == mrOk)
    {
		AuthoringAnalysisResults->Init(
            AnalyserFasade.PAuthoringAnalyser()->GetParagraphsResult(),
            AnalyserFasade.PAuthoringAnalyser()->GetSentencesResult(),
            AnalyserFasade.PAuthoringAnalyser()->GetWordsResult() );
        AuthoringAnalysisResults->ShowModal();
    }
}
//---------------------------------------------------------------------------



void __fastcall TAuthoringAnalyserTable::N5Click(TObject *Sender)
{
	About->ShowModal();
}
//---------------------------------------------------------------------------

