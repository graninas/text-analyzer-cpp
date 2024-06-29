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
#ifndef DAuthoringAnalyserH
#define DAuthoringAnalyserH
//---------------------------------------------------------------------------


#include "DTextsConfigurator.h"

#include "UParSentWordFSM.h"

#include "DAuthoringAnalysisReporter.h"

#include "DRangeMapsEqualifer.h"

#include "CHamNSConnector.h"

#include "DFrequencyTablesContainer.h"

#include "CLogicalTextsContainer.h"


#include "CAnalyser.h"

class TAuthoringAnalyser : public TAnalyser
{
public:

	class EInvalidTextsConfigurator{};

    typedef map<TTextString, ParSentWordFSM::TCFCustomUnitDivisionTreeItem, less<TTextString> > TTextsParSentWordTrees;
    typedef map<TUInt, TRangeMapsEqualifer::TEqualifiedMapsContainer, less<TUInt> > 			TLeveledEqualifiedMaps;
    typedef map<TUInt, TFrequencyTablesContainer, less<TUInt> > 								TLeveledFrequencyContainers;
    typedef map<TUInt, TTextString, less<TUInt> >												TIndexToAliasAssociator;
	typedef map<TUInt, TIndexToAliasAssociator, less<TUInt> >                                   TLeveledIndexToAliasAssociators;

//    	<Небезопасный код>
    typedef map<TUInt, TResultVector, less<TUInt> >  TLeveledResultVectors;
//		</Небезопасный код>

private:


    TTextsConfigurator         * _AllTextsConfigurator;

    TTextsConfigurator           _AnalysedTextsConfigurator;

    TTextsParSentWordTrees       _Trees;

    TLeveledEqualifiedMaps 	     _LeveledEqualifiedMaps;

    TLeveledFrequencyContainers  _FrequencyContainers;

    TLeveledIndexToAliasAssociators  _IndexToAliasAssociators;

//    	<Небезопасный код>
	TLeveledResultVectors	   	_ResultVectors;
  	THamNSConnector<TSInt> 		_HamNSConnector;

	THamNSConnector<TSInt>::TVector _ComposeNSImageVector(const TUInt & tTreeLevel, const TTextString & tAlias);
//		</Небезопасный код>

    TTextString _ComposeText(const TUInt & tTreeLevel, const TTextString & tAlias);

	void _MakeParSentWordTree(TLogicalTextItem * tItem);
    void _CreateEqualifiedMaps(const TUInt & tTreeLevel);
    void _CalculateFrequencies(const TUInt & tTreeLevel);
    void _NeuroSystemPreparing(const TUInt & tTreeLevel);
    void _NeuroSystemComparing(const TUInt & tTreeLevel);
    void _NeuroSystemProcessing(const TUInt & tTreeLevel);
    void _ResultsPrinting(const TUInt & tTreeLevel);

    void _SelectAnalysedTexts();
    void _MakeParSentWordTrees();
    void _PrepareSamples();
    void _CalculateFrequencies();
    void _NeuroSystemProcessing();
    void _ResultsPrinting();


    void _ReportShowMessage(const TTextString & tMessage);
    void _ReportAboutAnalysisBegin(const TTextString & tMessage);
    void _ReportAboutAnalysisEnd(const TTextString & tMessage);
    void _ReportAboutActionBegin(const TTextString & tStage, const TTextString & tMessage);
    void _ReportAboutActionEnd(const TTextString & tStage, const TTextString & tMessage);
    void _ReportAboutAction(const TTextString & tStage, const TTextString & tMessage);
    virtual void _ReportAboutProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress);

    void _Clear();

    TTextString _Result(const TUInt & tTreeLevel);

public:

	TBool IsReady();

    void SetTextsConfigurator(TTextsConfigurator * tTextsConfigurator);

    virtual TTextString Name() const;
	virtual void SetReporter(TAnalysisReporter * tReporter);
    virtual void DoAnalysis();

    TTextString GetParagraphsResult();
    TTextString GetSentencesResult();
    TTextString GetWordsResult();


	TAuthoringAnalyser(const TTextString & tName)
    : TAnalyser(tName), _AllTextsConfigurator(NULL){};

    ~TAuthoringAnalyser()
    {
		_Clear();
    }
};




#endif
 