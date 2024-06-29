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
#ifndef CAnalyserH
#define CAnalyserH
//---------------------------------------------------------------------------

#include "CAnalysisReporter.h"
#include "UTypes.h"

class TAnalyser
{
public:

	typedef TTextString SpecificatorType;
    SpecificatorType 	Specificator() const;

protected:

	TTextString _Name;

    TAnalysisReporter * _Reporter;


    virtual void _ReportShowMessage(const TTextString & tMessage);
    virtual void _ReportAboutAnalysisBegin(const TTextString & tMessage);
    virtual void _ReportAboutAnalysisEnd(const TTextString & tMessage);
    virtual void _ReportAboutActionBegin(const TTextString & tStage, const TTextString & tMessage);
    virtual void _ReportAboutActionEnd(const TTextString & tStage, const TTextString & tMessage);
    virtual void _ReportAboutAction(const TTextString & tStage, const TTextString & tMessage);
    virtual void _ReportAboutProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress);


public:

    virtual TTextString Name() const;
    virtual void SetReporter(TAnalysisReporter * tReporter);
	virtual void DoAnalysis() = 0;

	TAnalyser(const TTextString & tName)
    	: _Name(tName), _Reporter(NULL){};

};

#endif
