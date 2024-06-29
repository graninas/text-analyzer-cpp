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
#ifndef CNamedSetsContainerH
#define CNamedSetsContainerH
//---------------------------------------------------------------------------

#include "CNamedSetItem.h"
#include "UStructs.h"

#include "CErrorSpecificators.h"


    template <class NameType, class SetType> class TNamedSetsContainer : public TErrorSpecificators
    {
         public:
             typedef vector<TNamedSetItem<NameType, SetType> > TNamedSets;

         private:
            TNamedSets _Sets;

            TBool _IsValidIndex(const TUInt & tIndex) const
            {
                  if (tIndex >= _Sets.size()) return false;
                  else return true;
            };

            TBool _GetIndex(const NameType & tName, TUInt *tIndex)
            {
                for (TUInt i=0; i<_Sets.size(); i++)
                  if (_Sets[i].Name() == tName)
                  {
                       (*tIndex) = i;
                       return true;
                  }
            return false;
            };

         public:

             TBool IsExist(const NameType & tName)
             {
                  TUInt Index;
                  return (_GetIndex(tName, &Index));
             };

             TBool AddItem(const TNamedSetItem<NameType, SetType> & tSetItem)
             {
                 TUInt Index;
                 if (_GetIndex(tSetItem.Name(), &Index)) return false;

                 _Sets.push_back(tSetItem);
                 return true;
             };

             TBool    DeleteItem(const NameType & tName)
             {
             TUInt Index;
                 if  (_GetIndex(tName, &Index))
                 {
                     _Sets.erase(&_Sets[Index]);
                     return true;
                 };

             return false;
             };

             TUInt    Count() const { return _Sets.size(); };


           inline SetType operator [] (const NameType & tName)
           {
             TUInt Index;
                 if  (_GetIndex(tName, &Index)) return _Sets[Index].Set();
                 else throw EOutOfRange();
           };


            TNamedSetsContainer & operator << (const TNamedSetItem<NameType, SetType> & tSetItem)
            {
                AddItem(tSetItem);
                return *this;
            }


             void Clear() { _Sets.clear(); };

             TNamedSetsContainer(){};
            ~TNamedSetsContainer(){};

    };


/*

Протестировано. Работает.

Примеры использования.

    TNamedSetItem<TTextString, TCharsSet> NSI("Digits", TCharsSet("0123456789"));


    if (NSI.IsSubset(""))  Edit1->Text = "true";
    else                   Edit1->Text = "false";

    if (NSI.IsSubset(TCharsSet("123444444f")))  Edit2->Text = "true";
    else                                        Edit2->Text = "false";


    typedef TNamedSetItem<TTextString, TCharsSet> TNSI;
    TNSI s1("RusSmall", TCharsSet("абвгдеёжзийклмнопрстуфхцчшщъыьэюя"));

    TNamedSetsContainer<TTextString, TCharsSet> NSC;

       NSC.AddItem(s1);
         Edit2->Text = NSC["RusSmall"].Elements();
         Label1->Caption = NSC.Count();

       NSC << TNSI("RusBig", "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ") << NSI <<
              TNSI("LatBig", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
         Edit2->Text = NSC["RusBig"].Elements();
         Edit1->Text = NSC["LatBig"].Elements();
         Label1->Caption = NSC.Count();

         //Error generating:
         //Edit1->Text = NSC["LaввtBig"].Elements();

*/


#endif
 