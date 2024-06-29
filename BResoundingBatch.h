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
#ifndef BResoundingBatchH
#define BResoundingBatchH
//---------------------------------------------------------------------------

#include "BRuleResoundingItems.h"
#include "CErrorSpecificators.h"


    class TResoundingBatch : public TErrorSpecificators
    {
        public:

              typedef vector<TRuleResoundingItems> TResoundingInstances;

        private:

            TResoundingInstances  _Instances;


            void _Merge(const TUInt & tInstanceIndex, TResoundingItem & tResoundingItem)
            {
                if (_Instances[tInstanceIndex].Count())
                {
                TUInt lastItem = _Instances[tInstanceIndex].Count()-1;

                     if (_Instances[tInstanceIndex][lastItem].Intersects(tResoundingItem.AffectedRange()))
                         _Instances[tInstanceIndex][lastItem].Merge(tResoundingItem);
                     else
                         _Instances[tInstanceIndex].AddItem(tResoundingItem);
                }
                else _Instances[tInstanceIndex].AddItem(tResoundingItem);
            };


             TBool _Find(const TUInt & tRuleNumber, TUInt * tIndex)
             {
                 for (TUInt i=0; i<_Instances.size(); i++)
                 if ( _Instances[i].RuleNumber() == tRuleNumber)
                 {
                     *tIndex = i;
                     return true;
                 }
             return false;
             };


             void _AddItem(TRuleResoundingItems & tRuleResoundingItem)
             {
                _Instances.push_back(tRuleResoundingItem);
             };

        public:


             TBool IsValidIndex(const TUInt & tIndex) const
             {
                if (tIndex >= _Instances.size()) return false;
             return true;
             }

             TUInt Count()     const { return _Instances.size(); }

             void  Merge(const TUInt & tIndex,  TResoundingItem & tResoundingItem)
             {
                 if (!IsValidIndex(tIndex)) throw EInvalidInstanceIndex();

                _Merge(tIndex, tResoundingItem);
             };

             void  AddInstance(const TSFloat & tValue, const TUInt & tRuleNumber)
             {
             TRuleResoundingItems dummy(tValue, tRuleNumber);
                 _Instances.push_back(dummy);
             };

            inline TRuleResoundingItems & operator[] (const TUInt & tIndex)
            {
                if (!IsValidIndex(tIndex)) throw EOutOfRange();
                return  _Instances[tIndex];
            };


//tLinkDot == index в тексте
            TBool PackLinkedBatch(const TUInt & tLinkDot, TResoundingBatch * tTarget)
            {
                TResoundingBatch      batchDummy;
                TRuleResoundingItems  resItemsDummy;

                   for (TUInt i=0; i<_Instances.size(); i++)
                      if (_Instances[i].GetLinkedResoundingItems(tLinkDot, &resItemsDummy))
                          batchDummy._AddItem(resItemsDummy);

               (*tTarget) = batchDummy;

               if (batchDummy.Count()) return true;
            return false;
            };

            TBool Intersects(const TUInt & tLinkDot)
            {
                   for (TUInt i=0; i<_Instances.size(); i++)
                      if (_Instances[i].Intersects(tLinkDot)) return true;
            return false;
            }



             void Clear()
             {
                  for (TUInt i=0; i<_Instances.size(); i++)
                  _Instances[i].Clear();
             _Instances.clear();
             };

             TResoundingBatch(){};
    };




#endif
 