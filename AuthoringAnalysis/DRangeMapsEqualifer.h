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
#ifndef DRangeMapsEqualiferH
#define DRangeMapsEqualiferH
//---------------------------------------------------------------------------


#include "DAdaptedRangeMap.h"
#include "CSpecificatorContainer.h"
#include "DLengthCounter.h"

class TRangeMapsEqualifer
{
public:

    typedef TSpecificatorContainer<TAdaptedRangeMap<> >   			TBasePRangeMapsContainer;
    typedef TSpecificatorContainer<TAdaptedRangeMap<TRangeItem> >   TEqualifiedMapsContainer;

    typedef vector<TRangeItem>  TRangeItems;

private:

	typedef TSpecificatorContainer<TLengthCounter> TLengthCountersContainer;

	typedef vector<TRangeItem*> PRangeItems;

	TBasePRangeMapsContainer  _BasePRangeMapsContainer;
    TEqualifiedMapsContainer  _ResultRangeMapsContainer;

    TRangeItems	_ConvertToRangeItems(const TAdaptedRangeMap<>::TRangeAdapters & tAdapters);

    void _SortMaps();
    void _EvaluateLengths(TLengthCountersContainer * tCountersContainer);
    void _EvaluateCommonLengthCounts(TLengthCountersContainer * tCountersContainer, TLengthCounter * tTargetCounter);
    void _EqualifyMaps(TLengthCountersContainer * tCountersContainer, TLengthCounter * tTemplateCounter);

    class EInvalidCountersContainer{};

public:

	void AddMap(const TTextString & tAlias, PRangeItems tItems);

    void Equalify();

    TRangeItems operator[](const TTextString & tAlias);

    TEqualifiedMapsContainer EqualifiedMapsContainer();

    TUInt Count() const;
    void  Clear();

	TRangeMapsEqualifer();
   ~TRangeMapsEqualifer();
};


                /*
                    while (iter != tTemplateCounter->End())
    {
    length = (*iter).first;
    count  = (*iter).second.Count();

    	for (TUInt i=0; i<tCountersContainer->Count(); i++)
        {
        	alias = (*tCountersContainer)[i].Specificator();
        	index = (*tCountersContainer)[i][length].AffectedRange().From();

        TAdaptedRangeMap<> map(alias);
        map.AddItems(_BasePRangeMapsContainer[alias].RangeItems(index, count));
        _ResultRangeMapsContainer.AddItem(map);
        };
    iter++;
    };
                */

#endif
