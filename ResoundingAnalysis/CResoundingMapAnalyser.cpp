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
#include "CResoundingMapAnalyser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



#include "CTextStringWrapper.h"

#include "CBaseCoverProcessor.h"
#include "BRuleProcessor.h"

#include "UCharsValues.h"

#include "UResoundingAnalysisConstants.h"


void TResoundingMapAnalyser::_BaseCoverProcessing()
{
_ReportAboutAction(cBaseCoverProcessingStage, cBaseCoverProcessingMessage);
TTextStringWrapper wrapper(_TextDataProvider->Text());

TBaseCoverProcessor<TTextStringWrapper> baseCoverProcessor(wrapper, ns_CharsValues::DefaultCharValuesMap());

    if (_Reporter)	baseCoverProcessor.Process(_Reporter->ProgressFunc());
    else            baseCoverProcessor.Process();

    _ResoundingCover << baseCoverProcessor.BaseCover();
};

void TResoundingMapAnalyser::_RulesProcessing()
{
_ReportAboutAction(cRulesProcessingStage, cRulesProcessingMessage);
TTextStringWrapper wrapper(_TextDataProvider->Text());

TRuleProcessor<TTextStringWrapper> ruleProcessor(wrapper);

ruleProcessor << _Rules;

    if (_Reporter)	ruleProcessor.Process(_Reporter->ProgressFunc());
    else            ruleProcessor.Process();

    _ResoundingCover << ruleProcessor.ResoundingBatch();
};



void TResoundingMapAnalyser::_PrepareResoundingCover()
{
_ReportAboutAction(cPreparingResoundingCoverSatge, cPreparingResoundingCoverMessage);
	_ResoundingCover.Range(TRangeItem(_TextDataProvider->Begin(), _TextDataProvider->End()));
};

void TResoundingMapAnalyser::_CalculateMap()
{
_ReportAboutAction(cCalculatingMapStage, cCalculatingMapMessage);
	_BaseCoverProcessing();
    _RulesProcessing();
};

void TResoundingMapAnalyser::_MergeMap()
{
_ReportAboutAction(cMergingMapStage, cMergingMapMessage);
	_ResoundingCover.Merge();
};


void TResoundingMapAnalyser::_ReportShowMessage(const TTextString & tMessage)
{
    TAnalyser::_ReportShowMessage(tMessage);
};

void TResoundingMapAnalyser::_ReportAboutAnalysisBegin(const TTextString & tMessage)
{
    TAnalyser::_ReportAboutAnalysisBegin(tMessage);
};

void TResoundingMapAnalyser::_ReportAboutAnalysisEnd(const TTextString & tMessage)
{
    TAnalyser::_ReportAboutAnalysisEnd(tMessage);
};

void TResoundingMapAnalyser::_ReportAboutActionBegin(const TTextString & tStage, const TTextString & tMessage)
{
    TAnalyser::_ReportAboutActionBegin(tStage, tMessage);
};

void TResoundingMapAnalyser::_ReportAboutActionEnd(const TTextString & tStage, const TTextString & tMessage)
{
    TAnalyser::_ReportAboutActionEnd(tStage, tMessage);
};

void TResoundingMapAnalyser::_ReportAboutAction(const TTextString & tStage, const TTextString & tMessage)
{
	TAnalyser::_ReportAboutAction(tStage, tMessage);
};

void TResoundingMapAnalyser::_ReportAboutProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
    TAnalyser::_ReportAboutProgress(tStage, tBegin, tEnd, tProgress);
};

void TResoundingMapAnalyser::_Clear()
{
    _ResoundingCover.Clear();
};


TResoundingCover  * TResoundingMapAnalyser::PResoundingCover()
{
	return &_ResoundingCover;
};

TTextDataProvider * TResoundingMapAnalyser::PTextDataProvider()
{
    return _TextDataProvider;
};

void TResoundingMapAnalyser::LoadText(TTextDataProvider * tTextDataProvider)
{
	_Clear();
	_TextDataProvider = tTextDataProvider;
};

void TResoundingMapAnalyser::LoadRules(const TRulesProxy & tRules)
{
	_Clear();
	_Rules = tRules;
};

TTextString TResoundingMapAnalyser::Name() const
{
	return TAnalyser::Name();
};

void TResoundingMapAnalyser::SetReporter(TAnalysisReporter * tReporter)
{
	TAnalyser::SetReporter(tReporter);
};

void TResoundingMapAnalyser::DoAnalysis()
{
if (!_TextDataProvider || !_Rules.Count()) return;
_Clear();
_ReportAboutAnalysisBegin("Анализ благозвучия начат.");

	_PrepareResoundingCover();
    _CalculateMap();
    _MergeMap();
    
_ReportAboutAnalysisBegin("Анализ благозвучия завершен.");
};







