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

#include "fPrimaryTextLoading.h"
#include "TPrimaryProcessThread.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPrimaryTextLoading *PrimaryTextLoading;

//---------------------------------------------------------------------------
__fastcall TPrimaryTextLoading::TPrimaryTextLoading(TComponent* Owner)
    : TForm(Owner)
{
    _CurBitmapIndex = 0;

}
//---------------------------------------------------------------------------

void  __fastcall TPrimaryTextLoading::GoPrimaryProcess()
{
   this->Show();

   _Analyser->PrimaryProcess();

   AEnableReadyExecute(this);
}

void TPrimaryTextLoading::SetAnalyser(TTextResoundingAnalyser * tAnalyser)
{
    _Analyser = tAnalyser;
};

int TPrimaryTextLoading::_NextBitmapIndex()
{
    if ((_CurBitmapIndex+1)>=ILProcess->Count)
         _CurBitmapIndex = 0;
    else _CurBitmapIndex += 1;
return   _CurBitmapIndex;
};


void __fastcall TPrimaryTextLoading::UpdateProcess(const int & tMax, const int & tCurrent)
{
Update();
int max = tMax;
    PBPrimaryProcessProgress->Max = max;
    PBPrimaryProcessProgress->Position = tCurrent;

    if (max == 0) max = 1;

     //ILProcess->GetBitmap(_NextBitmapIndex(), IPrimaryProcessDemo->Picture->Bitmap);

float fpercent = (float(tCurrent)/float(max))*100.0f;
int   ipercent = int(fpercent);

     LPrimaryProcessPercent->Caption = IntToStr(ipercent);
     LPrimaryProcessPercent->Caption = LPrimaryProcessPercent->Caption + " %";
Update();
};

void __fastcall TPrimaryTextLoading::AEnableReadyExecute(TObject *Sender)
{
    BtnReady->Enabled = true;
    LPrimaryProcessPercent->Caption = "Готово.";
    PBPrimaryProcessProgress->Position = PBPrimaryProcessProgress->Max;
}
//---------------------------------------------------------------------------

void __fastcall TPrimaryTextLoading::AReadyClickExecute(TObject *Sender)
{
   _Analyser->SetAuthorAndTitle(EAuthorName->Text, ETitle->Text);
   this->Hide();
}
//---------------------------------------------------------------------------

