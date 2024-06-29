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
#ifndef CFrequencyTableH
#define CFrequencyTableH
//---------------------------------------------------------------------------

#include "UStructs.h"
#include <map>

#include "CErrorSpecificators.h"


enum TFrequencyTableManipulators {ftm_Clear, ftm_ClearNullItems};

template <class KeyType> class TFrequencyTable
{
   public:

      class TFrequencyItem
      {
      public:
          KeyType  Key;
          TUInt    Count;
          TFrequencyItem(KeyType tKey, TUInt tCount) : Key(tKey), Count(tCount){};
          TFrequencyItem(){};
      };

      typedef map<KeyType, TUInt> 	 TFrequencyMap;
      typedef vector<TFrequencyItem> TFrequencyVector;

   private:

      TFrequencyMap   _Map;

   public:

      TFrequencyTable & operator << (TFrequencyTable tTable)
      {
         TFrequencyMap :: iterator tIter;

         tIter = tTable._Map.begin();

            while (tIter != tTable._Map.end())
            {
              _Map[(*tIter).first] += (*tIter).second;
              tIter++;
            }

      return *this;
      };

      TFrequencyTable & operator << (const TFrequencyTable & tTable)
      {
         TFrequencyMap :: iterator tIter;

         tIter = tTable._Map.begin();

            while (tIter != tTable._Map.end())
            {
              _Map[(*tIter).first] += (*tIter).second;
              tIter++;
            }

      return *this;
      };

      TFrequencyTable & operator << (const TFrequencyItem & tItem)
      {
        _Map[tItem.Key] += tItem.Count;

         return *this;
      };

      TFrequencyTable & operator << (const KeyType & tKey)
      {
        _Map[tKey] += 1;
         return *this;
      };

      TFrequencyTable & operator << (const TFrequencyTableManipulators & tManipulator)
      {
         switch(tManipulator)
         {
             case ftm_Clear:           Clear(); break;
             case ftm_ClearNullItems:  ClearNullItems(); break;
         };

         return *this;
      };

      TFrequencyTable & operator << (const TFrequencyVector & tFrequencyVector)
      {
         for (TUInt i=0; i<tFrequencyVector.size(); i++)
            _Map[tFrequencyVector[i].Key] += tFrequencyVector[i].Count;
         return *this;
      };

      TFrequencyTable & operator >> (TFrequencyTable & tTable)
      {
         TFrequencyMap :: iterator tIter;

            tIter = tTable._Map.begin();

         while (tIter != tTable._Map.end())
         {
            _Map.erase((*tIter).first);

            tIter++;
         };

      return *this;
      };

      TFrequencyTable & operator >> (const TFrequencyItem & tItem)
      {
         _Map.erase(tItem.Key);

         return *this;
      };

      TFrequencyTable & operator >> (const KeyType & tKey)
      {
        _Map.erase(tKey);

         return *this;
      };

      TFrequencyTable & operator >> (const TFrequencyVector & tFrequencyVector)
      {
         for (TUInt i=0; i<tFrequencyVector.size(); i++)
            _Map.erase(tFrequencyVector[i].Key);
            
         return *this;
      };

      TFrequencyVector FrequencyVector()
      {
      TFrequencyVector v;

         TFrequencyMap :: iterator tIter;

            tIter = _Map.begin();

         while (tIter != _Map.end())
         {
             v.push_back(TFrequencyItem((*tIter).first, (*tIter).second));
             tIter++;
         };

      return v;
      };


      inline TUInt & operator [] (KeyType tKey)
      {
          return _Map[tKey];
      };

      TUInt Count() const
      {
          return _Map.size();
      };

      void Clear()
      {
          _Map.clear();
      };

      void ClearNullItems()
      {
         TFrequencyMap tmp = _Map;
         TFrequencyMap :: iterator thisIter;

            thisIter = tmp.begin();

         while (thisIter != tmp.end())
         {
            if ((*thisIter).second == 0) _Map.erase((*thisIter).first);

            thisIter++;
         };
      };

      TFrequencyTable() {};
      TFrequencyTable(const TFrequencyVector & tFrequencyVector)
      {
          (*this) << tFrequencyVector;
      };
     ~TFrequencyTable() { Clear(); };
};

/*

   Примеры использования (передаваемые значения менялись на ходу, так что с "ожиданиями" могут быть расхождения).

   TFrequencyTable<char> CFT;
   typedef TFrequencyTable<char>::TFrequencyItem TCharMapItem;

      TCharMapItem Item;
      Item.Key = 'a';
      Item.Count = 10;


      CFT['f'] = 1;
      CFT['4'] = 1;
      CFT['f'] += 4;

      Memo3->Lines->Add(IntToStr(CFT.Count()));

   CFT << Item;
   CFT << TCharMapItem('s', 6) << TCharMapItem('s', 10);

      Memo3->Lines->Add(IntToStr(CFT.Count()));
      Memo1->Lines->Add("f :" + IntToStr(CFT['f']));
      Memo1->Lines->Add("c :" + IntToStr(CFT['c']));
*/


/*

   TFrequencyTable<char> CFT;
   TFrequencyTable<char> CFT2;

   typedef TFrequencyTable<char>::TFrequencyItem TCharMapItem;

      CFT['f'] = 1;
      CFT['4'] = 1;
      CFT['s'] = 10;

      Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 3 expected");

      CFT2['s'] = 20;
      CFT2['k'] = 100;

      Memo3->Lines->Add("CFT2.Count = " + IntToStr(CFT2.Count()) + ", 2 expected");
      Memo3->Lines->Add("Merge into CFT...");

   CFT << CFT2;
      Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 4 expected");

   Memo3->Lines->Add("CFT2 Refilling...");
   CFT2.Clear();
   CFT2['1'] = 1;
   CFT2['2'] = 1;
   CFT2['4'] = 1;
   CFT2['s'] = 1;
   CFT2 << TCharMapItem('p', 99);

      Memo3->Lines->Add("CFT2.Count = " + IntToStr(CFT2.Count()) + ", 5 expected");
      Memo3->Lines->Add("CFT2[p] = " + IntToStr(CFT2['p']) + ", 99 expected");

      Memo3->Lines->Add("Removing from CFT...");
   CFT >> CFT2;

      Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 2 expected");
      Memo3->Lines->Add("CFT2.Count = " + IntToStr(CFT2.Count()) + ", 5 expected");

      Memo3->Lines->Add("Removing from CFT2...");
   CFT2 >> TCharMapItem('p', 0);
      Memo3->Lines->Add("CFT2.Count = " + IntToStr(CFT2.Count()) + ", 4 expected");
      Memo3->Lines->Add("CFT2[p] = " + IntToStr(CFT2['p']) + ", 0 expected");
      Memo3->Lines->Add("CFT2.Count = " + IntToStr(CFT2.Count()) + ", 5 expected");

   CFT2.ClearNullItems();

      Memo3->Lines->Add("CFT2.Count = " + IntToStr(CFT2.Count()) + ", 4 expected");
*/

/*
   TFrequencyTable<char> CFT;

   typedef TFrequencyTable<char>::TFrequencyItem TCharMapItem;

      CFT['f'] = 1;
      CFT['4'] = 0;
      CFT['s'] = 10;
      CFT << 'd' << 's';

      Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 4 expected");
         CFT << ftm_ClearNullItems;
      Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 3 expected");
         CFT << ftm_Clear;
      Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 0 expected");
*/

/*

typedef TFrequencyTable<char>::TFrequencyVector TFVector;
typedef TFrequencyTable<char>::TFrequencyItem TCharMapItem;

  TFVector v;
    v.push_back(TCharMapItem('d', 22));

TFrequencyTable<char> CFT(v);

       Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 1 expected");

   v.push_back(TCharMapItem('c', 12));
   v.push_back(TCharMapItem('d', 10));

   CFT << v;
       Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 2 expected");
   CFT >> v;
       Memo3->Lines->Add("CFT.Count = " + IntToStr(CFT.Count()) + ", 0 expected");


*/

#endif
