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

#ifndef fAuthorAndTitleFormH
#define fAuthorAndTitleFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

enum TInitMode {im_Prototype, im_KeyText, im_Editing};

class TfAuthorAndTitle : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *LCurrentTextNumberInfo;
	TLabel *Label1;
	TEdit *EAuthor;
	TEdit *ETitle;
	TBitBtn *BtnOK;
	TBitBtn *BtnCancel;
	TCheckBox *ChkKeyText;
	void __fastcall EAuthorChange(TObject *Sender);
	void __fastcall ETitleChange(TObject *Sender);
	void __fastcall ChkKeyTextClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall EAuthorKeyPress(TObject *Sender, char &Key);
	void __fastcall ETitleKeyPress(TObject *Sender, char &Key);
private:	// User declarations

	AnsiString _Author;
    AnsiString _Title;
    bool	   _KeyText;

public:		// User declarations
	__fastcall TfAuthorAndTitle(TComponent* Owner);

       AnsiString Author() { return _Author; }
       AnsiString Title()  {return _Title; }
       bool	      IsKeyText() {return _KeyText; }

       void Init(const TInitMode & tInitMode, const AnsiString & tAuthor, const AnsiString & tTitle);
    };
//---------------------------------------------------------------------------
extern PACKAGE TfAuthorAndTitle *fAuthorAndTitle;
//---------------------------------------------------------------------------
#endif
