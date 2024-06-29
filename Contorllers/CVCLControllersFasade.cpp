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
#pragma hdrstop
#include "CVCLControllersFasade.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "CVCLFileDataLoader.h"
#include "VCLConstants.h"
#include "UConstants.h"
#include "CTextsListFormatter.h"

void TVCLControllersFasade::_UpdateTextsList()
{
    TCheckListBox * listBox = _AuthoringAnalyserForm->TextsCheckListBox();

    TTextsListFormatter  formatter(_AnalyserFasade->PTextsController()->PLogicalTextContainer());
    TTextsInfoStrings    formattedList =  formatter.FullTitlesInfoStrings(cTitleFormat, cDotted);
    TTextsConfigurator * txtConfig     = _AnalyserFasade->PTextsController()->PTextsConfigurator();

    listBox->Items->Clear();

TTextString alias;
    for (TUInt i=0; i<formattedList.Count(); i++)
    {
    alias = formattedList[i].Alias();
         listBox->Items->Add(formattedList[i].Format());
         if (txtConfig->IsActivated(alias))
	         listBox->Checked[i] = true;
    };

    listBox->ItemIndex = _AnalyserFasade->PTextsController()->CurrentIndex();
};

void TVCLControllersFasade::_UpdateCurrentTextInfo()
{
	_AuthoringAnalyserForm->SetCurrentTextInfo(_AnalyserFasade->PTextsController()->CurrentIndex(),
    						  _AnalyserFasade->PTextsController()->CurrentAuthor(),
                              _AnalyserFasade->PTextsController()->CurrentTitle());
};

void TVCLControllersFasade::_UpdateKeyTextInfo()
{
	_AuthoringAnalyserForm->SetKeyTextInfo(_AnalyserFasade->PTextsController()->KeyTextIndex(),
    					  _AnalyserFasade->PTextsController()->KeyTextAuthor(),
                          _AnalyserFasade->PTextsController()->KeyTextTitle());
};

void TVCLControllersFasade::_UpdateCommonTextsInfo()
{
    _AuthoringAnalyserForm->SetKeyTextDefined     (_AnalyserFasade->KeyTextDefined());
    _AuthoringAnalyserForm->SetTotalTextsLoaded   (_AnalyserFasade->TotalTextsLoaded());
    _AuthoringAnalyserForm->SetTotalTextsActivated(_AnalyserFasade->TotalTextsActivated());
};

void TVCLControllersFasade::_UpdateSelectedTextPreview()
{
	if (_ShowPreview && _AnalyserFasade->TotalTextsLoaded())
    					_AuthoringAnalyserForm->SetTextPreview(_AnalyserFasade->PTextsController()->CurrentText());
    else
    					_AuthoringAnalyserForm->SetTextPreview("");
};

void TVCLControllersFasade::_UpdateAll()
{
	_UpdateTextsList();
    _UpdateCurrentTextInfo();
    _UpdateKeyTextInfo();
    _UpdateCommonTextsInfo();
    _UpdateSelectedTextPreview();
    _ViewsContainer->UpdateGroup(cAllViews);
};

void TVCLControllersFasade::SetAnalyserControllersFasade(TAnalyserControllersFasade * tFasade)
{
    _AnalyserFasade = tFasade;
};

void TVCLControllersFasade::SetViewsContainer(TVCLViewsContainer	*	tViewsContainer)
{
    _ViewsContainer = tViewsContainer;
};

void TVCLControllersFasade::SetAuthoringAnalyserTable(TAuthoringAnalyserTable  *  tAuthoringAnalyserTable)
{
    _AuthoringAnalyserForm = tAuthoringAnalyserTable;
};

void TVCLControllersFasade::LoadAsPrototypeText(const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle)
{
TVCLFileDataLoader ldr;
    _AnalyserFasade->LoadAsPrototype(tFileName, tAuthor, tTitle, &ldr);
    _UpdateAll();
};

void TVCLControllersFasade::LoadAsKeyText(const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle)
{
TVCLFileDataLoader ldr;
    _AnalyserFasade->LoadAsKeyText(tFileName, tAuthor, tTitle, &ldr);
    _UpdateAll();
};

void TVCLControllersFasade::SelectText(const TUInt & tItemIndex, const TBool & tChecked)
{
    _AnalyserFasade->SelectText(tItemIndex, tChecked);
    _UpdateAll();
};

void TVCLControllersFasade::SetCurrentTextAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle)
{
    _AnalyserFasade->SetCurrentTextAuthorAndTitle(tAuthor, tTitle);
    _UpdateAll();
};

void TVCLControllersFasade::SetKeyTextAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle)
{
    _AnalyserFasade->SetKeyTextAuthorAndTitle(tAuthor, tTitle);
    _UpdateAll();
};

TUInt TVCLControllersFasade::TotalTextsLoaded() const
{
    return _AnalyserFasade->TotalTextsLoaded();
};

TBool TVCLControllersFasade::KeyTextDefined() const
{
    return _AnalyserFasade->KeyTextDefined();
}

void TVCLControllersFasade::SetCurrentTextAsKeyText()
{
    _AnalyserFasade->SetCurrentTextAsKeyText();
    _UpdateAll();
};

void TVCLControllersFasade::SetKeyTextAsPrototypeText()
{
    _AnalyserFasade->SetKeyTextAsPrototypeText();
    _UpdateAll();
};

void TVCLControllersFasade::ShowPreview(const TBool & tShowPreview)
{
	_ShowPreview = tShowPreview;
    _UpdateAll();
};

void TVCLControllersFasade::SetActivatedAll(const TBool & tActivated)
{
    _AnalyserFasade->SetActivatedAll(tActivated);
    _UpdateAll();
};

void TVCLControllersFasade::DeleteCurrentText()
{
    _AnalyserFasade->DeleteCurrentText();
    _UpdateAll();
};

void TVCLControllersFasade::DeleteKeyText()
{
    _AnalyserFasade->DeleteKeyText();
    _UpdateAll();
};


void TVCLControllersFasade::DeleteAllTexts()
{
    _AnalyserFasade->DeleteAllTexts();
    _UpdateAll();
};

void TVCLControllersFasade::SetResoundingMapRules(const TRulesProxy & tProxy)
{
	_AnalyserFasade->LoadResoundingAnalysisRules(tProxy);
};

void TVCLControllersFasade::SetPrototypeTextToResoundingAnalysis()
{
    _AnalyserFasade->SetPrototypeTextToResoundingAnalysis();
};

void TVCLControllersFasade::SetKeyTextToResoundingAnalysis()
{
    _AnalyserFasade->SetKeyTextToResoundingAnalysis();
};

void TVCLControllersFasade::DoAuthoringAnalysis()
{
    _AnalyserFasade->DoAnalysis(cAuthoringAnalysisName);
};

void TVCLControllersFasade::DoResoundingAnalysis()
{
    _AnalyserFasade->DoAnalysis(cResoundingAnalysisName);
};
