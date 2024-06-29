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
#ifndef APageH
#define APageH
//---------------------------------------------------------------------------

#include "CRangeItem.h"
#include "CErrorSpecificators.h"
#include "UStructs.h"

namespace ns_Page
{

   class TPage : public TErrorSpecificators
   {
       public:

           typedef vector<TRangeItem> TRows;

       private:

           TRows _Rows;

       public:

           TBool IsValidIndex(const TUInt & tIndex) const
           {
               if (tIndex >= _Rows.size()) return false;
           return true;
           }

           TRangeItem Range() const
           {
              if (!_Rows.size()) throw ENoChildItems();
           return TRangeItem(_Rows[0].From(), _Rows[_Rows.size()-1].To());
           };

           inline TRangeItem & operator[] (const TUInt & tIndex)
           {
               if (!IsValidIndex(tIndex)) throw EOutOfRange();
           return _Rows[tIndex];
           };

           TUInt TextIndex(const TUInt & tRow, const TUInt & tCol)
           {
              TRangeItem range = _Rows[tRow];
           return range.From() + tCol;
           };

           TPage & operator << (const TRangeItem & tRow)
           {
              _Rows.push_back(tRow);
           return *this;
           };


           TUInt RowLength(const TUInt & tIndex) const
           {
           if (!IsValidIndex(tIndex)) throw EInvalidIndex();
               return _Rows[tIndex].Length();
           };

           TUInt MaxRowLength() const
           {
           if (!_Rows.size()) throw ENoChildItems();
           
               TUInt max = _Rows[0].Length();

               for (TUInt i=1; i<_Rows.size(); i++)
               if (_Rows[i].Length() > max) max = _Rows[i].Length();

           return max;
           };


           TUInt RowsCount() const { return _Rows.size(); }
           TUInt Count()     const { return _Rows.size(); }

           void Clear()  { _Rows.clear(); };

           TPage(){};
          ~TPage(){ Clear(); }
   };

};   //End of namespace

#endif
