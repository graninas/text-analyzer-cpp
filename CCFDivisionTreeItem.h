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
#ifndef CCFDivisionTreeItemH
#define CCFDivisionTreeItemH
//---------------------------------------------------------------------------

#include "CDivisionTreeItem.h"
#include "CFrequencyTable.h"
#include "CRangeItem.h"


enum TCFTreeLevelsDefiner {tlm_FirstLevel=0, tlm_LastLevel, tlm_LastButOneLevel};

template <class LevelDataType, class CompositeUnitType> class TCFTreeLevelInfo;

   template <class LevelDataType, class CompositeUnitType> class TCFDivisionTreeItem : public TDivisionTreeItem<LevelDataType, CompositeUnitType>
   {
   friend class TCFTreeLevelInfo<LevelDataType, CompositeUnitType>;

       public:

         typedef TCFDivisionTreeItem<LevelDataType, CompositeUnitType> TItem;
         typedef vector<TItem>                                       TItems;
         typedef TItem                                              *PItem;
         typedef vector<PItem>                                       PItems;

         typedef CompositeUnitType                                   TUnit;
         typedef CompositeUnitType                                  *PUnit;
         typedef vector<PUnit>                                       PUnits;


           typedef TFrequencyTable<TChar>              TCharFrequencyTable;

       private:

          TItems                  _Items;
          TCharFrequencyTable     _CFTable;


          TUInt _LevelsCounter()
          {
              if (_Items.size()) return _Items[0]._LevelsCounter() + 1;
              else return 1;
          };

          TUInt _ItemsOnLevel(const TUInt & tLevel)
          {
              if (tLevel == 0) return _Items.size();

              TUInt count = 0;
                 for (TUInt i=0; i<_Items.size(); i++)
                    count += _Items[i]._ItemsOnLevel(tLevel-1);

          return count;
          };

          void _GetLevelItems(const TUInt & tLevel, PItems *tTarget)
          {
              if (tLevel == 0)
              {
                   for (TUInt i=0; i<_Items.size(); i++)
                      tTarget->push_back(&_Items[i]);

              return;
              };

              if (!_Items.size()) throw EOutOfLevels();

              for (TUInt i=0; i<_Items.size(); i++)
                  _Items[i]._GetLevelItems(tLevel-1, tTarget);
          };

          TBool _IsLastLevel()
          {
              return ((!_Items.size()) ? true : false);
          };

          void _GetLastLevelItems(PItems *tTarget)
          {
               if (_Items.size())
               {
                   if (_Items[0]._IsLastLevel())
                   {
                       for (TUInt i=0; i<_Items.size(); i++)
                          tTarget->push_back(&_Items[i]);

                       return;
                   }
                   else
                       for (TUInt i=0; i<_Items.size(); i++)
                           _Items[i]._GetLastLevelItems(tTarget);
               }

          tTarget->push_back(this);
          };

          void _GetLevelUnits(const TUInt & tLevel, PUnits *tTarget)
          {
              if (tLevel == 0)
              {
                   for (TUInt i=0; i<_Items.size(); i++)
                      tTarget->push_back(&_Items[i]._CompositeUnit);

              return;
              };

              if (!_Items.size()) throw EOutOfLevels();

              for (TUInt i=0; i<_Items.size(); i++)
                  _Items[i]._GetLevelUnits(tLevel-1, tTarget);
          };

          TCFDivisionTreeItem & _AddItem(const TUInt & tLevelDeep, const TCFDivisionTreeItem & tItem)
          {
               if (tLevelDeep)
               {
                    if (!Count()) throw ENoChildItems();
                    return _Items[_Items.size()-1]._AddItem(tLevelDeep-1, tItem);
               }

                 _Items.push_back(tItem);
          return _Items[_Items.size()-1];
          };

          void _Clear()
          {
              for (TUInt i=0; i<_Items.size(); i++)
                 _Items[i]._Clear();

          _Items.clear();
          };

       public:

          TBool IsValidIndex(const TUInt & tIndex) { return (tIndex >= _Items.size()) ? false : true; };


          LevelDataType          LevelData    ()  const { return _LevelData; };
          void                   LevelData    (   const LevelDataType & tLevelData)  { _LevelData = tLevelData; };
          CompositeUnitType      CompositeUnit()  const { return _CompositeUnit; };
          void                   CompositeUnit(   const CompositeUnitType & tCompositeUnit)  { _CompositeUnit = tCompositeUnit; };

          TUInt LevelsCount()   { return _LevelsCounter()-1; }
          TUInt Count()  const  { return _Items.size();    }


          TItems  &  Items()  { return _Items; };

          TCFDivisionTreeItem & AddItem(const TUInt & tLevelDeep, const TCFDivisionTreeItem & tItem)
             {   return  _AddItem(tLevelDeep, tItem);   };


                        TCFDivisionTreeItem * FirstChild()
                        {
                            if (!Count()) throw ENoChildItems();
                            return &_Items[0];
                        };

                        TCFDivisionTreeItem * LastChild()
                        {
                            if (!Count()) throw ENoChildItems();
                            return & _Items[Count()-1];
                        };


          inline TCFDivisionTreeItem<LevelDataType, CompositeUnitType> & operator [] (const TUInt & tIndex)
          {
             if (IsValidIndex(tIndex)) return _Items[tIndex];
             else throw EOutOfRange();
          };


          TCharFrequencyTable    CFTable() {return _CFTable;};
          void                   CFTable(const TCharFrequencyTable & tCFTable) { _CFTable = tCFTable; };


          TCFDivisionTreeItem(const LevelDataType & tLevelData, const CompositeUnitType & tCompositeUnit) : TDivisionTreeItem<LevelDataType, CompositeUnitType>(tLevelData, tCompositeUnit){};

          TCFDivisionTreeItem(const LevelDataType & tLevelData, const CompositeUnitType & tCompositeUnit, const TCharFrequencyTable & tCFTable)
            : TDivisionTreeItem(tLevelData, tCompositeUnit), _CFTable(tCFTable) {};


       private:

          TCFDivisionTreeItem() {};
   };

////////////////////////////////////////////////////////////////////////////////
///Специальные классы, позволяющие интерпретировать дерево в виде слоев/////////
////////////////////////////////////////////////////////////////////////////////

//Класс, предоставляющий интерфейс работы с уровнем.
   template <class LevelDataType, class CompositeUnitType> class TCFTreeLevelInfo : public TErrorSpecificators
   {
       public:
           typedef TCFDivisionTreeItem<LevelDataType, CompositeUnitType> TItem;

       private:
           TUInt _Level;

           TItem * _Tree;

           TCFTreeLevelInfo(){};
       public:

/*
Умеет делать со своим слоем следующее:

          TItem::PItems PItems(const TRangeItem & tRange);
          TItem::PItems PItems();
          TItem::PUnits    PUnits(const TRangeItem & tRange);
          TItem::PUnits    PUnits();
          CompositeUnitType         ComposeUnit(const TRangeItem & tRange);
          inline TItem * operator[] (const TUInt & tIndex);
          TUInt Count();
*/

          TItem::PItems PItems(const TRangeItem & tRange)
          {
              TItem::PItems items;

                  _Tree->_GetLevelItems(_Level, &items);

              if (tRange.To()>items.size()) throw EOutOfRange();

              TItem::PItems range(&items[tRange.From()], &items[tRange.To()+1]);

              items.clear();
              return range;
          };

          TItem::PItems PItems()
          {
              TItem::PItems items;
                 _Tree->_GetLevelItems(_Level, &items);
              return items;
          };

          TItem::PUnits    PUnits(const TRangeItem & tRange)
          {
             TItem::PUnits units;

                 _Tree->_GetLevelUnits(_Level, &units);

              if (tRange.To()>units.size()) throw EOutOfRange();

              TItem::PUnits range(&units[tRange.From()], &units[tRange.To()+1]);

              units.clear();
              return range;
          };

          TItem::PUnits    PUnits()
          {
              TItem::PUnits units;
                 _Tree->_GetLevelUnits(_Level, &units);
              return units;
          };

          TItem::TUnit         ComposeUnit(const TRangeItem & tRange)
          {
              TItem::PUnits units = PUnits(tRange);
              TItem::TUnit ResUnit = *units[0];

               for (TUInt i=1; i<units.size(); i++)
                    ResUnit = ResUnit + *units[i];

          return ResUnit;
          };

          inline TItem * operator[] (const TUInt & tIndex)
          {
              TItem::PItems items = PItems();

              if (tIndex>=items.size()) throw EOutOfRange();

                 return items[tIndex];
          };


          TUInt Count() { return _Tree->_ItemsOnLevel(_Level); };

          TItem::TCharFrequencyTable  CFTable()
          {
               TItem::PItems items;
                   _Tree->_GetLastLevelItems(&items);

               TItem::TCharFrequencyTable table;

               for (TUInt i=0; i<items.size(); i++)
                  table << items[i]->CFTable();

          items.clear();
          return table;
          };


          TItem::TCharFrequencyTable  CFTable(const TRangeItem & tRange)
          {
               TItem::PItems items;
                   _Tree->_GetLastLevelItems(&items);

               if (tRange.To()>items.size()) throw EOutOfRange();

               TItem::PItems range(&items[tRange.From()], &items[tRange.To()+1]);
                   items.clear();

               TItem::TCharFrequencyTable table;

               for (TUInt i=0; i<range.size(); i++)
                  table << range[i]->CFTable();

          range.clear();
          return table;
          };


          TCFTreeLevelInfo(TItem * tTree, const TUInt & tLevel) : _Tree(tTree), _Level(tLevel){};
         ~TCFTreeLevelInfo(){};
   };

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//-------------- Навигация по дереву, представленному в виде слоев -------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

   template <class LevelDataType, class CompositeUnitType> class TCFTreeLevel : public TErrorSpecificators
   {
       public:
           typedef TCFDivisionTreeItem<LevelDataType, CompositeUnitType> TItem;
           typedef TItem                                              *PItem;
           typedef TItem::PItems                                       PItems;
           typedef TItem::TUnit                                        TUnit;
           typedef TItem::PUnit                                        PUnit;
           typedef TItem::PUnits                                       PUnits;

       private:

           PItem     _Tree;
           vector<TCFTreeLevelInfo<LevelDataType, CompositeUnitType> >   _LevelsInfo;


           void _CreateLevelsInfo(const TUInt & tLevel)
           {
           if ( tLevel >= _Tree->LevelsCount()) throw EOutOfLevels();

               for (TUInt i=_LevelsInfo.size(); i<=tLevel; i++)
                   _LevelsInfo.push_back(TCFTreeLevelInfo<LevelDataType, CompositeUnitType>(_Tree, i));
           };


           TUInt _ReduceLevelLeft(const TUInt & tLevel1, const TUInt & tIndex)
           {
                TUInt level = tLevel1;
                TUInt leftindex = tIndex;
                PItems pItems;
                PItem  parent;

                while (level < (_Tree->LevelsCount()-1))
                {
                parent = (*this)[level][leftindex];
                   if (!parent->Count()) throw EEmptyLevels();

                    level++;

                    pItems = (*this)[level].PItems();


                    leftindex = distance(pItems.begin(), find(pItems.begin(), pItems.end(), &(*parent)[0]));
                };

           return leftindex;
           };

           TUInt _ReduceLevelRight(const TUInt & tLevel1, const TUInt & tIndex)
           {
                TUInt level = tLevel1;
                TUInt rightindex = tIndex;
                PItems pItems;
                PItem  parent;

                while (level < (_Tree->LevelsCount()-1))
                {
                parent = (*this)[level][rightindex];
                   if (!parent->Count()) throw EEmptyLevels();

                    level++;

                    pItems = (*this)[level].PItems();

                    rightindex = distance(pItems.begin(), find(pItems.begin(), pItems.end(), &(*parent)[parent->Count()-1]));
                };

           return rightindex;
           };


       public:


          TItem::TCharFrequencyTable CrossLevelCFTable(const TUInt & tLevel1, const TUInt & tIndex1, const TUInt & tLevel2, const TUInt & tIndex2)
          {
              return (*this)[_Tree->LevelsCount()-1].CFTable(TRangeItem(_ReduceLevelLeft(tLevel1, tIndex1), _ReduceLevelRight(tLevel2, tIndex2)));
          };


          TItem::TUnit          CrossLevelComposeUnit(const TUInt & tLevel1, const TUInt & tIndex1, const TUInt & tLevel2, const TUInt & tIndex2)
          {
              return (*this)[_Tree->LevelsCount()-1].ComposeUnit(TRangeItem(_ReduceLevelLeft(tLevel1, tIndex1), _ReduceLevelRight(tLevel2, tIndex2)));
          };

          TItem::PUnits            CrossLevelPUnits(const TUInt & tLevel1, const TUInt & tIndex1, const TUInt & tLevel2, const TUInt & tIndex2)
          {
              return (*this)[_Tree->LevelsCount()-1].PUnits(TRangeItem(_ReduceLevelLeft(tLevel1, tIndex1), _ReduceLevelRight(tLevel2, tIndex2)));
          };

          TItem::PItems         CrossLevelPItems(const TUInt & tLevel1, const TUInt & tIndex1, const TUInt & tLevel2, const TUInt & tIndex2)
          {
              return (*this)[_Tree->LevelsCount()-1].PItems(TRangeItem(_ReduceLevelLeft(tLevel1, tIndex1), _ReduceLevelRight(tLevel2, tIndex2)));
          };



          inline TCFTreeLevelInfo<LevelDataType, CompositeUnitType> & operator[] (const TUInt & tLevel)
          {
               _CreateLevelsInfo(tLevel);
               return _LevelsInfo[tLevel];
          };

          inline TCFTreeLevelInfo<LevelDataType, CompositeUnitType> & operator[] (const TCFTreeLevelsDefiner & tLevelDefiner)
          {
              if (tLevelDefiner == tlm_FirstLevel)
              {
                  _CreateLevelsInfo(0);
                  return _LevelsInfo[0];
              }
              else
                 if (tLevelDefiner == tlm_LastLevel)
                 {
                     _CreateLevelsInfo(_Tree->LevelsCount()-1);
                     return _LevelsInfo[_Tree->LevelsCount()-1];
                 }
                 else
                    if (tLevelDefiner == tlm_LastButOneLevel)
                    {
                        _CreateLevelsInfo(_Tree->LevelsCount()-2);
                        return _LevelsInfo[_Tree->LevelsCount()-2];
                    };

          throw EOutOfRange();
          };


          TCFTreeLevel(TItem * tTree) : _Tree(tTree) {};
         ~TCFTreeLevel() { _LevelsInfo.clear(); };

       private:

           TCFTreeLevel(){};
   };



#endif

/*
   Пример использования 1:


#include "UParSentWordFSM.h"
#include "FiniteStateMachine.h"
#include "CStateMachineDescriptor.h"
#include "CFiniteStateMachineManager.h"
#include "CTextStringWrapper.h"
#include <time.h>

   ParSentWordFSM::TCFCustomUnitDivisionTreeItem   Tree(0, TRangeItem(1, Memo1->Text.Length()));

   ParSentWordFSM::TParSenWordDescriptor D = ParSentWordFSM::Descriptor(&Tree);

#define TState ParSentWordFSM::TState
#define TEvent ParSentWordFSM::TEvent
#define TFSMachine SFiniteStateMachine<TState, TEvent, SOnEnterFunctor<TState, TEvent>, SThrowStrategy<TEvent> >
#define TFSMM  TFiniteStateMachineManager<TEvent, TFSMachine, ParSentWordFSM::TParSenWordDescriptor, TTextStringWrapper>

     TTextStringWrapper TextWrapper(Memo1->Text);

     TFSMM fsmManager(D, TextWrapper);

time_t t1, t2;

       t1 = time(NULL);
            fsmManager.Process();
       t2 = time(NULL);

       Memo4->Lines->Add("Done.");
       Memo4->Lines->Add("Seconds: " + IntToStr(t2-t1));

TCFTreeLevel<TSFloat, TRangeItem>  Levels(&Tree);

       Memo4->Lines->Add("Tree.LevelsCount = " + IntToStr(Tree.LevelsCount()));
       Memo4->Lines->Add("Level 0 : Paragraphs. Count = " + IntToStr(Levels[0].Count()));
       Memo4->Lines->Add("Level 1 : Sentences.  Count = " + IntToStr(Levels[1].Count()));
       Memo4->Lines->Add("Level 2 : Words.      Count = " + IntToStr(Levels[2].Count()));


ParSentWordFSM::TCFCustomUnitDivisionTreeItem::PItems pItems;
       pItems = Levels[2].PItems();


TTextString S;
TFrequencyTable<TChar> FTable;
TUInt i;
TSInt j;


       for (i=0; i<pItems.size(); i++)
       {
           S = TextWrapper.SubString(pItems[i]->CompositeUnit().From(), pItems[i]->CompositeUnit().Length());
           Memo3->Lines->Add(S);
       };


       for (i=0; i<pItems.size(); i++)
       {
           S = TextWrapper.SubString(pItems[i]->CompositeUnit().From(), pItems[i]->CompositeUnit().Length());
           FTable << ftm_Clear;

              for (j=1; j<=S.Length(); j++)
                  FTable << S[j];

       pItems[i]->CFTable(FTable);
       };


  FTable << ftm_Clear << Levels[0].CFTable();
     Memo4->Lines->Add("Level 0: CFTable.Count = " + IntToStr(FTable.Count()));
  FTable << ftm_Clear << Levels[1].CFTable();
     Memo4->Lines->Add("Level 1: CFTable.Count = " + IntToStr(FTable.Count()));
  FTable << ftm_Clear << Levels[2].CFTable();
     Memo4->Lines->Add("Level 2: CFTable.Count = " + IntToStr(FTable.Count()));

  FTable << ftm_Clear << Levels[0].CFTable();
TFrequencyTable<TChar>::TFrequencyVector fVector = FTable.GetFrequencyVector();

     for (TUInt i=0; i<fVector.size(); i++)
       Memo3->Lines->Add(TTextString(fVector[i].Key) + "   " + IntToStr(fVector[i].Count));

#undef TState
#undef TEvent
#undef TFSMachine
#undef TFSMM






   Пример использования 2:

   ParSentWordFSM::TCFCustomUnitDivisionTreeItem   Tree(0, TRangeItem(1, Memo1->Text.Length()));

   ParSentWordFSM::TParSenWordDescriptor D = ParSentWordFSM::Descriptor(&Tree);

#define TState ParSentWordFSM::TState
#define TEvent ParSentWordFSM::TEvent
#define TFSMachine SFiniteStateMachine<TState, TEvent, SOnEnterFunctor<TState, TEvent>, SThrowStrategy<TEvent> >
#define TFSMM  TFiniteStateMachineManager<TEvent, TFSMachine, ParSentWordFSM::TParSenWordDescriptor, TTextStringWrapper>

     TTextStringWrapper TextWrapper(Memo1->Text);

     TFSMM fsmManager(D, TextWrapper);

time_t t1, t2;

       t1 = time(NULL);
            fsmManager.Process();
       t2 = time(NULL);

       Memo3->Lines->Add("Done.");
       Memo3->Lines->Add("Seconds: " + IntToStr(t2-t1));


ParSentWordFSM::TCFCustomUnitTreeLevel  Levels(&Tree);

       Memo3->Lines->Add("Level 0 : Paragraphs. Count = " + IntToStr(Levels[0].Count()));
       Memo3->Lines->Add("Level 1 : Sentences.  Count = " + IntToStr(Levels[1].Count()));
       Memo3->Lines->Add("Level 2 : Words.      Count = " + IntToStr(Levels[2].Count()));

TCFTreeLevel<TUInt, TRangeItem>::PUnits rCompositeUnits;
       rCompositeUnits = Levels[0].PUnits();

//Тестирование функций PItems и PUnits класса TCFTreeLevelInfo.
//В них производится инициализация вектора диапазоном другого вектора.
//Возникает вопрос о границах диапазона. Как выясняется, границы имеют следующую
//структуру:  [from, to).

//Получаем все указатели на элементы 2-го уровня:
ParSentWordFSM::TCFCustomUnitTreeLevel::PItems pItems;
       pItems = Levels[2].PItems();

//Получаем диапазон указателей, подразумевая, что должны быть получены все -
//[ 0, pItems.size() ).
ParSentWordFSM::TCFCustomUnitTreeLevel::PItems pItems2;
       pItems2 = Levels[2].PItems(TRangeItem(0, pItems.size()-1));


//Сравниваем количество элементов первого и второго массивов указателей:
       Memo4->Lines->Add(IntToStr(pItems.size()) + "  " + IntToStr(pItems2.size()));

//Для чистоты эксперимента пытаемся получить доступ к самим элементам.
//Если run-time ошибки не возникает, значит, все указатели верные.
       for (TUInt i=0; i<pItems2.size(); i++)
       pItems2[i]->Count();

//Функция PUnits действует аналогично.

#undef TState
#undef TEvent
#undef TFSMachine
#undef TFSMM

*/
