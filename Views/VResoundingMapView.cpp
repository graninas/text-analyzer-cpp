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
#include "VResoundingMapView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "APagesCompositor.H"
#include "GLConstants.H"
#include "BRulesProxy.h"

	void TResoundingMapView::_PreparePages()
    {
    TCoveredPage coveredPage;
	    coveredPage << _Document.CurrentPage() << _Cover.Part(_Document.CurrentPage().Range().From(), _Document.CurrentPage().Range().To());

        _GLResoundingMapPage << coveredPage;
	    _GLTextPage << _Document.PCurrentPage();

        _GLTextPage.Draw();
        _GLResoundingMapPage.Draw();
    };

    void TResoundingMapView::_SelectResoundingMapItem(const TUInt & tMouseX, const TUInt & tMouseY)
    {
        if (_GLResoundingMapPage.Select(tMouseX, tMouseY))
        {
        TUInt index;
             _GLResoundingMapPage.SelectedIndex(&index);

             _GLTextPage.Select(index);
             _GLTextPage.Draw();
             _GLResoundingMapPage.Draw();
         UpdateViews();
        _SetResoundingRulesList();
        }
    };

    TTextString TResoundingMapView::_ComposeRulesList()
    {
    TUInt      tLinkDot;
    TRulesProxy        rulesProxy;

            if (!_GLResoundingMapPage.SelectedLinkDot(&tLinkDot)) return "";

            rulesProxy = _ResoundingRules;

       TResoundingBatch batch;
       TRuleResoundingItems ruleResItems;
       TResoundingItem::TLinkDots  linkDots;
       TTextString s;
       TRangeItem range;
       TUInt i,j,k,l;
       TTextString text = _Document.Text();


           if (!_ResoundingCover.Batch().PackLinkedBatch(tLinkDot, &batch)) return "";

//           s += text[tLinkDot] + " : " + cWinParagraph;
           s += "===================================" + cWinParagraph;


           for (j=0; j<batch.Count(); j++)
           {
           ruleResItems = batch[j];
           TRule rule(rulesProxy.RuleByNumber(ruleResItems.RuleNumber()));

               s += "Номер правила: " + IntToStr(rule.Number()) + cWinParagraph;
               s += "Описание: " + rule.Description() + cWinParagraph;
               s += "Найденные элементы:" + cWinParagraph;

               for (k=0; k<ruleResItems.Count(); k++)
               {
               range    = ruleResItems[k].AffectedRange();
               linkDots = ruleResItems[k].LinkDots();
           s += IntToStr(k+1) + "). ""..." + text.SubString(range.From(), range.Length()) + "...""" + cWinParagraph;

           for (l=0; l<linkDots.size(); l++)
           s += text[linkDots[l]];
               };
           s += cWinParagraph + "-----------------------------------" + cWinParagraph;
           };
    return s;
    }

    void TResoundingMapView::_SetResoundingRulesList()
    {
      _ResoundingRulesList = _ComposeRulesList();
    }


    void TResoundingMapView::CreateGLView(const HWND & thWnd, const TSInt & tWidth, const TSInt & tHeight, const TTextString & tViewName)
    {
    TGLDefaultWndConfigurer  glWndConf(tWidth, tHeight, tViewName, thWnd);
    TGLDefaultViewConfigurer glViewConf;

    TMPGLWindow _pmWnd;
        _pmWnd << &glWndConf;

        _GLWindows.AddItem( &_pmWnd );
        _GLViews.AddItem(TGLView(tViewName) << &glViewConf);

    _GLViews[tViewName] << _pmWnd.Window();

    _CurrentView = tViewName;
    };

	void TResoundingMapView::InitGLTextPage(const TTextString & tViewName)
    {
        _GLTextPage << &_GLViews[tViewName];
        _GLTextPage << _Document.TextDataProvider();
    };

	void TResoundingMapView::InitGLResoundingMapPage(const TTextString & tViewName)
    {
        _GLResoundingMapPage << &_GLViews[tViewName];
        _GLResoundingMapPage <<  _Document.TextDataProvider();
    };


	void TResoundingMapView::NextPage()
    {
    	_Document.NextPage();
    	DrawAll();
    };

	void TResoundingMapView::PrevPage()
    {
    	_Document.PrevPage();
    	DrawAll();
    };

    void TResoundingMapView::UpdateViews()
    {
        try {
            for (TUInt i=0; i<_GLViews.Count(); i++)
              _GLViews[i].Update();
        }
        catch(...) {  };
    };

    void TResoundingMapView::DrawAll()
    {
    	_PreparePages();
        UpdateViews();
    }

    void TResoundingMapView::Init(TTextDataProvider * tTextDataProvider, TValuesCover tCover, TResoundingCover * tResCover, TRulesProxy tResoundingRules)
    {
       TPagesCompositor pagesCompositor(cDefaultRowLength, cDefaultRowsCount);

           _Document.Init(tTextDataProvider);
           _Document.Copmose(&pagesCompositor);
           _Document.SetCurrentPage(0);

        _Cover = tCover;
        _ResoundingCover = (*tResCover);
        _ResoundingRules = tResoundingRules;
    };
