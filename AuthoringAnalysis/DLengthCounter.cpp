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
#include "DLengthCounter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void TLengthCounter::_AddItem(const TUInt & tLength, const TUInt & tItemIndex)
{
TLengthCounts::iterator iter = _LengthCounts.find(tLength);

	if (iter != _LengthCounts.end())
    {
		_LengthCounts[tLength]++;
   		_LengthCounts[tLength].AffectedRange().To(tItemIndex);
    }
	else
       	_LengthCounts[tLength] = TLengthCount(1, TRangeItem(tItemIndex, tItemIndex));
};

void TLengthCounter::_EvaluateItem(const TRangeItem & tItem, const TUInt & tItemIndex)
{
	_AddItem(tItem.Length(), tItemIndex);
};


TTextString TLengthCounter::Alias() const
{
	return _Alias;
};

void TLengthCounter::Alias(const TTextString & tAlias) 
{
	_Alias = tAlias;
};


void TLengthCounter::EvaluateItems(TRangeItems tItems)
{
	for (TUInt i=0; i<tItems.size(); i++)
	    _EvaluateItem(tItems[i], i);
};

TUInt TLengthCounter::MinLength()
{
	TLengthCounts::iterator iter = _LengthCounts.begin();
    TUInt minLength = (*iter).first;
    iter++;
		while(iter != _LengthCounts.end())
        {
			if ((*iter).first < minLength) minLength = (*iter).first;
        iter++;
        }
return minLength;
};

TUInt TLengthCounter::MaxLength()
{
	TLengthCounts::iterator iter = _LengthCounts.begin();
    TUInt maxLength = (*iter).first;
    iter++;
		while(iter != _LengthCounts.end())
        {
			if ((*iter).first > maxLength) maxLength = (*iter).first;
        iter++;
        }
return maxLength;
};

void TLengthCounter::MinCount(const TUInt & tLength, TUInt * tMin)
{
	TLengthCounts::iterator iter = _LengthCounts.find(tLength);

    if (iter == _LengthCounts.end())     (*tMin) = 0;
    if (_LengthCounts[tLength].Count() < (*tMin)) (*tMin) = _LengthCounts[tLength].Count();
};


void TLengthCounter::AddLengthCount(const TUInt & tLength, const TUInt & tCount)
{
if (!tCount) return;
	_LengthCounts[tLength].Count(tCount);
};

             
TLengthCount & TLengthCounter::operator[](const TUInt & tLength)
{
TLengthCounts::iterator iter = _LengthCounts.find(tLength);

	if (iter == _LengthCounts.end())
    	return _Dummy;

return (*iter).second;
};

TLengthCounter::TLengthCounts::iterator TLengthCounter::ToBegin()
{
	_Iterator = _LengthCounts.begin();
return _Iterator;
};

TLengthCounter::TLengthCounts::iterator TLengthCounter::ToEnd()
{
	_Iterator = _LengthCounts.end();
return _Iterator;
};

TLengthCounter::TLengthCounts::iterator TLengthCounter::Begin()
{
	return _LengthCounts.begin();
}
TLengthCounter::TLengthCounts::iterator TLengthCounter::End()
{
	return _LengthCounts.end();
};

TLengthCounter::TLengthCounts::iterator TLengthCounter::Next()
{
    if (_Iterator != _LengthCounts.end()) _Iterator++;
return _Iterator;
};

void TLengthCounter::Clear()
{
	_LengthCounts.clear();
    _Alias = "";
    _Iterator = _LengthCounts.end();
}


