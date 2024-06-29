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
#ifndef CSpecificatorContainerH
#define CSpecificatorContainerH
//---------------------------------------------------------------------------

#include "CContainer.h"

/*
   Требования:
     - тип ItemType::SpecificatorType
     - SpecificatorType Specificator() {}
       (В случае неуникальности будет возвращаться первый попавшийся объект
        с этим спецификатором.)
*/

template <class ItemType> class TSpecificatorContainer : public TContainer<ItemType>
{
public:

    TBool GetIndex(const ItemType::SpecificatorType & tSpecificator, TUInt *tIndex) const
    {
        for (TUInt i=0; i<_Items.size(); i++)
          if (_Items[i].Specificator() == tSpecificator)
          {
               (*tIndex) = i;
               return true;
          }
    return false;
    };

    TBool GetSpecificator(const TUInt & tIndex, ItemType::SpecificatorType * tSpecificator) const
    {
        if (IsValidIndex(tIndex))
        {
           *tSpecificator = _Items[tIndex].Specificator();
        return true;
        }
    return false;
    };

    TBool IsInvalidSpecificator(const ItemType::SpecificatorType & tSpecificator) const
    {
        TUInt index;
        if (!GetIndex(tSpecificator, &index)) return false;
    return true;
    };

    ItemType & Item(const ItemType::SpecificatorType & tSpecificator)
    {
    TUInt Index;
        if  (GetIndex(tSpecificator, &Index)) return _Items[Index];

    throw EInvalidIndex();
    };

    ItemType * PItem(const ItemType::SpecificatorType & tSpecificator)
    {
    TUInt Index;
        if  (GetIndex(tSpecificator, &Index)) return &_Items[Index];

    throw EInvalidIndex();
    };

    inline ItemType & operator [] (const TUInt & tIndex)
    {
        if (!IsValidIndex(tIndex)) throw EOutOfRange();

        return _Items[tIndex];
    };

    inline ItemType & operator [] (const ItemType::SpecificatorType & tSpecificator)
    {
    TUInt Index;
        if  (!GetIndex(tSpecificator, &Index)) throw EOutOfRange();

        return _Items[Index];
    };


      TBool DeleteItem(const ItemType::SpecificatorType & tSpecificator)
      {
      TUInt Index;
          if  (GetIndex(tSpecificator, &Index))
          {
             _Items.erase(&_Items[Index]);
             return true;
          }

      return false;
      };

     TSpecificatorContainer() : TContainer<ItemType>() {};
    ~TSpecificatorContainer(){ Clear(); };
};

#endif
 