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

#include "fResoundingMapTableOld.h"
#include "ATextResoundingAnalyser.h"
#include "TPrimaryProcessThread.h"
#include "TMainUpdateThread.h"
#include "fPrimaryTextLoading.h"
#include "VCLConstants.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
TResoundingMapTableOld *ResoundingMapTableOld;

TTextResoundingAnalyser  Analyser;

//---------------------------------------------------------------------------
__fastcall TResoundingMapTableOld::TResoundingMapTableOld(TComponent* Owner)
    : TForm(Owner)
{
    ADisablePagesNavigation->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::SetResoundingRulesList(const AnsiString & tList)
{
    MMapRules->Text = tList;
};

void __fastcall TResoundingMapTableOld::SetAssonancesRulesList(const AnsiString & tList)
{
    MAssonancesRules->Text = tList;
};

void __fastcall TResoundingMapTableOld::AOpenTextExecute(TObject *Sender)
{
if (PrimaryProcessTread)
{
    PrimaryProcessTread->Suspend();
    PrimaryProcessTread->Terminate();
    delete PrimaryProcessTread;
};

PrimaryProcessTread = new TPrimaryProcessThread(true,  &Analyser);
PrimaryProcessTread->Priority = cPrimaryProcessThreadPriority;

      Analyser.ClearAll();

      AResoundingMapRulesLoad->Execute();
      AAssonancesMapRulesLoad->Execute();

      Analyser.SetTreeProcessing(true);

PrimaryTextLoading->SetAnalyser(&Analyser);

PrimaryProcessTread->Resume();

     if (ODOpenText->Execute())
     {
          if (!Analyser.LoadText(ODOpenText->FileName))
          {
              ShowMessage("Не удалось загрузить файл.");

              Analyser.SetTreeProcessing(false);
          return;
          };

          PrimaryTextLoading->GoPrimaryProcess();
          PrimaryProcessTread->Suspend();

     Analyser.SetTreeProcessing(false);
     }
     else
     {
       PrimaryProcessTread->Suspend();
       Analyser.SetTreeProcessing(false);
     return;
     }

  while (!Analyser.ReadyToWork());

MainUpdateThread = new TMainUpdateThread(true,  &Analyser);
MainUpdateThread->Priority = cMainUpdateThreadPriority;
MainUpdateThread->Resume();


  Analyser.CreateGLView(PTextPanel->Handle, PTextPanel->Width, PTextPanel->Height, cTextViewName);
  Analyser.CreateGLView(PMapDrawingPanel1->Handle, PMapDrawingPanel1->Width, PMapDrawingPanel1->Height, cMapView1Name);
  Analyser.CreateGLView(PMapDrawingPanel2->Handle, PMapDrawingPanel2->Width, PMapDrawingPanel2->Height, cMapView2Name);
  Analyser.CreateGLView(PMapDrawingPanel3->Handle, PMapDrawingPanel3->Width, PMapDrawingPanel3->Height, cFleschViewName);

  Analyser.InitGLTextPage(cTextViewName);
  Analyser.InitGLResoundingMapPage(cMapView1Name);
  Analyser.InitGLAssonancesMapPage(cMapView2Name);
//  Analyser.InitGLFleschPage(cFleschViewName);

  Analyser.SelectPage(0);

AEnablePagesNavigation->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::ACloseProgramExecute(TObject *Sender)
{
    Analyser.ClearAll();

    if (PrimaryProcessTread) delete PrimaryProcessTread;
    if (MainUpdateThread)    delete MainUpdateThread;

    Application->Terminate();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    Analyser.ClearAll();
}
//---------------------------------------------------------------------------

#include "URules.h"


void __fastcall TResoundingMapTableOld::AResoundingMapRulesChangeExecute(
      TObject *Sender)
{
AResoundingMapRulesLoad->Execute();
    Analyser.OnResoundingRulesChange();
}
//---------------------------------------------------------------------------


void __fastcall TResoundingMapTableOld::AResoundingMapRulesLoadExecute(
      TObject *Sender)
{
TRulesProxy rulesProxy;
       if (ChkRule1->Checked) rulesProxy << ns_Rules::Hiss();
       if (ChkRule2->Checked) rulesProxy << ns_Rules::SameLettersContact();
       if (ChkRule3->Checked) rulesProxy << ns_Rules::SameWordsBegining(rd_Forward) << ns_Rules::SameWordsBegining(rd_Backward);
       if (ChkRule4->Checked) rulesProxy << ns_Rules::DoublingDoubles(rd_Forward);
       if (ChkRule5->Checked) rulesProxy << ns_Rules::Consonants();
       if (ChkRule6->Checked) rulesProxy << ns_Rules::AlternatingContact();
       if (ChkRule7->Checked) rulesProxy << ns_Rules::Noise();
Analyser.SetResoundingMapRules(rulesProxy);
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::AAssonancesMapRulesLoadExecute(
      TObject *Sender)
{
TRulesProxy rulesProxy;
       if (ChkAR1->Checked) rulesProxy << ns_Rules::Hiss();
       if (ChkAR2->Checked) rulesProxy << ns_Rules::SameLettersContact();
       if (ChkAR3->Checked) rulesProxy << ns_Rules::SameWordsBegining(rd_Forward) << ns_Rules::SameWordsBegining(rd_Backward);
       if (ChkAR4->Checked) rulesProxy << ns_Rules::DoublingDoubles(rd_Forward);
       if (ChkAR5->Checked) rulesProxy << ns_Rules::Consonants();
       if (ChkAR6->Checked) rulesProxy << ns_Rules::AlternatingContact();
       if (ChkAR6->Checked) rulesProxy << ns_Rules::Noise();
Analyser.SetAssonansesMapRules(rulesProxy);
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::AAssonancesMapRulesChangeExecute(
      TObject *Sender)
{
AAssonancesMapRulesLoad->Execute();
    Analyser.OnAssonancesRulesChange();
}
//---------------------------------------------------------------------------



void __fastcall TResoundingMapTableOld::AEnablePagesNavigationExecute(
      TObject *Sender)
{
   APrevPage->Enabled = true;
   ANextPage->Enabled = true;
   ALastPage->Enabled = true;
   AFirstPage->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::ADisablePagesNavigationExecute(
      TObject *Sender)
{
   APrevPage->Enabled = false;
   ANextPage->Enabled = false;
   ALastPage->Enabled = false;
   AFirstPage->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::AFirstPageExecute(TObject *Sender)
{
    Analyser.SelectFirstPage();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::APrevPageExecute(TObject *Sender)
{
   Analyser.SelectPrevPage();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::ANextPageExecute(TObject *Sender)
{
   Analyser.SelectNextPage();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::ALastPageExecute(TObject *Sender)
{
   Analyser.SelectLastPage();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::Button1Click(TObject *Sender)
{
  Analyser.UpdateViews();    
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::AOnResoundingMapPanelClickExecute(
      TObject *Sender)
{
   Analyser.OnResoundingMapClick(_MouseX, _MouseY);    
}
//---------------------------------------------------------------------------



void __fastcall TResoundingMapTableOld::PMapDrawingPanel1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   _MouseX = X;
   _MouseY = Y;

   AOnResoundingMapPanelClick->Execute();    
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::AOnAssonancesMapPanelClickExecute(
      TObject *Sender)
{
   Analyser.OnAssonancesMapClick(_MouseX, _MouseY);
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTableOld::PMapDrawingPanel2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   _MouseX = X;
   _MouseY = Y;

   AOnAssonancesMapPanelClick->Execute();
}
//---------------------------------------------------------------------------


