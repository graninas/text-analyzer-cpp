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
#include "ATextResoundingAnalyser.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include "CVCLFileDataLoader.h"

#include "WGLDefaultWndConfigurer.h"
#include "WGLDefaultViewConfigurer.h"

#include "UCharsValues.h"

#include "GLConstants.h"

    void TTextResoundingAnalyser::_DeleteTree()       { if (_Tree) delete _Tree; }
    void TTextResoundingAnalyser::_ClearViews()
    {
        for (TUInt i=0; i<_GLWindows.Count(); i++)
        {
           _GLWindows[i].Delete();
        };
    _GLWindows.Clear();
    _GLViews.Clear();
    }

    TTextString       * TTextResoundingAnalyser::_Data()  { return _RawDataContainer.PItem(_Alias)->Data(); }
    TTextString         TTextResoundingAnalyser::_Text()  { return _RawDataContainer.PItem(_Alias)->Text(); }
    TTextDataProvider * TTextResoundingAnalyser::_TextDataProvider()  { return _RawDataContainer.PItem(_Alias); }


    void TTextResoundingAnalyser::_TreeProcessingProc()
    {
    _TreeProcessing = true;
        _DeleteTree();
        _Tree = new  ParSentWordFSM::TCFCustomUnitDivisionTreeItem(0.0f, TRangeItem(1, _Data()->Length()));

        ParSentWordFSM::TParSenWordDescriptor D = ParSentWordFSM::Descriptor(_Tree);

               TTextStringWrapper TextWrapper(_Text());
               _fsmManager = new TFSMM(D, TextWrapper);

              _fsmManager->Process();

          delete _fsmManager;
    _TreeProcessing = false;
    };

    void TTextResoundingAnalyser::_DocumentProcessingProc()
    {
    _DocumentProcessing = true;

        _PagesCompositor = new TPagesCompositor(cDefaultRowLength, cDefaultRowsCount);

           _Document.Init(&_RawDataContainer[_Alias]);
           _Document.Copmose(_PagesCompositor);
           _Document.SetCurrentPage(0);

        delete _PagesCompositor;

    _DocumentProcessing = false;
    };


    void TTextResoundingAnalyser::_SetDefaultCharValuesMap()
    {
        _CharValuesMap = ns_CharsValues::DefaultCharValuesMap();
    }

    void TTextResoundingAnalyser::_SetDefaultSmoothRate()
    {
        _SmoothRate = cSmoothingRate;
    }


    void TTextResoundingAnalyser::_CreateMapCovers()
    {
     if (_ResoundingMapCover) delete _ResoundingMapCover;
         _ResoundingMapCover = new    TResoundingCover(TRangeItem(1, _Text().Length()));

     if (_AssonancesMapCover) delete _AssonancesMapCover;
         _AssonancesMapCover = new    TResoundingCover(TRangeItem(1, _Text().Length()));
    }

    void TTextResoundingAnalyser::_DeleteMapCovers()
    {
       if (_ResoundingMapCover) delete _ResoundingMapCover;
       if (_AssonancesMapCover) delete _AssonancesMapCover;
    };

    void TTextResoundingAnalyser::_BaseCoverProcess()
    {
    _CalculatingBaseCover = true;
        TTextStringWrapper wrapper(_Text());

    _BaseCoverProcessor = new TBaseCoverProcessor<TTextStringWrapper>(wrapper, _CharValuesMap);

           _BaseCoverProcessor->Process();

          *_ResoundingMapCover << _BaseCoverProcessor->BaseCover();
          *_AssonancesMapCover << _BaseCoverProcessor->BaseCover();

    delete _BaseCoverProcessor;

    _CalculatingBaseCover = false;
    };

    void TTextResoundingAnalyser::_RulesProcess(const TResoundingMaps & tMap)
    {
    _ProcessingRules = true;

        TTextStringWrapper wrapper(_Text());
       _RuleProcessor = new TRuleProcessor<TTextStringWrapper>(wrapper);

            if (tMap == rm_FullResoundingMap) (*_RuleProcessor) << _ResoundingRules;
            if (tMap == rm_AssonancesMap)     (*_RuleProcessor) << _AssonancesRules;

        _RuleProcessor->Process();

            if (tMap == rm_FullResoundingMap) (*_ResoundingMapCover) << _RuleProcessor->ResoundingBatch();
            if (tMap == rm_AssonancesMap)     (*_AssonancesMapCover) << _RuleProcessor->ResoundingBatch();

       delete _RuleProcessor;
    _ProcessingRules = false;
    };

    void TTextResoundingAnalyser::_CalculateMap(const TResoundingMaps & tMap)
    {
    _CalculatingMap = true;

         if (tMap == rm_FullResoundingMap) _BaseCoverProcess();
         if (tMap == rm_AssonancesMap)
         {
            if (!_AssonancesMapCover) throw EAssonancesMapNotReady();
            if (!_ResoundingMapCover) throw EResoundingMapNotReady();

            (*_AssonancesMapCover) << _ResoundingMapCover->BaseCover();
         };

         _RulesProcess(tMap);

    _CalculatingMap = false;
    };


    void TTextResoundingAnalyser::_PrepareGLTextPage()
    {
        _GLTextPage << _Document.PCurrentPage();
        _GLTextPage.Draw();
    };

    void TTextResoundingAnalyser::_PrepareGLResoundingMapPage()
    {
       if (!_ResoundingMapCover) throw EResoundingMapNotReady();

       TRangeItem   range       = _Document.CurrentPage().Range();
       TValuesCover valuesCover = _ResoundingMapCover->SmoothedCover(range, _SmoothRate);

       TCoveredPage coveredPage;
            coveredPage << _Document.CurrentPage();
            coveredPage <<  valuesCover;

      _GLResoundingMapPage << coveredPage;
      _GLResoundingMapPage.Draw();
    };

    void TTextResoundingAnalyser::_PrepareGLAssonancesMapPage()
    {
       if (!_AssonancesMapCover) throw EResoundingMapNotReady();

      _GLAssonancesMapPage << _Document.CurrentPage();
      _GLAssonancesMapPage << _ResoundingMapCover->Batch();
      _GLAssonancesMapPage.Draw();
    };


    void TTextResoundingAnalyser::_SelectResoundingMapItem(const TUInt & tMouseX, const TUInt & tMouseY)
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

    void TTextResoundingAnalyser::_SelectAssonancesMapItem(const TUInt & tMouseX, const TUInt & tMouseY)
    {
        if (_GLAssonancesMapPage.Select(tMouseX, tMouseY))
        {
        TUInt index;
             _GLAssonancesMapPage.SelectedIndex(&index);

             _GLTextPage.Select(index);
             _GLTextPage.Draw();
             _GLAssonancesMapPage.Draw();
         UpdateViews();
        _SetAssonancesRulesList();
        }
    };


    TTextString TTextResoundingAnalyser::_ComposeRulesList(const TResoundingMaps & tMap)
    {
    TResoundingCover * pCover;
    TUInt      tLinkDot;
    TRulesProxy        rulesProxy;

       if (tMap == rm_FullResoundingMap)
       {
            if (!_ResoundingMapCover) return "";
            if (!_GLResoundingMapPage.SelectedLinkDot(&tLinkDot)) return "";

            pCover = _ResoundingMapCover;
            rulesProxy = _ResoundingRules;
       }
       else if (tMap == rm_AssonancesMap)
            {
        if (!_AssonancesMapCover) return "";
        if (!_GLAssonancesMapPage.SelectedLinkDot(&tLinkDot)) return "";

            pCover = _AssonancesMapCover;
            rulesProxy = _AssonancesRules;
            };

       TResoundingBatch batch;
       TRuleResoundingItems ruleResItems;
       TResoundingItem::TLinkDots  linkDots;
       TTextString s;
       TRangeItem range;
       TUInt i,j,k,l;
       TTextString text = _Text();


           if (!pCover->Batch().PackLinkedBatch(tLinkDot, &batch)) return "";

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


    void TTextResoundingAnalyser::_SetResoundingRulesList()
    {
      _ResoundingRulesList = _ComposeRulesList(rm_FullResoundingMap);
    }

    void TTextResoundingAnalyser::_SetAssonancesRulesList()
    {
      _AssonancesRulesList = _ComposeRulesList(rm_AssonancesMap);
    }

    void TTextResoundingAnalyser::_CalculateMaps()
    {
          _CalculateMap(rm_FullResoundingMap);
          _CalculateMap(rm_AssonancesMap);
    };

    void TTextResoundingAnalyser::_ClearMaps()
    {
      if (_ResoundingMapCover) _ResoundingMapCover->Clear();
      if (_AssonancesMapCover) _AssonancesMapCover->Clear();
    }

    void TTextResoundingAnalyser::_ClearMap(const TResoundingMaps & tMap)
    {
         if (tMap == rm_FullResoundingMap) _ResoundingMapCover->Clear();
         if (tMap == rm_AssonancesMap)     _AssonancesMapCover->Clear();
    }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

    void TTextResoundingAnalyser::OnResoundingRulesChange()
    {
    _ClearMap(rm_FullResoundingMap);
         _CalculateMap(rm_FullResoundingMap);
         _PrepareGLResoundingMapPage();
         _GLResoundingMapPage.Draw();
    UpdateViews();
    };

    void TTextResoundingAnalyser::OnAssonancesRulesChange()
    {
    _ClearMap(rm_AssonancesMap);
         _CalculateMap(rm_AssonancesMap);
         _PrepareGLAssonancesMapPage();
         _GLAssonancesMapPage.Draw();
    UpdateViews();
    };

    void TTextResoundingAnalyser::OnSelectingPage()
    {
       _PrepareGLTextPage();
       _PrepareGLResoundingMapPage();
       _PrepareGLAssonancesMapPage();

    UpdateViews();
    }

    TBool TTextResoundingAnalyser::LoadText(const TTextString & tFileName)
    {
       try
       {
       TVCLFileDataLoader      _VCLFDL;
       
             TRawDataItem rdi(&_VCLFDL, tFileName);
             TUInt index = _RawDataContainer.AddItem(rdi);
            _RawDataContainer.UnvirtualizeAll();

            _Alias = _RawDataContainer[index].Alias();

            _CreateMapCovers();
            _CalculateMaps();
       }
       catch(...)  { return false; }
    return true;
    };

    void TTextResoundingAnalyser::SetAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle)
    {
       try
       {
           if (!_RawDataContainer.Count()) return;
       _LogicalTextContainer.AddItem(_Alias, tAuthor, tTitle, _RawDataContainer.PItem(_Alias)->CRC(), _RawDataContainer.PItem(_Alias));
       }
       catch (...)  { };
    };

    void TTextResoundingAnalyser::SetTreeProcessing(const TBool & tValue) {_TreeProcessing = tValue; }

    void TTextResoundingAnalyser::PrimaryProcess()
    {
    _ReadyToWork = false;

        _TreeProcessingProc();
        _DocumentProcessingProc();

    _ReadyToWork = true;
    };

    TBool TTextResoundingAnalyser::PrimaryProcessDone() { return _ReadyToWork; };

    TBool TTextResoundingAnalyser::PrimaryProcessInfo(TUInt * tMax, TUInt * tCurrent)
    {
    TUInt intdummy;
        if (_fsmManager)
        {
            _fsmManager->GetProcessInfo(&intdummy, tMax, tCurrent);
            return true;
        }
        else

           if (_PagesCompositor)
           {
        		_PagesCompositor->GetProcessInfo(&intdummy, tMax, tCurrent);
           }

    return false;
    };

    void TTextResoundingAnalyser::CreateGLView(const HWND & thWnd, const TSInt & tWidth, const TSInt & tHeight, const TTextString & tViewName)
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

    void TTextResoundingAnalyser::InitViews()
    {
        for (TUInt i=0; i<_GLWindows.Count(); i++)
           _GLWindows[i]->Init();
    }

    void TTextResoundingAnalyser::ResizeGLWindows(const TSInt & tWidth, const TSInt & tHeight, const TTextString & tViewName)
    {
       try {
//               _GLViews[tViewName].Resize(tWidth, tHeight);
       }
       catch(...) { };
    };

    void TTextResoundingAnalyser::Render(const TTextString & tViewName)
    {
        try {
              SelectView(tViewName);
             //Что-то, рисующее свои элементы.
        }
        catch(...) { };
    };

    HDC TTextResoundingAnalyser::hDC(const TTextString & tViewName)
    {
        try {
           return  _GLViews[tViewName].hDC();
        }
        catch(...) { return NULL; };
    };

    TGLWindow * TTextResoundingAnalyser::GLWindow(const TTextString & tViewName)
    {
        try {
           return  _GLWindows.PItem(tViewName)->Window();
        }
        catch(...) { return NULL; };
    };

    TGLView * TTextResoundingAnalyser::GLView(const TTextString & tViewName)
    {
        try {
           return  _GLViews.PItem(tViewName);
        }
        catch(...) { return NULL; };
    };

    TBool TTextResoundingAnalyser::SelectView  (const TTextString & tViewName)
    {
    _CurrentView = tViewName;
        try {
           return  _GLViews[tViewName].MakeCurrent();
        }
        catch(...) { return false; };
    };

    void TTextResoundingAnalyser::UpdateCurrentView()
    {
        try {
           _GLViews[_CurrentView].Update();
        }
        catch(...){ };
    };

    void TTextResoundingAnalyser::UpdateViews()
    {
        try {
            for (TUInt i=0; i<_GLViews.Count(); i++)
              _GLViews[i].Update();
        }
        catch(...) {  };
    };



    void TTextResoundingAnalyser::InitGLTextPage(const TTextString & tViewName)
    {
        _GLTextPage << &_GLViews[tViewName];
        _GLTextPage <<  _TextDataProvider();
    };

    void TTextResoundingAnalyser::InitGLResoundingMapPage(const TTextString & tViewName)
    {
        _GLResoundingMapPage << &_GLViews[tViewName];
        _GLResoundingMapPage <<  _TextDataProvider();
    };

    void TTextResoundingAnalyser::InitGLAssonancesMapPage(const TTextString & tViewName)
    {
        _GLAssonancesMapPage << &_GLViews[tViewName];
        _GLAssonancesMapPage <<  _TextDataProvider();
    };

    void TTextResoundingAnalyser::SelectPage(const TUInt & tIndex)
    {
        _Document.SetCurrentPage(tIndex);
         OnSelectingPage();
    };

    void TTextResoundingAnalyser::SelectNextPage()
    {
        _Document.NextPage();
         OnSelectingPage();
    };

    void TTextResoundingAnalyser::SelectLastPage()
    {
        _Document.LastPage();
         OnSelectingPage();
    };

    void TTextResoundingAnalyser::SelectPrevPage()
    {
        _Document.PrevPage();
         OnSelectingPage();
    };

    void TTextResoundingAnalyser::SelectFirstPage()
    {
        _Document.FirstPage();
         OnSelectingPage();
    }


    void TTextResoundingAnalyser::SetResoundingMapRules(const TRulesProxy & tProxy)
    {
        _ResoundingRules = tProxy;
    };

    void TTextResoundingAnalyser::SetAssonansesMapRules(const TRulesProxy & tProxy)
    {
        _AssonancesRules = tProxy;
    }


    void  TTextResoundingAnalyser::OnResoundingMapClick(const TUInt & tMouseX, const TUInt & tMouseY)
    {
        _SelectResoundingMapItem(tMouseX, tMouseY);
    };

    void  TTextResoundingAnalyser::OnAssonancesMapClick(const TUInt & tMouseX, const TUInt & tMouseY)
    {
        _SelectAssonancesMapItem(tMouseX, tMouseY);
    };

    void TTextResoundingAnalyser::ClearAll()
    {
        _RawDataContainer.Clear();
        _LogicalTextContainer.Clear();
        _Document.Clear();
        _ClearViews();
        _GLTextPage.Clear();
        _GLResoundingMapPage.Clear();
        _GLAssonancesMapPage.Clear();
//        _ResoundingRules.Clear();
//        _AssonancesRules.Clear();

        _DeleteMapCovers();
    };


    void TTextResoundingAnalyser::DrawAll()
    {
/*       _GLTextPage.Draw();
       _GLResoundingMapPage.Draw();
       _GLAssonancesMapPage.Draw();       */
    UpdateViews();
    }

    TTextString TTextResoundingAnalyser::GetResoundigRulesList()
    {
       return _ResoundingRulesList;
    }

    TTextString TTextResoundingAnalyser::GetAssonancesRulesList()
    {
       return _AssonancesRulesList;
    }


    TBool TTextResoundingAnalyser::ReadyToWork() const { return _ReadyToWork; }

    TTextDataProvider * TTextResoundingAnalyser::TextDataProvider() { return _RawDataContainer.PItem(_Alias); }

    TTextResoundingAnalyser::TTextResoundingAnalyser() : _SmoothRate(1), _fsmManager(NULL), _PagesCompositor(NULL), _Tree(NULL), _ReadyToWork(false), _Document(),
      _GLTextPage(), _ResoundingMapCover(NULL), _BaseCoverProcessor(NULL), _RuleProcessor(NULL), _AssonancesRules(), _ResoundingRules(),
      _CurrentView(""), _DocumentProcessing(false), _TreeProcessing(false), _CalculatingMap(false), _GLResoundingMapPage(), _GLAssonancesMapPage(),
      _CalculatingBaseCover(false), _ProcessingRules(false), _AssonancesRulesList(""), _ResoundingRulesList("")

    {
       _SetDefaultCharValuesMap();
       _SetDefaultSmoothRate();
    };

    TTextResoundingAnalyser::~TTextResoundingAnalyser()
    {
//       ClearAll();
    _DeleteTree();
    };

