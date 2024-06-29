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
#ifndef CAnalysisReporterH
#define CAnalysisReporterH
//---------------------------------------------------------------------------

#include "UTypes.h"
#include "UReportFunctionsTypes.h"

class TAnalysisReporter
{
protected:

	PShowMessageFunc _ShowMessageFunc;
    PProgressFunc	 _ProgressFunc;

	PShowMessageActionFunc  _ShowMessageActionFunc;
	PProgressActionFunc     _ProgressActionFunc;

    PShowMessageFunc	    _AnalysisBeginFunc;
    PShowMessageFunc 		_AnalysisEndFunc;
    PShowMessageActionFunc  _StageBeginFunc;
    PShowMessageActionFunc  _StageEndFunc;

public:

	void SetShowMessageFunc(PShowMessageFunc tFunc);
    void SetProgressFunc   (PProgressFunc    tFunc);

	void SetShowMessageActionFunc(PShowMessageActionFunc tFunc);
    void SetProgressActionFunc   (PProgressActionFunc    tFunc);

    void SetAnalysisBeginFunc(PShowMessageFunc tFunc);
    void SetAnalysisEndFunc(PShowMessageFunc tFunc);
    void SetStageBeginFunc(PShowMessageActionFunc tFunc);
    void SetStageEndFunc(PShowMessageActionFunc tFunc);

    PShowMessageFunc ShowMessageFunc();
    PProgressFunc    ProgressFunc();

    PShowMessageActionFunc ShowMessageActionFunc();
    PProgressActionFunc    ProgressActionFunc();

	void ReportShowMessage(const TTextString & Message);

    void ReportAnalysisBegin(const TTextString & Message);
    void ReportAnalysisEnd  (const TTextString & Message);
    void ReportStageBegin   (const TTextString & tStage, const TTextString & Message);
    void ReportStageEnd     (const TTextString & tStage, const TTextString & Message);

    void ReportAnalysisStage   (const TTextString & tStage, const TTextString & Message);
    void ReportAnalysisProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress);

	TAnalysisReporter(){};
};


#endif
