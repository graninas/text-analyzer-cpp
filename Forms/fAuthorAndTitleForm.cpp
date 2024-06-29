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

#include "fAuthorAndTitleForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfAuthorAndTitle *fAuthorAndTitle;
//---------------------------------------------------------------------------
__fastcall TfAuthorAndTitle::TfAuthorAndTitle(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfAuthorAndTitle::EAuthorChange(TObject *Sender)
{
	 _Author = EAuthor->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfAuthorAndTitle::ETitleChange(TObject *Sender)
{
	 _Title = ETitle->Text;
}
//---------------------------------------------------------------------------
void __fastcall TfAuthorAndTitle::ChkKeyTextClick(TObject *Sender)
{
	 _KeyText = ChkKeyText->Checked;
}
//---------------------------------------------------------------------------

void __fastcall TfAuthorAndTitle::FormShow(TObject *Sender)
{
EAuthor->SetFocus();	
}
//---------------------------------------------------------------------------

       void TfAuthorAndTitle::Init(const TInitMode & tInitMode, const AnsiString & tAuthor, const AnsiString & tTitle)
       {
            _Title = tTitle;
            _Author = tAuthor;

            ETitle->Text = tTitle;
            EAuthor->Text = tAuthor;

            switch (tInitMode)
            {
                 case im_Prototype:
                 {
	                 ChkKeyText->Checked = false;
                     BtnCancel->Enabled = false;
                     _KeyText = false;
                 }; break;

                 case im_KeyText:
                 {
	                 ChkKeyText->Checked = true;
                     BtnCancel->Enabled = false;
                     _KeyText = true;
                 }; break;

                 case im_Editing:
                 {
	                 ChkKeyText->Checked = false;
                     BtnCancel->Enabled = true;
                     _KeyText = false;
                 }; break;
            };
       }






void __fastcall TfAuthorAndTitle::EAuthorKeyPress(TObject *Sender,
      char &Key)
{
	if (Key == 13) fAuthorAndTitle->ModalResult = mrOk;
}
//---------------------------------------------------------------------------

void __fastcall TfAuthorAndTitle::ETitleKeyPress(TObject *Sender,
      char &Key)
{
	if (Key == 13) fAuthorAndTitle->ModalResult = mrOk;	
}
//---------------------------------------------------------------------------

