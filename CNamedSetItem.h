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
#ifndef CNamedSetItemH
#define CNamedSetItemH
//---------------------------------------------------------------------------

#include "UTypes.h"
#include "CCharsSet.h"


//Пример шаблона - если захочется в будущем использовать.
//Ему необходима доработка: метод IsSubset, манипуляции с set...
/*   template <class ElementType> class TSet
   {
      private:

          set <ElementType> _Set;
      public:
         typedef ElementType TElementType;


   } ;  */


   template <class NameType, class SetType> class TNamedSetItem
   {
       private:
            NameType   _Name;
            SetType    _Set;

       public:

         NameType Name() const { return _Name; };
         NameType Name(NameType tName)  { _Name = tName; };
         SetType  Set()  const  { return _Set;  };
         SetType  Set( SetType  tSet)   { _Set = tSet; };

         TBool  IsSubset(const SetType::TElementType & tElement) const
         {
             return _Set.IsSubset(tElement);
         }

         TBool  IsSubset(const SetType & tSet)  const
         {
             return _Set.IsSubset(tSet);
         }

         SetType::TElementType  EmptySubset()  const
         {
             return _Set.EmptySubset();
         }

         TBool operator == (const TNamedSetItem & tItem) { return (_Set == tItem._Set); };

         //For STL algorithms.
         friend TBool operator == (const TNamedSetItem & tItem1, const TNamedSetItem & tItem2)
         {
              return (tItem1._Set == tItem2._Set) ? true : false;
         };

         TNamedSetItem(const NameType & tName, const SetType & tSet) : _Name(tName), _Set(tSet){};
         TNamedSetItem(const NameType & tName, SetType::TElementType tElement) : _Name(tName), _Set(tElement){};
   };


/*
   Примеры использования.


       TNamedSetItem<TTextString, TCharsSet> NSI("Digits", TCharsSet("0123456789"));

    if (NSI.IsSubset(""))  Edit1->Text = "true";
    else                   Edit1->Text = "false";


    if (NSI.IsSubset(TCharsSet("123444444f")))  Edit2->Text = "true";
    else                                        Edit2->Text = "false";
*/

#endif
 