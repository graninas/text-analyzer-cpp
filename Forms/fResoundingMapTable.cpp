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

#include "fResoundingMapTable.h"
#include "VCLConstants.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TResoundingMapTable *ResoundingMapTable;

TResoundingMapView  ResoundingMapView;



//---------------------------------------------------------------------------
__fastcall TResoundingMapTable::TResoundingMapTable(TComponent* Owner)
	: TForm(Owner)
{

}
//---------------------------------------------------------------------------

void TResoundingMapTable::Init(TTextDataProvider * tTextDataProvider, TValuesCover tCover, TResoundingCover * tResoundingCover, TRulesProxy tRulesProxy)
{
  ResoundingMapView.CreateGLView(PTextPanel->Handle, PTextPanel->Width, PTextPanel->Height, cTextViewName);
  ResoundingMapView.CreateGLView(PMapDrawingPanel1->Handle, PMapDrawingPanel1->Width, PMapDrawingPanel1->Height, cMapView1Name);

ResoundingMapView.Init(tTextDataProvider, tCover, tResoundingCover, tRulesProxy);

  ResoundingMapView.InitGLTextPage(cTextViewName);
  ResoundingMapView.InitGLResoundingMapPage(cMapView1Name);

//ResoundingMapView.DrawAll();
this->Show();
this->Update();
ResoundingMapView.DrawAll();
};

void __fastcall TResoundingMapTable::ToolButton2Click(TObject *Sender)
{
	ResoundingMapView.PrevPage();
    this->Update();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTable::ToolButton3Click(TObject *Sender)
{
	ResoundingMapView.NextPage();
    this->Update();
}
//---------------------------------------------------------------------------

void __fastcall TResoundingMapTable::PMapDrawingPanel1MouseDown(
      TObject *Sender, TMouseButton Button, TShiftState Shift, int X,
      int Y)
{
   _MouseX = X;
   _MouseY = Y;
ResoundingMapView.OnMouseClick(_MouseX, _MouseY);
SetResoundingRulesList(ResoundingMapView.RulesList());
 this->Update();
}
//---------------------------------------------------------------------------
void TResoundingMapTable::SetResoundingRulesList(TTextString tRules)
{
	MMapRules->Text = tRules;
}
