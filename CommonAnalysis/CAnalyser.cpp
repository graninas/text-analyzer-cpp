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
#include "CAnalyser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void TAnalyser::_ReportShowMessage(const TTextString & tMessage)
{
    if (_Reporter) _Reporter->ReportShowMessage(tMessage);
};

void TAnalyser::_ReportAboutAnalysisBegin(const TTextString & tMessage)
{
    if (_Reporter) _Reporter->ReportAnalysisBegin(tMessage);
};

void TAnalyser::_ReportAboutAnalysisEnd(const TTextString & tMessage)
{
    if (_Reporter) _Reporter->ReportAnalysisEnd(tMessage);
};

void TAnalyser::_ReportAboutActionBegin(const TTextString & tStage, const TTextString & tMessage)
{
    if (_Reporter) _Reporter->ReportStageBegin(tStage, tMessage);
};

void TAnalyser::_ReportAboutActionEnd(const TTextString & tStage, const TTextString & tMessage)
{
    if (_Reporter) _Reporter->ReportStageEnd(tStage, tMessage);
};

void TAnalyser::_ReportAboutAction(const TTextString & tStage, const TTextString & tMessage)
{
	if (_Reporter) _Reporter->ReportAnalysisStage(tStage, tMessage);
};

void TAnalyser::_ReportAboutProgress(const TTextString & tStage, const TUInt & tBegin, const TUInt & tEnd, const TUInt & tProgress)
{
    if (_Reporter) _Reporter->ReportAnalysisProgress(tStage, tBegin, tEnd, tProgress);
};


TAnalyser::SpecificatorType 	TAnalyser::Specificator() const
{
	return _Name;
};

TTextString TAnalyser::Name() const
{
	return _Name;
}

void TAnalyser::SetReporter(TAnalysisReporter * tReporter)
{
	_Reporter = tReporter;
};

