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
#ifndef CDataContainerH
#define CDataContainerH
//---------------------------------------------------------------------------


#include "UStructs.h"
#include "CErrorSpecificators.h"
#include "CTextStringList.h"
#include "CSpecificatorContainer.h"


/*
   Требования:
     - тип ItemType::SpecificatorType
     - SpecificatorType Specificator() {}
       (В случае неуникальности будет возвращаться первый попавшийся объект
        с этим спецификатором.)
*/




template <class ItemType> class TDataContainer : public TSpecificatorContainer<ItemType>
{
public:

   TTextString * Data(const TUInt & tIndex) const
   {
      if (!IsValidIndex(tIndex)) throw EInvalidIndex();
   return _Items[tIndex].Data();
   };

    TTextString * Data(const ItemType::SpecificatorType & tSpecificator) const
    {
    TUInt Index;
        if  (GetIndex(tSpecificator, &Index)) return Data(Index);
    throw EInvalidIndex();
    };

    TTextString Text(const TUInt & tIndex) const
    {
      if (!IsValidIndex(tIndex)) throw EInvalidIndex();

    return _Items[tIndex].Text();
    };

    TTextString Text(const ItemType::SpecificatorType & tSpecificator) const
    {
    TUInt Index;
        if  (GetIndex(tSpecificator, &Index)) return Text(Index);
    throw EInvalidIndex();
    };

    TBool GetAlias(const TUInt & tIndex, TTextString * tAlias)
    {
        return GetSpecificator(tIndex, tAlias);
    };

    TBool IsValidAlias(const TTextString & tAlias) const
    {
        return IsInvalidSpecificator(tAlias);
    };

    TTextStringList    AliasesList()
    {
        TTextStringList list;
        for (TUInt i=0; i<Count(); i++)
            list.AddItem(_Items[i].Alias());
    return list;
    };


     TDataContainer() : TSpecificatorContainer<ItemType>(){};
    ~TDataContainer(){ Clear(); };
};



#endif
