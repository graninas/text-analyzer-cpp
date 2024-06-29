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
#ifndef CRangeItemH
#define CRangeItemH
//---------------------------------------------------------------------------

#include "CCompositeUnit.h"

   class TRangeItem : public TCompositeUnit
   {
       public:

          TRangeItem() : TCompositeUnit(){};
          TRangeItem(TRangeItem * tRangeItem) : TCompositeUnit(tRangeItem->From(), tRangeItem->To()) {}
          TRangeItem(const TUInt & tFrom, const TUInt & tTo) : TCompositeUnit(tFrom, tTo){};


          TRangeItem operator+ (const TRangeItem & tItem) const
          {
              TRangeItem tmp = *this;

              if (_From > tItem._From) tmp._From = tItem._From;
              if (_To < tItem._To)     tmp._To   = tItem._To;

          return tmp;
          };

          TRangeItem * PRange()
          {
              return this;
          }

          TBool In(const TUInt & tIndex) const
          {
               return ((tIndex>=_From) && (tIndex<=_To)) ? true : false;
          };

          TBool Intersects(const TRangeItem & tRange) const
          {
              return (In(tRange.From()) || (In(tRange.To())));
          };
   };

#endif
 