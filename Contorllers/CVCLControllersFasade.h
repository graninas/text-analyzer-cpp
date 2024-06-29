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
#ifndef CVCLControllersFasadeH
#define CVCLControllersFasadeH
//---------------------------------------------------------------------------

#include "fAuthoringAnalyserTable.h"
#include "fResoundingMapTable.h"
#include "CAnalyserControllersFasade.h"

#include "VVCLViewsContainer.h"

#include "VCLConstants.h"

    class TVCLControllersFasade
    {
    private:

	    TAuthoringAnalyserTable    * _AuthoringAnalyserForm;
        TAnalyserControllersFasade * _AnalyserFasade;


        TVCLViewsContainer	       * _ViewsContainer;

        TBool _ShowPreview;


        void _UpdateTextsList();
        void _UpdateCurrentTextInfo();
        void _UpdateKeyTextInfo();
        void _UpdateCommonTextsInfo();
        void _UpdateSelectedTextPreview();

        void _UpdateAll();

    public:

        void SetAnalyserControllersFasade(TAnalyserControllersFasade * tFasade);
        void SetViewsContainer(TVCLViewsContainer	*	tViewsContainer);
        void SetAuthoringAnalyserTable(TAuthoringAnalyserTable  * tAuthoringAnalyserTable);

        void LoadAsPrototypeText(const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle);
        void LoadAsKeyText      (const TTextString & tFileName, const TTextString & tAuthor, const TTextString & tTitle);

        void SelectText(const TUInt & tItemIndex, const TBool & tChecked);
        void SetCurrentTextAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle);
        void SetKeyTextAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle);

        TUInt TotalTextsLoaded() const;
        TBool KeyTextDefined() const;

        void SetCurrentTextAsKeyText();
        void SetKeyTextAsPrototypeText();

        void ShowPreview(const TBool & tShowPreview);
        void SetActivatedAll(const TBool & tFlag);

        void SetResoundingMapRules(const TRulesProxy & tProxy);
        void SetPrototypeTextToResoundingAnalysis();
        void SetKeyTextToResoundingAnalysis();

        void DeleteCurrentText();
        void DeleteKeyText();
        void DeleteAllTexts();

        void DoAuthoringAnalysis();
        void DoResoundingAnalysis();


        

        TVCLControllersFasade() : _ShowPreview(true)
        {
        };
    };

#endif


