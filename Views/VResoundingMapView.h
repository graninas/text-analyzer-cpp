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
#ifndef VResoundingMapViewH
#define VResoundingMapViewH
//---------------------------------------------------------------------------

#include "WGLTextPage.h"
#include "WGLMapPage.h"

#include "ADocument.h"
#include "ACoveredPage.h"


#include "WGLDefaultWndConfigurer.h"
#include "WGLDefaultViewConfigurer.h"

#include "CSpecificatorContainer.h"

#include "BResoundingCover.h"
#include "BRulesProxy.h"


class TResoundingMapView
{
private:

             typedef TGLWindow * PGLWindow;
             typedef TGLView   * PGLView;

             typedef TSpecificatorContainer<TMPGLWindow> PGLWindows;
             typedef TSpecificatorContainer<TGLView>     TGLViews;


	ns_Document::TDocument  _Document;
    TValuesCover            _Cover;
    TResoundingCover 	    _ResoundingCover;
    TRulesProxy				_ResoundingRules;

	PGLWindows  _GLWindows;
    TGLViews    _GLViews;
    TTextString _CurrentView;

    TGLTextPage        _GLTextPage;
    TGLMapPage         _GLResoundingMapPage;

    TTextString  _ResoundingRulesList;

	void _PreparePages();

    void _SelectResoundingMapItem(const TUInt & tMouseX, const TUInt & tMouseY);

    TTextString _ComposeRulesList();

    void _SetResoundingRulesList();

public:

    void CreateGLView(const HWND & thWnd, const TSInt & tWidth, const TSInt & tHeight, const TTextString & tViewName);
	void InitGLTextPage(const TTextString & tViewName);
	void InitGLResoundingMapPage(const TTextString & tViewName);

	void NextPage();
	void PrevPage();

    void UpdateViews();
    void DrawAll();

    //void Init(TTextDataProvider * tTextDataProvider, TValuesCover tCover);
    void Init(TTextDataProvider * tTextDataProvider, TValuesCover tCover, TResoundingCover * tResCover, TRulesProxy tResoundingRules);

    void OnMouseClick(const TUInt & tMouseX, const TUInt & tMouseY)
    {
        _SelectResoundingMapItem(tMouseX, tMouseY);
    };

    TTextString RulesList()
    {
        return _ResoundingRulesList;
    };


	TResoundingMapView()
    	{};
};



#endif
