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
#ifndef BRuleResoundingItemsH
#define BRuleResoundingItemsH
//---------------------------------------------------------------------------

#include "BResoundingItem.h"
#include "CErrorSpecificators.h"

    class TRuleResoundingItems : public TErrorSpecificators
    {
        public:
             typedef vector<TResoundingItem> TResoundingItems;

        private:

            TSFloat   _Value;
            TUInt     _RuleNumber;

            TResoundingItems _Items;

        public:

            TBool IsValidIndex(const TUInt & tIndex)
            {
                if (tIndex >= _Items.size()) return false;
            return true;
            }

            TSFloat    Value()      const { return _Value; };
            void       Value(const TSFloat & tValue) { _Value = tValue; };
            TUInt      RuleNumber() const { return _RuleNumber; }

            TUInt      Count()      const { return _Items.size(); }
            TResoundingItems & ResoundingItems() { return _Items; }

            TRuleResoundingItems & operator << (const TSFloat & tValue)
            {
                _Value = tValue;
                return *this;
            };

            TRuleResoundingItems & operator << (const TResoundingItem & tItem)
            {
                _Items.push_back(tItem);
                return *this;
            };

            void AddItem(const TResoundingItem & tItem)
            {
                 _Items.push_back(tItem);
            };

            void Merge(const TResoundingItem & tItem)
            {
                if (!_Items.size()) AddItem(tItem);
                else  _Items[_Items.size()-1].Merge(tItem);
            };

            void Clear()
            {
                for (TUInt i=0; i<_Items.size(); i++)
                 _Items[i].Clear();
            _Items.clear();
            }

            inline TResoundingItem & operator[] (const TUInt & tIndex)
            {
                if (!IsValidIndex(tIndex)) throw EOutOfRange();
            return _Items[tIndex];
            };


//tLinkDot == index в тексте
            TBool GetLinkedResoundingItems(const TUInt & tLinkDot, TRuleResoundingItems * tTarget)
            {
                TRuleResoundingItems dummy(_Value, _RuleNumber);

                   for (TUInt i=0; i<_Items.size(); i++)
                      if (_Items[i].IsLinked(tLinkDot)) dummy.AddItem(_Items[i]);

               (*tTarget) = dummy;

               if (dummy.Count()) return true;
            return false;
            };

            TBool Intersects(const TUInt & tLinkDot)
            {
                   for (TUInt i=0; i<_Items.size(); i++)
                      if (_Items[i].IsLinked(tLinkDot)) return true;
            return false;
            }




        TRuleResoundingItems(const TSFloat & tValue, const TUInt & tRuleNumber) : _Value(tValue), _RuleNumber(tRuleNumber) {};
        TRuleResoundingItems(){};
       ~TRuleResoundingItems(){ Clear(); }
    };

#endif
 