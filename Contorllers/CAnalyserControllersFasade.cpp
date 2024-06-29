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
#include "CAnalyserControllersFasade.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include "UConstants.h"

TTextsController * TAnalyserControllersFasade::PTextsController()
{
	return &_TextsController;
}

void TAnalyserControllersFasade::SetTextsController(TTextsController * tTextsController)
{
	_TextsController = *tTextsController;
}

TAuthoringAnalyser * TAnalyserControllersFasade::PAuthoringAnalyser()
{
    return &_AuthoringAnalyser;
};

TResoundingMapAnalyser * TAnalyserControllersFasade::PResoundingMapAnalyser()
{
    return &_ResoundingAnalyser;
};

void TAnalyserControllersFasade::LoadAsPrototype(const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle, TRawDataLoader * tLoader)
{
TTextString alias;
    _TextsController.LoadText(tFileName, tLoader, &alias);
    _TextsController.SetAuthorAndTitle(alias, tAuthor, tTitle);
};

void TAnalyserControllersFasade::LoadAsKeyText  (const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle, TRawDataLoader * tLoader)
{
TTextString alias;
    _TextsController.LoadText(tFileName, tLoader, &alias);
    _TextsController.SetAuthorAndTitle(alias, tAuthor, tTitle);
    _TextsController.SetPrototypeTextAsKeyText(alias);
};

void TAnalyserControllersFasade::DeleteCurrentText()
{
    _TextsController.DeleteCurrentText();
}

void TAnalyserControllersFasade::DeleteKeyText()
{
    _TextsController.DeleteKeyText();
};

void TAnalyserControllersFasade::DeleteAllTexts()
{
    _TextsController.DeleteAllTexts();
};

void TAnalyserControllersFasade::SelectText(const TUInt & tItemIndex, const TBool & tChecked)
{
    _TextsController.SetCurrent(tItemIndex);
    _TextsController.SetActivated(tItemIndex, tChecked);
};

void TAnalyserControllersFasade::SetActivatedAll(const TBool & tActivated)
{
    _TextsController.SetActivatedAll(tActivated);
};

void TAnalyserControllersFasade::SetCurrentTextAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle)
{
    _TextsController.SetAuthorAndTitle(_TextsController.CurrentAlias(), tAuthor, tTitle);
};

void TAnalyserControllersFasade::SetKeyTextAuthorAndTitle    (const TTextString & tAuthor, const TTextString & tTitle)
{
    _TextsController.SetAuthorAndTitle(_TextsController.KeyTextAlias(), tAuthor, tTitle);
};

TUInt TAnalyserControllersFasade::TotalTextsLoaded() const
{
    return  _TextsController.TextsCount();
};

TBool TAnalyserControllersFasade::KeyTextDefined() const
{
    return  _TextsController.KeyTextDefined();
};

TUInt TAnalyserControllersFasade::TotalTextsActivated() 
{
    return  _TextsController.ActivatedTextsCount();
};

void TAnalyserControllersFasade::SetCurrentTextAsKeyText()
{
    _TextsController.SetPrototypeTextAsKeyText(_TextsController.CurrentAlias());
};

void TAnalyserControllersFasade::SetKeyTextAsPrototypeText()
{
    _TextsController.SetKeyTextAsPrototypeText();
};

void TAnalyserControllersFasade::SetAuthoringAnalysisReporter(TAnalysisReporter * tReporter)
{
    _AuthoringAnalyser.SetReporter(tReporter);
};

void TAnalyserControllersFasade::SetResoundingAnalysisReporter(TAnalysisReporter * tReporter)
{
    _ResoundingAnalyser.SetReporter(tReporter);
};


void TAnalyserControllersFasade::LoadResoundingAnalysisRules(const TRulesProxy & tRules)
{
    _ResoundingAnalyser.LoadRules(tRules);
};

void TAnalyserControllersFasade::SetPrototypeTextToResoundingAnalysis()
{
    _ResoundingAnalyser.LoadText(_TextsController.CurrentTextDataProvider());
};

void TAnalyserControllersFasade::SetKeyTextToResoundingAnalysis()
{
    _ResoundingAnalyser.LoadText(_TextsController.KeyTextDataProvider());
};


void TAnalyserControllersFasade::DoAnalysis(const TTextString & tName)
{
	if (_AuthoringAnalyser.Name() == tName)			_AuthoringAnalyser.DoAnalysis();
    else
    	if (_ResoundingAnalyser.Name() == tName)	_ResoundingAnalyser.DoAnalysis();
};


TAnalyserControllersFasade::TAnalyserControllersFasade()
	:	_AuthoringAnalyser(cAuthoringAnalysisName), _ResoundingAnalyser(cResoundingAnalysisName)
{
	_AuthoringAnalyser.SetTextsConfigurator(_TextsController.PTextsConfigurator());
    _AuthoringAnalyser.SetReporter(NULL);
    _ResoundingAnalyser.SetReporter(NULL);
};
