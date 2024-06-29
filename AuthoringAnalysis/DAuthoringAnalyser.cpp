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
#include "DAuthoringAnalyser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



#include "CTextStringWrapper.h"
#include "CRangeItem.h"

#include "CFiniteStateMachineManager.h"
#include "FiniteStateMachine.h"

#include "DCharFrequencyCalculator.h"

#include "UAuthoringAnalysisConstants.h"

THamNSConnector<TSInt>::TVector TAuthoringAnalyser::_ComposeNSImageVector(const TUInt & tTreeLevel, const TTextString & tAlias)
{
	TSpecifiedFrequencyTable::FrequencyTableType frequencyTable = _FrequencyContainers[tTreeLevel][tAlias].FrequencyTable();
    TSpecifiedFrequencyTable::FrequencyTableType::TFrequencyVector frequencyVector = frequencyTable.FrequencyVector();

    THamNSConnector<TSInt>::TVector nsVector;

    for (TUInt i=0; i<frequencyVector.size(); i++)
    	nsVector.push_back(frequencyVector[i].Count);
return nsVector;
};

TTextString TAuthoringAnalyser::_ComposeText(const TUInt & tTreeLevel, const TTextString & tAlias)
{
    TTextString text = _AnalysedTextsConfigurator[tAlias].PLogicalTextItem()->Text();
    TRangeMapsEqualifer::TRangeItems items = _LeveledEqualifiedMaps[tTreeLevel][tAlias].Items();

    TTextString s = "";

       	for (TUInt i=0; i<items.size(); i++)
        	s += text.SubString(items[i].From(), items[i].Length());
return s;
};

void TAuthoringAnalyser::_MakeParSentWordTree(TLogicalTextItem * tItem)
{
//_ReportAboutAction(cTreeMakingStage, cTreeMakingMessage);
_ReportAboutActionBegin(cTreeMakingStage, tItem->Title() + ": " + cTreeMakingMessage);

TTextStringWrapper wrapper(tItem->Text());

	ParSentWordFSM::TCFCustomUnitDivisionTreeItem  tree(0, TRangeItem(1, wrapper.Text().Length()));
    ParSentWordFSM::TParSenWordDescriptor          descriptor = ParSentWordFSM::Descriptor(&tree);

#define TState ParSentWordFSM::TState
#define TEvent ParSentWordFSM::TEvent
#define TFSMachine FSM::SFiniteStateMachine<TState, TEvent, FSM::SOnEnterFunctor<TState, TEvent>, FSM::SIgnoreStrategy<TEvent> >
#define TFSMM      TFiniteStateMachineManager<TEvent, TFSMachine, ParSentWordFSM::TParSenWordDescriptor, TTextStringWrapper>

	TFSMM fsmManager(descriptor, wrapper);

    if (_Reporter)	fsmManager.Process(_Reporter->ProgressFunc());
    else            fsmManager.Process();

#undef  TState
#undef  TEvent
#undef  TFSMachine
#undef  TFSMM

_Trees.insert(TTextsParSentWordTrees::value_type(tItem->Alias(), tree));
_ReportAboutActionEnd(cTreeMakingStage, cDoneMessage);
};

void TAuthoringAnalyser::_CreateEqualifiedMaps(const TUInt & tTreeLevel)
{
//_ReportAboutAction(cPrepareSamplesStage, cPrepareSamplesMessage);
_ReportAboutActionBegin(cPrepareSamplesStage, "Уровень " + CLeveledMessage(tTreeLevel) + ": " + cPrepareSamplesMessage);

TRangeMapsEqualifer rangeMapsEqualifier;

	TTextsParSentWordTrees::iterator iter = _Trees.begin();

    while (iter != _Trees.end())
    {
    _ReportShowMessage("Текст: " + _AnalysedTextsConfigurator[(*iter).first].PLogicalTextItem()->Title() + "...");

		TCFTreeLevel<TSFloat, TRangeItem>  Levels(&(*iter).second);

        rangeMapsEqualifier.AddMap((*iter).first, Levels[tTreeLevel].PUnits());
    iter++;
    };

    rangeMapsEqualifier.Equalify();
    _LeveledEqualifiedMaps.insert(TLeveledEqualifiedMaps::value_type(tTreeLevel, rangeMapsEqualifier.EqualifiedMapsContainer()));

_ReportAboutActionEnd(cPrepareSamplesStage, cDoneMessage);
}

void TAuthoringAnalyser::_CalculateFrequencies(const TUInt & tTreeLevel)
{
//_ReportAboutAction(cCalculateFrequenciesStage, cCalculateFrequenciesMessage);
_ReportAboutActionBegin(cCalculateFrequenciesStage, "Уровень " + CLeveledMessage(tTreeLevel) + ": " + cCalculateFrequenciesMessage);

TCharFrequencyCalculator  calculator;
TFrequencyTablesContainer frequencyContainer;

	TTextsConfigurator::TTextConfigurations::iterator iter = _AnalysedTextsConfigurator.Begin();

    TTextString text;
    TTextString alias;

    while (iter != _AnalysedTextsConfigurator.End())
    {
    alias = (*iter).first;
    _ReportShowMessage("Текст: " + _AnalysedTextsConfigurator[alias].PLogicalTextItem()->Title() + "...");
		text = _ComposeText(tTreeLevel, alias);

        frequencyContainer.AddItem(TSpecifiedFrequencyTable(alias, calculator(text)));
    iter++;
    }

_FrequencyContainers.insert(TLeveledFrequencyContainers::value_type(tTreeLevel, frequencyContainer));
_ReportAboutActionEnd(cCalculateFrequenciesStage, cDoneMessage);
};

void TAuthoringAnalyser::_NeuroSystemPreparing(const TUInt & tTreeLevel)
{
//_ReportAboutAction(cHamNSPreparingStage, cHamNSPreparingMessage);
_ReportAboutActionBegin(cHamNSPreparingStage, "Уровень " + CLeveledMessage(tTreeLevel) + ": " + cHamNSPreparingMessage);

/*==============================================================================
	<Небезопасный код>
==============================================================================*/

    TTextsConfigurator::TTextConfigurations::iterator iter = _AnalysedTextsConfigurator.Begin();
    TTextString keyTextAlias = _AnalysedTextsConfigurator.KeyTextAlias();
    TTextString alias;
    TUInt 		nsIndex;

    _HamNSConnector.HamNS.ClearAll();
    _HamNSConnector.NSLoadEntryVector( _ComposeNSImageVector(tTreeLevel, keyTextAlias) );

TIndexToAliasAssociator associator;

    while (iter != _AnalysedTextsConfigurator.End())
    {
    alias = (*iter).first;

    _ReportShowMessage("Текст: " + _AnalysedTextsConfigurator[alias].PLogicalTextItem()->Title() + "...");

        if (alias != keyTextAlias)
        {
        	nsIndex = _HamNSConnector.NSLoadSampleImage( _ComposeNSImageVector(tTreeLevel, alias) );
            associator.insert(TIndexToAliasAssociator::value_type( nsIndex, alias ));
        };
    iter++;
    };

_IndexToAliasAssociators.insert(TLeveledIndexToAliasAssociators::value_type( tTreeLevel, associator ));
/*==============================================================================
	</Небезопасный код>
==============================================================================*/

_ReportAboutActionEnd(cHamNSPreparingStage, cDoneMessage);
};

void TAuthoringAnalyser::_NeuroSystemComparing(const TUInt & tTreeLevel)
{
//_ReportAboutAction(cHamNSComparingStage, cHamNSComparingMessage);
_ReportAboutActionBegin(cHamNSComparingStage, "Уровень " + CLeveledMessage(tTreeLevel) + ": " + cHamNSComparingMessage);
/*==============================================================================
	<Небезопасный код>
==============================================================================*/
	_HamNSConnector.NSDoAllSteps(cNeuroSystemMaxIterations);

    TResultVector resIndexes;
    _HamNSConnector.NSResult(&resIndexes);

    _ResultVectors.insert(TLeveledResultVectors::value_type(tTreeLevel, resIndexes));
/*==============================================================================
	</Небезопасный код>
==============================================================================*/
_ReportAboutActionEnd(cHamNSComparingStage, cDoneMessage);
};

void TAuthoringAnalyser::_NeuroSystemProcessing(const TUInt & tTreeLevel)
{
_ReportAboutAction(cHamNSProcessingStage, cHamNSProcessingMessage);

	_NeuroSystemPreparing(tTreeLevel);
	_NeuroSystemComparing(tTreeLevel);
};

void TAuthoringAnalyser::_ResultsPrinting(const TUInt & tTreeLevel)
{
    _ReportShowMessage(cResultsMessageLevelBody + CLeveledMessage(tTreeLevel));

//<Небезопасный код>
TResultVector resIndexes = _ResultVectors[tTreeLevel];

TTextString alias;
TUInt       nsIndex;
TTextString author;
TTextString title;

TIndexToAliasAssociator associator = _IndexToAliasAssociators[tTreeLevel];

	if (!resIndexes.size())
         _ReportShowMessage(cAnalysisFailure);
	else
	    for (TUInt i=0; i<resIndexes.size(); i++)
        {
        nsIndex = resIndexes[i];
        alias   = associator[nsIndex];
        author  = _AnalysedTextsConfigurator[alias].PLogicalTextItem()->Author();
        title   = _AnalysedTextsConfigurator[alias].PLogicalTextItem()->Title();

            _ReportShowMessage( " "" " + title + " "". " + author );
        }
//</Небезопасный код>
};



void TAuthoringAnalyser::_SelectAnalysedTexts()
{
_ReportAboutAction(cPreparingTextsStage, cPreparingTextsMessage);

	_AnalysedTextsConfigurator = (*_AllTextsConfigurator);
	_AnalysedTextsConfigurator.SetConfigurations(_AllTextsConfigurator->Configurations());
	_AnalysedTextsConfigurator.RemoveNotActivated();
};

void TAuthoringAnalyser::_MakeParSentWordTrees()
{
_ReportAboutAction(cTreeMakingStage, cTreeMakingMessage);

    TTextsConfigurator::TTextConfigurations::iterator iter = _AnalysedTextsConfigurator.Begin();
    TTextString alias;

    while (iter != _AnalysedTextsConfigurator.End())
    {
        alias = (*iter).first;

        _MakeParSentWordTree((*iter).second.PLogicalTextItem());
    iter++;
    };
};

void TAuthoringAnalyser::_PrepareSamples()
{
_ReportAboutAction(cPrepareSamplesStage, cPrepareSamplesMessage);

	_CreateEqualifiedMaps(cParagraphsLevel);
    _CreateEqualifiedMaps(cSentencesLevel);
    _CreateEqualifiedMaps(cWordsLevel);
};

void TAuthoringAnalyser::_CalculateFrequencies()
{
_ReportAboutAction(cCalculateFrequenciesStage, cCalculateFrequenciesMessage);
	_CalculateFrequencies(cParagraphsLevel);
	_CalculateFrequencies(cSentencesLevel);
	_CalculateFrequencies(cWordsLevel);
};

void TAuthoringAnalyser::_NeuroSystemProcessing()
{
_ReportAboutAction(cHamNSProcessingStage, cHamNSProcessingMessage);
	_NeuroSystemProcessing(cParagraphsLevel);
	_NeuroSystemProcessing(cSentencesLevel);
	_NeuroSystemProcessing(cWordsLevel);
};

void TAuthoringAnalyser::_ResultsPrinting()
{
	_ReportShowMessage(cResultsMessageBorder);
	_ReportShowMessage(cResultsMessageTitle);

    _ResultsPrinting(cParagraphsLevel);
    _ResultsPrinting(cSentencesLevel);
    _ResultsPrinting(cWordsLevel);
};

void TAuthoringAnalyser::_ReportShowMessage(const TTextString & tMessage)
{
    TAnalyser::_ReportShowMessage(tMessage);
};

void TAuthoringAnalyser::_ReportAboutAnalysisBegin(const TTextString & tMessage)
{
    TAnalyser::_ReportAboutAnalysisBegin(tMessage);
};

void TAuthoringAnalyser::_ReportAboutAnalysisEnd(const TTextString & tMessage)
{
    TAnalyser::_ReportAboutAnalysisEnd(tMessage);
};

void TAuthoringAnalyser::_ReportAboutActionBegin(const TTextString & tStage, const TTextString & tMessage)
{
    TAnalyser::_ReportAboutActionBegin(tStage, tMessage);
};

void TAuthoringAnalyser::_ReportAboutActionEnd(const TTextString & tStage, const TTextString & tMessage)
{
    TAnalyser::_ReportAboutActionEnd(tStage, tMessage);
};

void TAuthoringAnalyser::_ReportAboutAction(const TTextString & tStage, const TTextString & tMessage)
{
	TAnalyser::_ReportAboutAction(tStage, tMessage);
};

void TAuthoringAnalyser::_ReportAboutProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
    TAnalyser::_ReportAboutProgress(tStage, tBegin, tEnd, tProgress);
};

void TAuthoringAnalyser::_Clear()
{
	_AnalysedTextsConfigurator.Clear();
    _Trees.clear();
    _LeveledEqualifiedMaps.clear();
    _FrequencyContainers.clear();
    _IndexToAliasAssociators.clear();
    _ResultVectors.clear();
//   <Небезопасный код>
    _HamNSConnector.HamNS.ClearAll();
//   </Небезопасный код>
};

TTextString TAuthoringAnalyser::_Result(const TUInt & tTreeLevel)
{
//	<Небезопасный код>
TResultVector resIndexes = _ResultVectors[tTreeLevel];

TTextString alias;
TUInt       nsIndex;
TTextString author;
TTextString title;

TTextString result = "";

TIndexToAliasAssociator associator = _IndexToAliasAssociators[tTreeLevel];

	if (!resIndexes.size()) return "";
	else
	    for (TUInt i=0; i<resIndexes.size(); i++)
        {
        nsIndex = resIndexes[i];
        alias   = associator[nsIndex];
        author  = _AnalysedTextsConfigurator[alias].PLogicalTextItem()->Author();
        title   = _AnalysedTextsConfigurator[alias].PLogicalTextItem()->Title();

            result = result + " "" " + title + " "". " + author;
        }
return result;
//	</Небезопасный код>
}

TBool TAuthoringAnalyser::IsReady()
{
	return (_AllTextsConfigurator && _AllTextsConfigurator->KeyTextDefined() && _AllTextsConfigurator->Count() > 1);
};

void TAuthoringAnalyser::SetTextsConfigurator(TTextsConfigurator * tTextsConfigurator)
{
    _AllTextsConfigurator = tTextsConfigurator;
};

void TAuthoringAnalyser::SetReporter(TAnalysisReporter * tReporter)
{
	TAnalyser::SetReporter(tReporter);
};


void TAuthoringAnalyser::DoAnalysis()
{
if (!_AllTextsConfigurator) return;
_Clear();
_ReportAboutAnalysisBegin("Анализ авторства начат.");

    _SelectAnalysedTexts();
    _MakeParSentWordTrees();
    _PrepareSamples();
    _CalculateFrequencies();
    _NeuroSystemProcessing();

_ReportAboutAnalysisBegin("Анализ авторства завершен.");

	_ResultsPrinting();
};

TTextString TAuthoringAnalyser::Name() const
{
	return TAnalyser::Name();
};

TTextString TAuthoringAnalyser::GetParagraphsResult()
{
	return _Result(cParagraphsLevel);
};

TTextString TAuthoringAnalyser::GetSentencesResult()
{
	return _Result(cSentencesLevel);
};

TTextString TAuthoringAnalyser::GetWordsResult()
{
	return _Result(cWordsLevel);
};
