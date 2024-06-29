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

#include <vcl.h>
#pragma hdrstop

#include "fTestingTable.h"

#include "CRawDataItem.h"
#include "CVCLFileDataLoader.h"

#include "CNamedSetsContainer.h"

#include "FiniteStateMachine.h"

#include "CTextsController.h"

#include "VCLConstants.h"
using namespace FSM;

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTestingTable *TestingTable;

#include "CTextStringWrapper.h"
TTextStringWrapper TextWrapper;
TTextsController TextsController2;

TTextString curAlias;

#include "DRangeMapsEqualifer.h"
TRangeMapsEqualifer rme;


//---------------------------------------------------------------------------
__fastcall TTestingTable::TTestingTable(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TTestingTable::Button4Click(TObject *Sender)
{
   TVCLFileDataLoader FDL;

   if (OpenDialog1->Execute())
   if (OpenDialog1->FileName != "")
       TextsController2.LoadText(OpenDialog1->FileName, &FDL, &curAlias);

   Memo1->Text = TextsController2[curAlias]->Text();
   LBTitles->Items->Add(curAlias);
//   GetTextsList();
}
//---------------------------------------------------------------------------

#include "UParSentWordFSM.h"
#include "FiniteStateMachine.h"
#include "CStateMachineDescriptor.h"
#include "CFiniteStateMachineManager.h"
#include <time.h>

void __fastcall TTestingTable::Button2Click(TObject *Sender)
{
TextWrapper = TextsController2[curAlias]->Text();
   ParSentWordFSM::TCFCustomUnitDivisionTreeItem   Tree(0, TRangeItem(1, TextWrapper.Text().Length()));
   ParSentWordFSM::TParSenWordDescriptor 		   D = ParSentWordFSM::Descriptor(&Tree);

#define TState ParSentWordFSM::TState
#define TEvent ParSentWordFSM::TEvent
#define TFSMachine SFiniteStateMachine<TState, TEvent, SOnEnterFunctor<TState, TEvent>, SIgnoreStrategy<TEvent> >
#define TFSMM  TFiniteStateMachineManager<TEvent, TFSMachine, ParSentWordFSM::TParSenWordDescriptor, TTextStringWrapper>

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


	rme.AddMap(curAlias, Levels[2].PUnits());

/*

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
                                  */
#undef TState
#undef TEvent
#undef TFSMachine
#undef TFSMM
}
//---------------------------------------------------------------------------

#include "CTextStringWrapper.h"
#include "CFleschReadingComfortability.h"

void __fastcall TTestingTable::Button5Click(TObject *Sender)
{
    TFleschReadingComfortability<TRussianFleschCalculator> flesch;

    ShowMessage("Flesch reading comfort = " + FloatToStr(flesch.FleschReadingComfortability(&TextWrapper)));
}
//---------------------------------------------------------------------------

#include "URules.h"
#include "BRuleProcessor.h"

void __fastcall TTestingTable::Button3Click(TObject *Sender)
{

    TRuleProcessor<TTextStringWrapper> rp(TextWrapper);

    rp << ns_Rules::Hiss()
       << ns_Rules::SameLettersContact()
       << ns_Rules::SameWordsBegining(rd_Forward)
       << ns_Rules::SameWordsBegining(rd_Backward)
       << ns_Rules::DoublingDoubles(rd_Forward)
       << ns_Rules::DoublingTriples(rd_Forward)
       << ns_Rules::Consonants()
       << ns_Rules::Vowels()
       << ns_Rules::Noise();

   rp << ns_Rules::AlternatingContact();

    rp.Process();

TResoundingBatch batch   =  rp.ResoundingBatch();
TRuleResoundingItems        ruleResItems;
TResoundingItem::TLinkDots  dots;
TRangeItem                  affectedRange;


TTextString s;

Memo3->Text = "";

   for (TUInt i=0; i<batch.Count(); i++)
   {
   ruleResItems = batch[i];

      for (TUInt j=0; j<ruleResItems.Count(); j++)
      {
          dots = ruleResItems[j].LinkDots();
          affectedRange = ruleResItems[j].AffectedRange();
          s = "";

          for (TUInt k=0; k<dots.size(); k++)
             s += TextWrapper[dots[k]];

       Memo3->Lines->Add(s);
       Memo3->Lines->Add(TextWrapper.SubString(affectedRange.From(), affectedRange.Count()) + " | " + FloatToStr(ruleResItems.Value()));
       Memo3->Lines->Add(FloatToStr(batch[i].Value()));
      };
   };
}
//---------------------------------------------------------------------------

#include "CBaseCoverProcessor.h"
#include "UCharsValues.h"
#include "BResoundingCover.h"

void __fastcall TTestingTable::Button1Click(TObject *Sender)
{
    TBaseCoverProcessor<TTextStringWrapper> bcp(TextWrapper, ns_CharsValues::DefaultCharValuesMap());
    TRuleProcessor<TTextStringWrapper>      rp(TextWrapper);

    rp << ns_Rules::Hiss()
       << ns_Rules::SameLettersContact()
       << ns_Rules::SameWordsBegining(rd_Forward)
       << ns_Rules::SameWordsBegining(rd_Backward)
       << ns_Rules::DoublingDoubles(rd_Forward)
       << ns_Rules::DoublingTriples(rd_Forward)
       << ns_Rules::Consonants()
       << ns_Rules::Vowels()
       << ns_Rules::Noise();

   rp << ns_Rules::AlternatingContact();

    rp.Process();
    bcp.Process();

    TResoundingCover resCover(TRangeItem(TextWrapper.Begin(), TextWrapper.End()));
       resCover << bcp.BaseCover() << rp.ResoundingBatch();

    TValuesCover base     = resCover.BaseCover();
    TValuesCover merged   = resCover.MergedCover();
    TValuesCover smoothed = merged.Smoothed();

    Memo3->Text = "";
      for (TUInt j=0; j<smoothed.Count(); j++)
         Memo3->Lines->Add(FloatToStr(base[j]) + " | " + FloatToStr(merged[j]) + " | " + FloatToStr(smoothed[j]) );
}
//---------------------------------------------------------------------------


#include "ADocument.h"
#include "APagesCompositor.h"

void __fastcall TTestingTable::Button7Click(TObject *Sender)
{
   ns_Document::TDocument doc(&TextWrapper);

   TPagesCompositor pc(60, 40);
   doc.Copmose(&pc);
     Memo1->Lines->Add("Length: " + IntToStr(TextWrapper.Length()));
     Memo1->Lines->Add("Doc.Count() = " + IntToStr(doc.Count()));
     Memo1->Lines->Add("Length / (RowLength*RowsCount) = " + FloatToStr(TextWrapper.Length() / (60*40)));

     Memo4->Text = "";
     for (TUInt i=0; i<doc.Count(); i++)
         Memo4->Text = Memo4->Text + "\n\r----------\n\r" + doc[i];
}
//---------------------------------------------------------------------------

void __fastcall TTestingTable::FormCreate(TObject *Sender)
{

      try
      {
         TVCLFileDataLoader FDL;
         TRawDataItem RDI;

           RDI = TRawDataItem(&FDL, "3.txt");
         RDI.Unvirtualize();

         Edit1->Text = RDI.Alias();
         TextWrapper = RDI.Text();
         Memo1->Text = TextWrapper.Text();
         Edit2->Text = "3.txt";
      }
      catch(...)
      {
          TextWrapper = "Empty";
          Edit2->Text = "";
      };
}
//---------------------------------------------------------------------------

void __fastcall TTestingTable::BtnSetAuthorAndTitleClick(TObject *Sender)
{
    TextsController2.SetAuthorAndTitle(curAlias, Edit1->Text, Edit2->Text);

    GetTextsList();
}
//---------------------------------------------------------------------------

#include "CTextsListFormatter.h"

void TTestingTable::GetTextsList()
{
TTextsListFormatter formatter;
    TTextStringList list = formatter.FullTitlesList(cTitleFormat, true, TextsController2.PLogicalTextContainer());

    LBTitles->Items->Clear();
    for (TUInt i=0; i<list.Count(); i++)
    {
        LBTitles->Items->Add(list[i]);
    }
};

#include "DCharFrequencyCalculator.h"
void __fastcall TTestingTable::Button6Click(TObject *Sender)
{
    TCharFrequencyCalculator calc;
}
//---------------------------------------------------------------------------


void __fastcall TTestingTable::Button9Click(TObject *Sender)
{
    Edit2->Text = IntToStr(rme.Count());
	rme.Equalify();

    vector<TRangeItem> items;

    TTextStringWrapper wrapper;
    TTextString S;
    TTextString alias;


    alias 	= LBTitles->Items->operator [](0);
    items   = rme[alias];
    wrapper = TextsController2[alias]->Text();

    Memo3->Text = "";
    Memo4->Text = "";
       	for (TUInt i=0; i<items.size(); i++)
    	{
        	S = wrapper.SubString(items[i].From(), items[i].Length());
        	Memo3->Lines->Add(S);
    	};

    alias 	= LBTitles->Items->operator [](1);
    items   = rme[alias];
    wrapper = TextsController2[alias]->Text();

    	for (TUInt i=0; i<items.size(); i++)
    	{
        	S = wrapper.SubString(items[i].From(), items[i].Length());
        	Memo4->Lines->Add(S);
    	};
}
//---------------------------------------------------------------------------


void __fastcall TTestingTable::Button8Click(TObject *Sender)
{
TLogicalTextsContainer * cont = TextsController2.PLogicalTextContainer();
	for (TUInt i=0; i<cont->Count(); i++)
    {

        Memo2->Text = cont->Text(i);
        //MSelectedTextPreview->Text = (*cont)[i].Text();

    }
}
//---------------------------------------------------------------------------



