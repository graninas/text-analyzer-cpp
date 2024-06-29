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
#pragma hdrstop
#include "CAnalysisReporter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void TAnalysisReporter::SetShowMessageFunc(PShowMessageFunc tFunc)
{
	_ShowMessageFunc = tFunc;
};

void TAnalysisReporter::SetProgressFunc   (PProgressFunc    tFunc)
{
    _ProgressFunc = tFunc;
};

void TAnalysisReporter::SetShowMessageActionFunc(PShowMessageActionFunc tFunc)
{
	_ShowMessageActionFunc = tFunc;
};

void TAnalysisReporter::SetProgressActionFunc   (PProgressActionFunc    tFunc)
{
    _ProgressActionFunc = tFunc;
};

void TAnalysisReporter::SetAnalysisBeginFunc(PShowMessageFunc tFunc)
{
_AnalysisBeginFunc = tFunc;
};

void TAnalysisReporter::SetAnalysisEndFunc(PShowMessageFunc tFunc)
{
_AnalysisEndFunc = tFunc;
};

void TAnalysisReporter::SetStageBeginFunc(PShowMessageActionFunc tFunc)
{
_StageBeginFunc = tFunc;
};

void TAnalysisReporter::SetStageEndFunc(PShowMessageActionFunc tFunc)
{
_StageEndFunc = tFunc;
};


PShowMessageFunc TAnalysisReporter::ShowMessageFunc()
{
    return _ShowMessageFunc;
};

PProgressFunc TAnalysisReporter::ProgressFunc()
{
    return _ProgressFunc;
};

PShowMessageActionFunc TAnalysisReporter::ShowMessageActionFunc()
{
    return _ShowMessageActionFunc;
};

PProgressActionFunc    TAnalysisReporter::ProgressActionFunc()
{
    return _ProgressActionFunc;
};

void TAnalysisReporter::ReportShowMessage(const TTextString & Message)
{
    _ShowMessageFunc(Message);
};

void TAnalysisReporter::ReportAnalysisBegin(const TTextString & Message)
{
    _AnalysisBeginFunc(Message);
};

void TAnalysisReporter::ReportAnalysisEnd(const TTextString & Message)
{
    _AnalysisEndFunc(Message);
};

void TAnalysisReporter::ReportStageBegin(const TTextString & tStage, const TTextString & Message)
{
    _StageBeginFunc(tStage, Message);
};

void TAnalysisReporter::ReportStageEnd(const TTextString & tStage, const TTextString & Message)
{
    _StageEndFunc(tStage, Message);
};

void TAnalysisReporter::ReportAnalysisStage(const TTextString & tStage, const TTextString & Message)
{
	_ShowMessageActionFunc(tStage, Message);
};

void TAnalysisReporter::ReportAnalysisProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
    _ProgressActionFunc(tStage, tBegin, tEnd, tProgress);
};
 