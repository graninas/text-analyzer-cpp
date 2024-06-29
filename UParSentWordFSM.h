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
#ifndef UParSentWordFSMH
#define UParSentWordFSMH
//---------------------------------------------------------------------------

#include "CStateMachineDescriptor.h"
#include "CCFDivisionTreeItem.h"
#include "CCharsSetEvent.h"
#include "CFunctionalState.h"
#include "CRangeItem.h"

#include "UConstants.h"

namespace ParSentWordFSM
{                                          

    class   TState;
    typedef TCharsSetEvent TEvent;

    typedef TSFloat TCFLevelDataType;
    typedef TRangeItem TUnitType;

    typedef TCFDivisionTreeItem<TCFLevelDataType, TUnitType>  TCFCustomUnitDivisionTreeItem;
    typedef TCFTreeLevel<TCFLevelDataType, TUnitType>         TCFCustomUnitTreeLevel;

    typedef void (*TFuncPtr)(TCFCustomUnitDivisionTreeItem *, const TEvent &);
    typedef TStateMachineDescriptor<TState, TEvent> TParSenWordDescriptor;

/*Класс используемого состояния.*/

   class TState : public TFunctionalState<TEvent, TTextString>
   {
        private:

            TFuncPtr                      _Function;
            TCFCustomUnitDivisionTreeItem  *  _TargetTree;

        public:

            void OnEnter(const TState & tStateFrom, const TEvent & tEvent)
            {
                 _Function(_TargetTree, tEvent);
            };

          TState(const TTextString & tName, TFuncPtr tFunc, TCFCustomUnitDivisionTreeItem * tTargetTree)
            : TFunctionalState<TEvent, TTextString> (tName, sat_None), _Function(tFunc), _TargetTree(tTargetTree){};
   };

/*--------------------------------------
     Функции, работающие с деревом.
--------------------------------------*/

      void FEmpty(TCFCustomUnitDivisionTreeItem * tItem, const TEvent & tEvent)
      {
          return;
      };

      void FOpenParagraph(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
          TCFCustomUnitDivisionTreeItem NewItem(0, TRangeItem(tEvent.Iterator(), tEvent.Iterator()));
            tTree->AddItem(0, NewItem);
      };

      void FOpenSentence(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
          TCFCustomUnitDivisionTreeItem NewItem(1, TRangeItem(tEvent.Iterator(), tEvent.Iterator()));
            tTree->AddItem(1, NewItem);
      };

      void FOpenWord(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
          TCFCustomUnitDivisionTreeItem NewItem(2, TRangeItem(tEvent.Iterator(), tEvent.Iterator()));
            tTree->AddItem(2, NewItem);
      };

      void FOpenAll(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
           FOpenParagraph(tTree, tEvent);
           FOpenSentence(tTree, tEvent);
           FOpenWord(tTree, tEvent);
      };

      void FCloseWord(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
           TRangeItem Unit = (((tTree->LastChild())->LastChild())->LastChild())->CompositeUnit();
                   Unit.To(tEvent.Iterator()-1);   //-1 потому, что событие - исключающее.
                             (((tTree->LastChild())->LastChild())->LastChild())->CompositeUnit(Unit);
      };

      void FCloseSentence(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
           TRangeItem Unit = ((tTree->LastChild())->LastChild())->CompositeUnit();
                   Unit.To(tEvent.Iterator()-1);
                             ((tTree->LastChild())->LastChild())->CompositeUnit(Unit);
      };

      void FCloseParagraph(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
           TRangeItem Unit = (tTree->LastChild())->CompositeUnit();
                   Unit.To(tEvent.Iterator()-1);
                             (tTree->LastChild())->CompositeUnit(Unit);
      };

      void FOpenSentenceOpenWord(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
           FOpenSentence(tTree, tEvent);
           FOpenWord(tTree, tEvent);
      };

      void FCloseSentenceOpenSentenceOpenWord(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
           FCloseSentence(tTree, tEvent);
           FOpenSentence(tTree, tEvent);
           FOpenWord(tTree, tEvent);
      };

      void FCloseAll(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
          FCloseWord(tTree, tEvent);
          FCloseSentence(tTree, tEvent);
          FCloseParagraph(tTree, tEvent);
      };

      void FCloseSentenceCloseParagraph(TCFCustomUnitDivisionTreeItem * tTree, const TEvent & tEvent)
      {
          FCloseSentence(tTree, tEvent);
          FCloseParagraph(tTree, tEvent);
      };

/*------------------------------------------------------------------------------
   Порождающий класс.
------------------------------------------------------------------------------*/

TParSenWordDescriptor Descriptor(TCFCustomUnitDivisionTreeItem * tTree)
{

TParSenWordDescriptor D(TState("q0", FEmpty, tTree), "Paragraphs, Sentences, Words");

     D << TState("q0",  FEmpty, tTree)
       << TState("q1",  FOpenAll, tTree)
       << TState("q2",  FOpenSentenceOpenWord, tTree)
       << TState("q3",  FOpenWord, tTree)
       << TState("q4",  FEmpty, tTree)
       << TState("q5",  FCloseWord, tTree)
       << TState("q6",  FCloseSentence, tTree)
       << TState("q7",  FCloseSentenceOpenSentenceOpenWord, tTree)
       << TState("q8",  FEmpty, tTree)
       << TState("q9",  FEmpty, tTree)
       << TState("q10", FCloseWord, tTree)
       << TState("q11", FCloseAll, tTree)
       << TState("q12", FCloseSentenceCloseParagraph, tTree)
       << TState("q13", FCloseParagraph, tTree)
       << TState("q14", FEmpty, tTree);

     D << TEvent("WinParagraph", cWinParagraph)
       <<"q0"<<"q11"<<"q11"<<"q11"<<"q11"<<"q12"<<"q12"<<"q11"<<"q12"<<"q13"<<"q12"<<"q0"<<"q0"<<"q0"<<"q12";
     D << TEvent("SentenceEnd", cSentenceEnd)
       <<"q0"<<"q10"<<"q10"<<"q10"<<"q10"<<"q14"<<"q14"<<"q10"<<"q14"<<"q9"<<"q14"<<"q0"<<"q0"<<"q0"<<"q14";
     D << TEvent("Letters", cLetters + cDigits)
       <<"q1"<<"q4"<<"q4"<<"q4"<<"q4"<<"q3"<<"q2"<<"q4"<<"q3"<<"q2"<<"q7"<<"q1"<<"q1"<<"q1"<<"q7";
     D << TEvent("Space", cSpace + cTab)
       <<"q0"<<"q5"<<"q5"<<"q5"<<"q5"<<"q8"<<"q9"<<"q5"<<"q8"<<"q9"<<"q6"<<"q0"<<"q0"<<"q0"<<"q6";
     D << TEvent("PunctMarks and other symbols", TCharsSet(cPrintable) >> cWinParagraph >> cSentenceEnd >> cLetters >> cDigits >> cSpace >> cTab)
       <<"q0"<<"q5"<<"q5"<<"q5"<<"q5"<<"q8"<<"q9"<<"q5"<<"q8"<<"q9"<<"q14"<<"q0"<<"q0"<<"q0"<<"q14";
     D << TEvent("EndSign", TCharsSet(CTextStringEndSign))
       <<"q0"<<"q11"<<"q11"<<"q11"<<"q11"<<"q12"<<"q13"<<"q11"<<"q12"<<"q13"<<"q12"<<"q0"<<"q0"<<"q0"<<"q12";


return D;
};




};  //End of namespace.

#endif


/*
   Протестировано. Работает. КА необходимо дополнить для случая "-".


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
