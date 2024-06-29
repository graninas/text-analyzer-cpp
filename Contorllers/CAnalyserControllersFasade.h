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
#ifndef CAnalyserControllersFasadeH
#define CAnalyserControllersFasadeH
//---------------------------------------------------------------------------

#include "CTextsController.h"

#include "DAuthoringAnalyser.h"
#include "CResoundingMapAnalyser.h"

	class TAnalyserControllersFasade
    {
    private:

    	TTextsController 	_TextsController;

        TAuthoringAnalyser  	_AuthoringAnalyser;
		TResoundingMapAnalyser  _ResoundingAnalyser;

    public:

        TTextsController * PTextsController();
        void 			   SetTextsController(TTextsController * tTextsController);

        TAuthoringAnalyser	   * PAuthoringAnalyser();
        TResoundingMapAnalyser * PResoundingMapAnalyser();

        void LoadAsPrototype(const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle, TRawDataLoader * tLoader);
        void LoadAsKeyText  (const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle, TRawDataLoader * tLoader);

        void DeleteCurrentText();
        void DeleteKeyText();
        void DeleteAllTexts();

        void SelectText(const TUInt & tItemIndex, const TBool & tChecked);
        void SetActivatedAll(const TBool & tActivated);

        void SetCurrentTextAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle);
        void SetKeyTextAuthorAndTitle    (const TTextString & tAuthor, const TTextString & tTitle);

        TUInt TotalTextsLoaded() const;
        TBool KeyTextDefined()    const;
        TUInt TotalTextsActivated() ;

        void SetCurrentTextAsKeyText();
        void SetKeyTextAsPrototypeText();

        void SetAuthoringAnalysisReporter(TAnalysisReporter * tReporter);
        void SetResoundingAnalysisReporter(TAnalysisReporter * tReporter);

        void LoadResoundingAnalysisRules(const TRulesProxy & tRules);
        void SetPrototypeTextToResoundingAnalysis();
        void SetKeyTextToResoundingAnalysis();

        void DoAnalysis(const TTextString & tName);

		TAnalyserControllersFasade();
        ~TAnalyserControllersFasade(){};
    };




#endif
 