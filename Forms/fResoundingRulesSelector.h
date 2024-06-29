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

#ifndef fResoundingRulesSelectorH
#define fResoundingRulesSelectorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#include "BRulesProxy.h"

class TResoundingRulesSelector : public TForm
{
__published:	// IDE-managed Components
	TPanel *PRulesListPanel;
	TButton *BtnMakeResoundingMap;
	TButton *BtnCancel;
	TCheckListBox *CLBRulesListBox;
	TLabel *LTotalTextsInfo;
	TLabel *LPlusInfo;
	TLabel *LMinusInfo;
	TLabel *Label1;
	TLabel *Label3;
	TLabel *Label2;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
private:	// User declarations

	TRulesProxy  _Rules;

public:		// User declarations
	__fastcall TResoundingRulesSelector(TComponent* Owner);


    void Init();
	TRulesProxy GetRules();
};
//---------------------------------------------------------------------------
extern PACKAGE TResoundingRulesSelector *ResoundingRulesSelector;
//---------------------------------------------------------------------------
#endif
