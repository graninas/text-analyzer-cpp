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

#include "fAuthoringAnalysisResults.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAuthoringAnalysisResults *AuthoringAnalysisResults;
//---------------------------------------------------------------------------
__fastcall TAuthoringAnalysisResults::TAuthoringAnalysisResults(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void TAuthoringAnalysisResults::Init(const TTextString & tParagraphsRes, const TTextString & tSentencesRes, const TTextString & tWordsRes)
{
	LParagraphsResult->Caption = tParagraphsRes;
    LSentencesResult->Caption = tSentencesRes;
    LWordsResult->Caption = tWordsRes;
};
