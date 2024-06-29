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

#ifndef fAnalysisProcessH
#define fAnalysisProcessH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------

#include "CAnalyserControllersFasade.h"

struct TThreadingObjectInfo
{
	TAnalyserControllersFasade * Analyser;
    TTextString 			     AnalysisName;
};

class TAnalysisProcess : public TForm
{
__published:	// IDE-managed Components
	TCheckListBox *ChkLBProcessedTexts;
	TPanel *PRightPanel;
	TLabel *LCurrentOperation;
	TProgressBar *PBCurrentOperationProgress;
	TMemo *MProcessInfo;
	TLabel *LCurrentOperationInfo;
	TLabel *LCurrentOperationProgressInfo;
	TButton *BtnShowResults;
	TButton *BtnClose;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall BtnCloseClick(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall BtnShowResultsClick(TObject *Sender);
private:	// User declarations

	TAnalyserControllersFasade	*   _AnalyserFasade;
    TTextString 					_AnalysisName;

    HANDLE				 _Thread;
    TThreadingObjectInfo _ThreadingObjectInfo;

public:		// User declarations
	__fastcall TAnalysisProcess(TComponent* Owner);

    void Init(TAnalyserControllersFasade * tAnalyserFasade, const TTextString & tAnalysisName);


	void SetAction(const TTextString & tMessage);
	void SetMessage(const TTextString & tMessage);
    void SetProgress(const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress);

    void SetAnalysisBegin(const TTextString & tMessage);
    void SetAnalysisEnd(const TTextString & tMessage);
    void SetStageBegin(const TTextString & tStage, const TTextString & tMessage);
    void SetStageEnd(const TTextString & tStage, const TTextString & tMessage);

    void EnableButtons();
    void DisableButtons();

};
//---------------------------------------------------------------------------
extern PACKAGE TAnalysisProcess *AnalysisProcess;
extern PACKAGE TAnalysisReporter AnalysisReporter;
//---------------------------------------------------------------------------

#endif


