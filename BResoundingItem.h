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
#ifndef BResoundingItemH
#define BResoundingItemH
//---------------------------------------------------------------------------
#include "CErrorSpecificators.h"
#include "UStructs.h"
#include "CRangeItem.h"



    class TResoundingItem : public TErrorSpecificators  //"Единица звучания"
    {
        public:
             typedef vector<TUInt>  TLinkDots;   //LinkDot - символ в тексте. 
             
        private:

            TLinkDots _LinkDots;

        public:

        //Попадает ли в диапазон
           TBool   In(const TUInt & tIndex)  { return AffectedRange().In(tIndex); };
        //Пересекается ли с диапазоном
           TBool   Intersects(const TRangeItem & tRange) { return AffectedRange().Intersects(tRange); }

        //Подсоединена ли точка
           TBool   IsLinked(const TUInt & tLinkDot)
           {
               TUInt index;
               return GetLinkDot(tLinkDot, &index);
           };

        //Захваченная область текста
            TRangeItem  AffectedRange() const
            {
                 if (!_LinkDots.size()) throw ENoLinkDots();
                 TRangeItem dummy(_LinkDots[0], _LinkDots[_LinkDots.size()-1]);

            return dummy;
            };

            TLinkDots  LinkDots() const { return _LinkDots; }

         //Найти точку привязки; если существует - tIndex, true.
            TBool   GetLinkDot(const TUInt & tLinkDot, TUInt * tIndex)
            {
               for (TUInt i=0; i<_LinkDots.size(); i++)
                 if (_LinkDots[i] == tLinkDot)
                 {
                      *tIndex =i;
                      return true;
                 };
            return false;
            };

            void       Merge(const TResoundingItem & tItem)
            {
            TUInt index;
            TLinkDots  linkDots = tItem.LinkDots();

               for (TUInt i=0; i<linkDots.size(); i++)
                 if (!GetLinkDot(linkDots[i], &index)) _LinkDots.push_back(linkDots[i]);
            };


            TResoundingItem & operator << (const TUInt & tIndex)
            {
                _LinkDots.push_back(tIndex);
                return *this;
            };

                inline TUInt & operator [] (const TUInt & tIndex)
                {
                    if (tIndex >= _LinkDots.size()) throw EOutOfRange();

                return _LinkDots[tIndex];
                };

            TUInt Count() const { return _LinkDots.size(); };
            void  Clear()       { _LinkDots.clear(); };


           TResoundingItem(){};
          ~TResoundingItem(){ Clear(); }
    };






#endif
