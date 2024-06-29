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
#ifndef CCharsSetEventH
#define CCharsSetEventH
//---------------------------------------------------------------------------

#include "CNamedSetItem.h"
#include "CCharsSet.h"

class TCharsSetEvent
{
public:
	typedef TNamedSetItem<TTextString, TCharsSet>	TNamedCharsSetItem;
	typedef TCharsSet::TElementType  				TSubEvent;

private:

		TNamedCharsSetItem _Item;
		TUInt _Iterator;

public:

		TTextString Name() const;
		TNamedCharsSetItem * Item();
		TUInt Iterator()const;


		TCharsSetEvent & operator<< (const TUInt & tIterator);
		TBool operator == (const TCharsSetEvent & tEvent);
		TBool operator == (const TNamedCharsSetItem & tNamedSetItem);

		friend TBool operator == (const TCharsSetEvent & tEvent1, const TCharsSetEvent & tEvent2)
		{
			return (tEvent1._Item == tEvent2._Item) || (tEvent1._Item.IsSubset(tEvent2._Item.Set())) ? true : false;
		};


		TCharsSetEvent(const TNamedCharsSetItem & tItem) : _Item(tItem), _Iterator(0){};
		TCharsSetEvent(const TTextString & tEventName, const TCharsSet & tCharsSet) : _Item(TNamedCharsSetItem(tEventName, tCharsSet)), _Iterator(0){};
		TCharsSetEvent(const TTextString & tEventName, const TCharsSet::TElementType & tElements) : _Item(TNamedCharsSetItem(tEventName, tElements)), _Iterator(0){};
		TCharsSetEvent() : _Item("Event", ""){};

		TCharsSetEvent(const TCharsSet & tCharsSet,const TUInt & tIterator) : _Item(TNamedCharsSetItem(tCharsSet.Elements(), tCharsSet)), _Iterator(tIterator){};
		TCharsSetEvent(const TCharsSet::TElementType & tSubEvent, const TUInt & tIterator) : _Item("SubEvent", tSubEvent), _Iterator(tIterator){};
};


/*
Работает. Протестировано.


Пример использования.

TVCLFileDataLoader FDL;
TRawDataItem RDI;

if (OpenDialog1->Execute())
  RDI = TRawDataItem(&FDL, OpenDialog1->FileName);

RDI.Unvirtualize();

Edit1->Text = RDI.Alias();
Memo1->Text = RDI.Text();




  #define FSMStateTypeTTextString
  #define FSMEventTypeTCharsSetEvent

  typedef TCharsSetModificator TMod;
  TCharsSet CS;

  TCharsSetEvent CREvent("CR", (CS << man_CR));
 //Memo3->Text = CS.Elements();
  TCharsSetEvent LFEvent("LF", (CS << man_LF));
 //Memo3->Text = CS.Elements();
  TCharsSetEvent TextEvent("Text", (CS << man_Text) >> TMod(mod_WinParagraph) );

 Memo3->Text = CS.Elements();

  SFiniteStateMachine< FSMStateType,
  FSMEventType,
  SEmptyFunctor<FSMStateType, FSMEventType>,
  SThrowStrategy<FSMEventType>
>
  MyMachine(

 FSMBEGIN( "q0" ) //Событие "Пусто"

 FSMSTATES"q0" << "q1" << "q2" << "q3" << "q4" << "q5"
 FSMEVENT(CREvent) "q2" << "q2" << "q4" << "q5" << "q4" << "q5"
 FSMEVENT(LFEvent) "q3" << "q3" << "q5" << "q4" << "q4" << "q5"
 FSMEVENT(TextEvent)  "q1" << "q1" << "q4" << "q4" << "q4" << "q5"


 FSMEND
);


 TTextString S = Memo1->Text;
 TTextString tmp2;
 Edit2->Text = MyMachine.GetCurrentState();

 Memo2->Text = "";

  for (TSInt i=1; i<=S.Length(); i++)
  {
  MyMachine << S[i];
  };


  Memo2->Text = Memo1->Text;

  #undef FSMStateType
  #undef FSMEventType

*/

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

/*
Пример использования  TSTLSetEvent


  #define FSMStateTypeTTextString
  #define FSMEventTypeTSTLSetEvent

TSTLSetEvent CREvent("CR", cCR.c_str()), LFEvent("LF", cLF.c_str()), TextEvent("Text", cText.c_str());

  SFiniteStateMachine< FSMStateType,
  FSMEventType,
  SEmptyFunctor<FSMStateType, FSMEventType>,
  SThrowStrategy<FSMEventType>
>
  MyMachine(

 FSMBEGIN( "q0" ) //Событие "Пусто"

 FSMSTATES"q0" << "q1" << "q2" << "q3" << "q4" << "q5"
 FSMEVENT(CREvent) "q2" << "q2" << "q4" << "q5" << "q4" << "q5"
 FSMEVENT(LFEvent) "q3" << "q3" << "q5" << "q4" << "q4" << "q5"
 FSMEVENT(TextEvent)  "q1" << "q1" << "q4" << "q4" << "q4" << "q5"


 FSMEND
);


 TTextString S = Memo1->Text;
 TTextString tmp2;
 Edit2->Text = MyMachine.GetCurrentState();
 TSInt ParsCount = 0;
 TSInt PrevI = 1;

 Memo2->Text = "";

 string STLString;

  for (TSInt i=1; i<=S.Length(); i++)
  {
  MyMachine << S[i];

  if (MyMachine.GetCurrentState() == "q4")
  {
 Memo2->Text = Memo2->Text + S.SubString(PrevI, i-1);
 ParsCount++;
  PrevI = i-1;
  MyMachine << mmResetMachine;
  }

  if (MyMachine.GetCurrentState() == "q5")
  {
 Memo2->Text = Memo2->Text + S.SubString(PrevI, i);
 ParsCount++;
  PrevI = i;
  MyMachine << mmResetMachine;
  }
  };

  Label1->Caption = IntToStr(ParsCount);
  Memo2->Text = Memo1->Text;


  #undef FSMStateType
  #undef FSMEventType
};



*/



#endif

