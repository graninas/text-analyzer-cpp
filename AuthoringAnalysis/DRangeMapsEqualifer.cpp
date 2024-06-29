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
#include "DRangeMapsEqualifer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


TRangeMapsEqualifer::TRangeItems	TRangeMapsEqualifer::_ConvertToRangeItems(const TAdaptedRangeMap<>::TRangeAdapters & tAdapters)
{
TRangeItems items;

    for (TUInt i=0; i<tAdapters.size(); i++)
		items.push_back(tAdapters[i].Range());

return items;
};

void TRangeMapsEqualifer::_SortMaps()
{
	for (TUInt i=0; i<_BasePRangeMapsContainer.Count(); i++)
		_BasePRangeMapsContainer[i].Sort();
};

void TRangeMapsEqualifer::_EvaluateLengths(TLengthCountersContainer * tCountersContainer)
{
TLengthCounter counter;

	for (TUInt i=0; i<_BasePRangeMapsContainer.Count(); i++)
    {
    counter.Clear();
    counter.Alias(_BasePRangeMapsContainer[i].Specificator());

    	counter.EvaluateItems(_ConvertToRangeItems(_BasePRangeMapsContainer[i].Items()));
        tCountersContainer->AddItem(counter);
	};
};

void TRangeMapsEqualifer::_EvaluateCommonLengthCounts(TLengthCountersContainer * tCountersContainer, TLengthCounter * tTargetCounter)
{
if (!tCountersContainer->Count()) throw EInvalidCountersContainer();

TLengthCounter equalifiedCounter;
TUInt minCount;

	for (TUInt i=(*tCountersContainer)[0].MinLength(); i<=(*tCountersContainer)[0].MaxLength(); i++)
    {
	minCount = (*tCountersContainer)[0][i].Count();

		for (TUInt j=1; j<tCountersContainer->Count(); j++)
        	(*tCountersContainer)[j].MinCount(i, &minCount);

	equalifiedCounter.AddLengthCount(i, minCount);
    };

*tTargetCounter = equalifiedCounter;
};

void TRangeMapsEqualifer::_EqualifyMaps(TLengthCountersContainer * tCountersContainer, TLengthCounter * tTemplateCounter)
{
_ResultRangeMapsContainer.Clear();

	TLengthCounter::TLengthCounts::iterator iter;

    TUInt count;
    TUInt index;
    TUInt length;
    TTextString alias;

    TAdaptedRangeMap<>::TRangeAdapters adapters;

    TAdaptedRangeMap<TRangeItem> map;

    for (TUInt i=0; i<tCountersContainer->Count(); i++)
    {
    	alias = (*tCountersContainer)[i].Specificator();
        iter = tTemplateCounter->Begin();

        map.Clear();
        map.Alias(alias);

        while (iter != tTemplateCounter->End())
        {
        	length = (*iter).first;
            count  = (*iter).second.Count();

            index = (*tCountersContainer)[alias][length].AffectedRange().From();

            adapters = _BasePRangeMapsContainer[alias].Items(index, count);

            map.AddItems(_ConvertToRangeItems(adapters));
        iter++;
        }
    _ResultRangeMapsContainer.AddItem(map);
    };
};

void TRangeMapsEqualifer::Equalify()
{
    TLengthCountersContainer countersContainer;
    TLengthCounter 			 commonCounter;

    _SortMaps();
	_EvaluateLengths(&countersContainer);
    _EvaluateCommonLengthCounts(&countersContainer, &commonCounter);
    _EqualifyMaps(&countersContainer, &commonCounter);
};

TRangeMapsEqualifer::TRangeItems TRangeMapsEqualifer::operator[](const TTextString & tAlias)
{
	return _ResultRangeMapsContainer[tAlias].Items();
};

TRangeMapsEqualifer::TEqualifiedMapsContainer TRangeMapsEqualifer::EqualifiedMapsContainer()
{
    return _ResultRangeMapsContainer;
};

void TRangeMapsEqualifer::AddMap(const TTextString & tAlias, PRangeItems tItems)
{
TAdaptedRangeMap<>::TRangeAdapters adapters;

	for (TUInt i=0; i<tItems.size(); i++)
   	adapters.push_back(TRangeAdapter(tItems[i]));

TAdaptedRangeMap<> adaptedRangeMap(tAlias, adapters);

	_BasePRangeMapsContainer.AddItem(adaptedRangeMap);
};

TUInt TRangeMapsEqualifer::Count() const
{
	return _BasePRangeMapsContainer.Count();
};

void TRangeMapsEqualifer::Clear()
{
	_BasePRangeMapsContainer.Clear();
    _ResultRangeMapsContainer.Clear();
};

TRangeMapsEqualifer::TRangeMapsEqualifer()
{
};

TRangeMapsEqualifer::~TRangeMapsEqualifer()
{
	Clear();
};
