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
#ifndef DLengthCounterH
#define DLengthCounterH
//---------------------------------------------------------------------------


#include "UStructs.h"
#include "DLengthCount.h"


    class TLengthCounter
    {
    public:
    	typedef TTextString SpecificatorType;
        SpecificatorType Specificator() { return _Alias; };

        class EOutOfRange{};

		typedef vector<TRangeItem> TRangeItems;
    	typedef map<TUInt, TLengthCount> TLengthCounts;

    private:

    	TTextString   _Alias;
        TLengthCounts _LengthCounts;

        TLengthCount 			_Dummy;
        TLengthCounts::iterator _Iterator;


        void _AddItem(const TUInt & tLength, const TUInt & tItemIndex);
		void _EvaluateItem (const TRangeItem & tItem, const TUInt & tItemIndex);

    public:

    	TTextString Alias() const;
        void Alias(const TTextString & tAlias);

        void EvaluateItems(TRangeItems tItems);

		TUInt MinLength();
        TUInt MaxLength();
        void  MinCount(const TUInt & tLength, TUInt * tMin);

        void  AddLengthCount(const TUInt & tLength, const TUInt & tCount);

        TLengthCount & operator[](const TUInt & tLength);


           TLengthCounts::iterator ToBegin();
           TLengthCounts::iterator ToEnd();

           TLengthCounts::iterator Begin();
           TLengthCounts::iterator End();

           TLengthCounts::iterator Next();


        void Clear();

        TLengthCounter() : _Alias(""), _Iterator(_LengthCounts.end()) {};
        TLengthCounter(const TTextString & tAlias) : _Alias(tAlias), _Iterator(_LengthCounts.end()){};
       ~TLengthCounter(){ Clear(); }
    };



#endif
