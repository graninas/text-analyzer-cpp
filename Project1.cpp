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
//---------------------------------------------------------------------------
USEFORM("fTestingTable.cpp", TestingTable);
USEFORM("fPrimaryTextLoading.cpp", PrimaryTextLoading);
USEFORM("fAuthoringAnalyserTable.cpp", AuthoringAnalyserTable);
USEFORM("Forms\fResoundingMapTableOld.cpp", ResoundingMapTableOld);
USEFORM("Forms\fAuthorAndTitleForm.cpp", fAuthorAndTitle);
USEFORM("Forms\fAnalysisProcess.cpp", AnalysisProcess);
USEFORM("Forms\fResoundingRulesSelector.cpp", ResoundingRulesSelector);
USEFORM("Forms\fAuthoringAnalysisResults.cpp", AuthoringAnalysisResults);
USEFORM("Forms\fResoundingMapTable.cpp", ResoundingMapTable);
USEFORM("Forms\fAbout.cpp", About);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
		Application->CreateForm(__classid(TAuthoringAnalyserTable), &AuthoringAnalyserTable);
		Application->CreateForm(__classid(TPrimaryTextLoading), &PrimaryTextLoading);
		Application->CreateForm(__classid(TfAuthorAndTitle), &fAuthorAndTitle);
		Application->CreateForm(__classid(TAnalysisProcess), &AnalysisProcess);
		Application->CreateForm(__classid(TResoundingRulesSelector), &ResoundingRulesSelector);
		Application->CreateForm(__classid(TAuthoringAnalysisResults), &AuthoringAnalysisResults);
		Application->CreateForm(__classid(TResoundingMapTable), &ResoundingMapTable);
		Application->CreateForm(__classid(TAbout), &About);
		Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
