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

#include "fAbout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAbout *About;
//---------------------------------------------------------------------------
__fastcall TAbout::TAbout(TComponent* Owner)
        : TForm(Owner), _Expanded(false)
{
}
//---------------------------------------------------------------------------
void __fastcall TAbout::LMailToClick(TObject *Sender)
{
   ShellExecute(Application->Handle, NULL, "mailto:graninas@gmail.com", NULL, NULL, SW_SHOW);
}
//---------------------------------------------------------------------------
void __fastcall TAbout::LMoreClick(TObject *Sender)
{
	_Expanded = !_Expanded;
    if (!_Expanded)
    {
    	MInfo->Visible = false;
        About->Height = 161;
		PMainPanel->Height = 89;
        LMore->Caption = "Больше информации >>>";
        LMore->Top = 108;
        BtnOK->Top = 104;
    }
    else
    if (_Expanded)
    {
    	MInfo->Visible = true;
        About->Height = 300;
		PMainPanel->Height = 225;
        LMore->Caption = "<<< Меньше информации";
        LMore->Top = 244;
        BtnOK->Top = 240;
    }
}
//---------------------------------------------------------------------------

