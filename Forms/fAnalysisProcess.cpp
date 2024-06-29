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

#include "fAnalysisProcess.h"

#include "UConstants.h"



//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAnalysisProcess *AnalysisProcess;

TAnalysisReporter AnalysisReporter;

//---------------------------------------------------------------------------

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
TThreadingObjectInfo *tStruct = (TThreadingObjectInfo*) lpParameter;

   tStruct->Analyser->DoAnalysis(tStruct->AnalysisName);
   AnalysisProcess->EnableButtons();

return true;
};

//---------------------------------------------------------------------------


void ShowMessageFunc(const TTextString & tMsg)
{
	AnalysisProcess->SetAction(tMsg);
}

void  ProgressFunc(const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
    AnalysisProcess->SetProgress(tBegin, tEnd, tProgress);
}

void ShowMessageActionFunc(const TTextString & tAction, const TTextString & tMsg)
{
	AnalysisProcess->SetAction(tAction);
	AnalysisProcess->SetMessage(tMsg);
}

void  ProgressActionFunc(const TTextString & tAction, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
	AnalysisProcess->SetAction(tAction);
    AnalysisProcess->SetProgress(tBegin, tEnd, tProgress);
}

void AnalysisBeginFunc(const TTextString & tMessage)
{
    AnalysisProcess->SetAnalysisBegin(tMessage);
};

void AnalysisEndFunc(const TTextString & tMessage)
{
    AnalysisProcess->SetAnalysisEnd(tMessage);
};

void StageBeginFunc(const TTextString & tStage, const TTextString & tMessage)
{
    AnalysisProcess->SetStageBegin(tStage, tMessage);
};

void StageEndFunc(const TTextString & tStage, const TTextString & tMessage)
{
    AnalysisProcess->SetStageEnd(tStage, tMessage);
};

//---------------------------------------------------------------------------
__fastcall TAnalysisProcess::TAnalysisProcess(TComponent* Owner)
	: TForm(Owner)
{
	AnalysisReporter.SetShowMessageFunc(ShowMessageFunc);
    AnalysisReporter.SetProgressFunc   (ProgressFunc);

	AnalysisReporter.SetShowMessageActionFunc(ShowMessageActionFunc);
    AnalysisReporter.SetProgressActionFunc(ProgressActionFunc);

    AnalysisReporter.SetAnalysisBeginFunc(AnalysisBeginFunc);
    AnalysisReporter.SetAnalysisEndFunc(AnalysisEndFunc);
    AnalysisReporter.SetStageBeginFunc(StageBeginFunc);
    AnalysisReporter.SetStageEndFunc(StageEndFunc);
}
//---------------------------------------------------------------------------

void TAnalysisProcess::EnableButtons()
{
//    BtnClose->Enabled = true;
    BtnShowResults->Enabled = true;
};

void TAnalysisProcess::DisableButtons()
{
//    BtnClose->Enabled = false;
    BtnShowResults->Enabled = false;
};

void TAnalysisProcess::SetAction(const TTextString & tMessage)
{
	LCurrentOperation->Caption = tMessage;
    MProcessInfo->Lines->Add(tMessage);
};

void TAnalysisProcess::SetMessage(const TTextString & tMessage)
{
	LCurrentOperation->Caption = tMessage;
//    MProcessInfo->Lines->Add(tMessage);
this->Update();
};

void TAnalysisProcess::SetProgress(const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
	PBCurrentOperationProgress->Min = tBegin;
    PBCurrentOperationProgress->Max = tEnd;
    PBCurrentOperationProgress->Position = tProgress;
this->Update();
};

void TAnalysisProcess::SetAnalysisBegin(const TTextString & tMessage)
{
	MProcessInfo->Lines->Add(tMessage);
};

void TAnalysisProcess::SetAnalysisEnd(const TTextString & tMessage)
{
	MProcessInfo->Lines->Add(tMessage);
};

void TAnalysisProcess::SetStageBegin(const TTextString & tStage, const TTextString & tMessage)
{
	MProcessInfo->Lines->Add(tMessage);
};

void TAnalysisProcess::SetStageEnd(const TTextString & tStage, const TTextString & tMessage)
{
	MProcessInfo->Lines->Add(tMessage);
};

void TAnalysisProcess::Init(TAnalyserControllersFasade * tAnalyserFasade, const TTextString & tAnalysisName)
{
	_AnalyserFasade = tAnalyserFasade;
    MProcessInfo->Lines->Clear();

    DisableButtons();
    _AnalysisName = tAnalysisName;
};

void __fastcall TAnalysisProcess::FormShow(TObject *Sender)
{
_ThreadingObjectInfo.Analyser     = _AnalyserFasade;
_ThreadingObjectInfo.AnalysisName = _AnalysisName;

if (!_Thread) _Thread = CreateThread(NULL, NULL, ThreadProc, &_ThreadingObjectInfo, NULL, NULL);

}
//---------------------------------------------------------------------------

void __fastcall TAnalysisProcess::BtnCloseClick(TObject *Sender)
{
	if (_Thread)
    {
    	SuspendThread(_Thread);
        CloseHandle(_Thread);
    _Thread = NULL;
    ModalResult = mrCancel;
    }
}
//---------------------------------------------------------------------------

void __fastcall TAnalysisProcess::FormHide(TObject *Sender)
{
    if (_Thread)
    {
    	SuspendThread(_Thread);
        CloseHandle(_Thread);
    _Thread = NULL;
    }
}
//---------------------------------------------------------------------------

void __fastcall TAnalysisProcess::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	if (_Thread)
    {
    	SuspendThread(_Thread);
        CloseHandle(_Thread);
    _Thread = NULL;
    ModalResult = mrCancel;
    }
}
//---------------------------------------------------------------------------

void __fastcall TAnalysisProcess::BtnShowResultsClick(TObject *Sender)
{
	if (_Thread)
    {
    	SuspendThread(_Thread);
        CloseHandle(_Thread);
    _Thread = NULL;
    ModalResult = mrOk;
    }
}
//---------------------------------------------------------------------------

