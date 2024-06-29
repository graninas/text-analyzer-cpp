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
#ifndef CFleschReadingComfortabilityH
#define CFleschReadingComfortabilityH
//---------------------------------------------------------------------------
#include "UParSentWordFSM.h"
using namespace ParSentWordFSM;

#include "CSyllablesCounter.h"
#include "CTextStringWrapper.h"
#include "CFiniteStateMachineManager.h"
#include "FiniteStateMachine.h"
#include "CTextDivisionDescriptor.h"

      class TEnglishFleschCalculator
      {
           public:

               TSFloat Calculate(const TSFloat & tAverageWordsPerSentence, const TSFloat & tAverageSyllablesPerWord);

      TEnglishFleschCalculator(){};
      };

      class TRussianFleschCalculator
      {
           public:

               TSFloat Calculate(const TSFloat & tAverageWordsPerSentence, const TSFloat & tAverageSyllablesPerWord);

      TRussianFleschCalculator(){};
      };


      template <class FunctionCalculatorType> class TFleschReadingComfortability
      {
          private:

               FunctionCalculatorType _Calculator;


               void  _GetParSentWordTree(TCFCustomUnitDivisionTreeItem * tTargetTreeItem, const TTextString & tText)
               {
                   TParSenWordDescriptor D = Descriptor(tTargetTreeItem);

                        #define TState ParSentWordFSM::TState
                        #define TEvent ParSentWordFSM::TEvent
                        #define TFSMachine FSM::SFiniteStateMachine<TState, TEvent, FSM::SOnEnterFunctor<TState, TEvent>, FSM::SThrowStrategy<TEvent> >
                        #define TFSMM  TFiniteStateMachineManager<TEvent, TFSMachine, ParSentWordFSM::TParSenWordDescriptor, TTextStringWrapper>

                        TTextStringWrapper TextWrapper(tText);

                        TFSMM fsmManager(D, TextWrapper);
                              fsmManager.Process();

                        #undef TState
                        #undef TEvent
                        #undef TFSMachine
                        #undef TFSMM
               };

               void  _CalcAverageValues(TCFCustomUnitDivisionTreeItem & tTree, TSFloat * tASL, TSFloat * tAWL, const TTextString & tText)
               {
                 TCFTreeLevel<TCFLevelDataType, TRangeItem> Levels(&tTree);
                 TCFTreeLevel<TCFLevelDataType, TRangeItem>::PItems pItems = Levels[tlm_LastButOneLevel].PItems();  //Предложения

                      TSFloat ASL = 0;
                      TSFloat AWL = 0;

                          for (TUInt i=0; i<pItems.size(); i++)
                             ASL += pItems[i]->Count();

                       ASL /= TSFloat(pItems.size());



                 pItems = Levels[tlm_LastLevel].PItems();      //Слова
                     TTextString word;
                     TUChar  syllablesCount;

                 TSyllablesCounter SyllablesCounter;
                 TRangeItem rangeItem;

                     for (TUInt i=0; i<pItems.size(); i++)
                     {
                     rangeItem = pItems[i]->CompositeUnit();
                         word = tText.SubString(rangeItem.From(), rangeItem.Length());
                         syllablesCount = SyllablesCounter.SyllablesCount(word);

                         AWL += syllablesCount;
                     };

                AWL /= TSFloat(pItems.size());

               *tASL = ASL;
               *tAWL = AWL;
               };



          public:

              TSFloat ReadingComfortabilityFunction(const TSFloat & tAverageWordsPerSentence, const TSFloat & tAverageSyllablesPerWord)
              {
                  return   _Calculator.Calculate(tAverageWordsPerSentence, tAverageSyllablesPerWord);
              };


             
              TSFloat FleschReadingComfortability(const TCFCustomUnitDivisionTreeItem * tTextDivisionDescriptor, const TTextDataProvider * tTextProvider)
              {
                   TTextString                  text = tTextProvider->SubString(tTextDivisionDescriptor->CompositeUnit().From(), tTextDivisionDescriptor->CompositeUnit().Count());
                   TCFCustomUnitDivisionTreeItem  tree(0, TRangeItem(1, text.Length()));

                       TSFloat averageSentencesLength;
                       TSFloat averageSyllablesCount;

                      _GetParSentWordTree(&tree, text);
                      _CalcAverageValues(tree, &averageSentencesLength, &averageSyllablesCount, text);
                      
              return  _Calculator.Calculate(averageSentencesLength, averageSyllablesCount);
              };

              TSFloat FleschReadingComfortability(const TTextDataProvider * tTextProvider)
              {
              TTextString  text = tTextProvider->Text();
                       if (text.Length() == 0) return 0.0f;

                   TCFCustomUnitDivisionTreeItem tree(0, TRangeItem(1, text.Length()));

                       TSFloat averageSentencesLength;
                       TSFloat averageSyllablesCount;

                      _GetParSentWordTree(&tree, text);
                      _CalcAverageValues(tree, &averageSentencesLength, &averageSyllablesCount, text);

              return  _Calculator.Calculate(averageSentencesLength, averageSyllablesCount);
              };


          TFleschReadingComfortability(){};
      };

/*

     Протестировано. Работает.





*/



#endif
