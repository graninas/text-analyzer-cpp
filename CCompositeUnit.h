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
#ifndef CCompositeUnitH
#define CCompositeUnitH
//---------------------------------------------------------------------------

#include "UTypes.h"


// ласс €вл€етс€ предком дл€ всех классов, представл€ющих собой единицу компоновки текста.

    class TCompositeUnit
    {
        protected:

          TUInt _From;
          TUInt _To;

          TUInt _Smaller(const TUInt & tFrom, const TUInt & tTo) const
          {
              return (tFrom < tTo) ? tFrom : tTo;
          };

          TUInt _Bigger(const TUInt & tFrom, const TUInt & tTo) const
          {
              return (tFrom > tTo) ? tFrom : tTo;
          };

       public:

          TUInt From()   const { return _From; };
          void  From(TUInt tIndex) { _From = tIndex; };
          TUInt To()     const { return _To; };
          void  To(TUInt tIndex) { _To = tIndex; };

          TUInt Length() const { return _To - _From + 1; };
          TUInt Count()  const { return _To - _From + 1; };


          TCompositeUnit operator+ (const TCompositeUnit & tItem) const
          {
              TCompositeUnit tmp = *this;

              if (_From > tItem._From) tmp._From = tItem._From;
              if (_To < tItem._To)     tmp._To   = tItem._To;

          return tmp;
          };


          friend TBool operator == (const TCompositeUnit & tItem1, const TCompositeUnit & tItem2)
          {
              return ((tItem1._From == tItem2._From) && (tItem1._To == tItem2._To)) ? true : false;
          };

          friend TBool operator < (const TCompositeUnit & tItem1, const TCompositeUnit & tItem2)
          {
              return (tItem1._To < tItem2._From) ? true : false;
          };


 /*         TBool operator > (const TCompositeUnit & tItem)
          {
             return this->_From > tItem._To;
          };

          TBool operator < (const TCompositeUnit & tItem)
          {
             return this->_To < tItem._From;
          };        */


        TCompositeUnit(){};
        TCompositeUnit(const TUInt & tFrom, const TUInt & tTo) : _From(_Smaller(tFrom, tTo)), _To(_Bigger(tFrom, tTo)){};
    };



#endif
 