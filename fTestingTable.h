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

#ifndef fTestingTableH
#define fTestingTableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TTestingTable : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TOpenDialog *OpenDialog1;
        TButton *Button2;
        TMemo *Memo1;
        TEdit *Edit1;
        TButton *Button3;
        TEdit *Edit2;
        TLabel *Label1;
        TButton *Button4;
        TMemo *Memo2;
        TMemo *Memo3;
        TButton *Button5;
        TMemo *Memo4;
    TButton *Button6;
    TButton *Button7;
    TButton *Button8;
    TLabel *Label2;
    TButton *BtnSetAuthorAndTitle;
    TListBox *LBTitles;
    TButton *Button9;
	TButton *Button10;
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall Button7Click(TObject *Sender);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall BtnSetAuthorAndTitleClick(TObject *Sender);
    void __fastcall Button6Click(TObject *Sender);
	void __fastcall Button9Click(TObject *Sender);
	void __fastcall Button8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TTestingTable(TComponent* Owner);

        void GetTextsList();
};
//---------------------------------------------------------------------------
extern PACKAGE TTestingTable *TestingTable;
//---------------------------------------------------------------------------
#endif
