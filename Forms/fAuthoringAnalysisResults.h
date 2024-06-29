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

#ifndef fAuthoringAnalysisResultsH
#define fAuthoringAnalysisResultsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------

#include "UTypes.h"

class TAuthoringAnalysisResults : public TForm
{
__published:	// IDE-managed Components
	TBitBtn *BtnOk;
	TPanel *PMainPanel;
	TLabel *LResultsInfo;
	TLabel *LParagraphsResultInfo;
	TLabel *LSentencesResultInfo;
	TLabel *LWordsResultInfo;
	TLabel *LParagraphsResult;
	TLabel *LSentencesResult;
	TLabel *LWordsResult;
private:	// User declarations
public:		// User declarations

	__fastcall TAuthoringAnalysisResults(TComponent* Owner);

	void Init(const TTextString & tParagraphsRes, const TTextString & tSentencesRes, const TTextString & tWordsRes);
};
//---------------------------------------------------------------------------
extern PACKAGE TAuthoringAnalysisResults *AuthoringAnalysisResults;
//---------------------------------------------------------------------------
#endif
