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
#ifndef ATextResoundingAnalyserH
#define ATextResoundingAnalyserH
//---------------------------------------------------------------------------

#include "CSpecificatorContainer.h"

#include "CRawDataContainer.h"
#include "CLogicalTextsContainer.h"

#include "UParSentWordFSM.h"

#include "CFiniteStateMachineManager.h"
#include "FiniteStateMachine.h"
#include "CStateMachineDescriptor.h"
#include "CTextStringWrapper.h"

#include "ADocument.h"
#include "WGLTextPage.h"
#include "WGLMapPage.h"
#include "WGLAssonancesPage.h"
#include "BRuleProcessor.h"
#include "BResoundingCover.h"
#include "CBaseCoverProcessor.h"



 #define TState ParSentWordFSM::TState
 #define TEvent ParSentWordFSM::TEvent
 #define TFSMachine FSM::SFiniteStateMachine<TState, TEvent, FSM::SOnEnterFunctor<TState, TEvent>, FSM::SThrowStrategy<TEvent> >
 #define TFSMM  TFiniteStateMachineManager<TEvent, TFSMachine, ParSentWordFSM::TParSenWordDescriptor, TTextStringWrapper>

    class TTextResoundingAnalyser
    {
        public:

        class EAssonancesMapNotReady{};
        class EResoundingMapNotReady{};

             enum TResoundingMaps {rm_FullResoundingMap, rm_AssonancesMap, rm_FleschMap};

             typedef TGLWindow * PGLWindow;
             typedef TGLView   * PGLView;

             typedef TSpecificatorContainer<TMPGLWindow> PGLWindows;
             typedef TSpecificatorContainer<TGLView>     TGLViews;

        private:

            TRawDataContainer       _RawDataContainer;
            TLogicalTextsContainer  _LogicalTextContainer;

            TTextString _Alias;


            ParSentWordFSM::TCFCustomUnitDivisionTreeItem * _Tree;
            TFSMM * _fsmManager;

            ns_Document::TDocument  _Document;
            TPagesCompositor    *   _PagesCompositor;


            PGLWindows  _GLWindows;
            TGLViews    _GLViews;
            TTextString _CurrentView;


            TGLTextPage        _GLTextPage;
            TGLMapPage         _GLResoundingMapPage;
            TGLAssonancesPage  _GLAssonancesMapPage;

            TRulesProxy _ResoundingRules;
            TRulesProxy _AssonancesRules;

            TResoundingCover * _ResoundingMapCover;
            TResoundingCover * _AssonancesMapCover;

            TBaseCoverProcessor<TTextStringWrapper> * _BaseCoverProcessor;
            TRuleProcessor<TTextStringWrapper>      * _RuleProcessor;

            TBool _TreeProcessing;
            TBool _DocumentProcessing;
            TBool _ReadyToWork;

            TBool _CalculatingMap;
            TBool _CalculatingBaseCover;
            TBool _ProcessingRules;

            TValuesCover _CharValuesMap;
            TUInt        _SmoothRate;

            TTextString  _AssonancesRulesList;
            TTextString  _ResoundingRulesList;


            void _DeleteTree();
            void _ClearViews();


            TTextString       * _Data();
            TTextString         _Text();
            TTextDataProvider * _TextDataProvider();


            void _TreeProcessingProc();

            void _DocumentProcessingProc();

            void _SetDefaultCharValuesMap();
            void _SetDefaultSmoothRate();

            void _CreateMapCovers();
            void _DeleteMapCovers();

            void _BaseCoverProcess();
            void _RulesProcess(const TResoundingMaps & tMap);

            void _CalculateMap(const TResoundingMaps & tMap);

            void _PrepareGLTextPage();
            void _PrepareGLResoundingMapPage();
            void _PrepareGLAssonancesMapPage();

            void _SelectResoundingMapItem(const TUInt & tMouseX, const TUInt & tMouseY);
            void _SelectAssonancesMapItem(const TUInt & tMouseX, const TUInt & tMouseY);

            TTextString _ComposeRulesList(const TResoundingMaps & tMap);

            void _SetResoundingRulesList();
            void _SetAssonancesRulesList();

            void _CalculateMaps();
            void _ClearMaps();
            void _ClearMap(const TResoundingMaps & tMap);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


        public:

            void OnResoundingRulesChange();
            void OnAssonancesRulesChange();

            void OnSelectingPage();

            TBool LoadText(const TTextString & tFileName);

            void SetAuthorAndTitle(const TTextString & tAuthor, const TTextString & tTitle);
            void SetTreeProcessing(const TBool & tValue);

            void  PrimaryProcess();
            TBool PrimaryProcessDone();
            TBool PrimaryProcessInfo(TUInt * tMax, TUInt * tCurrent);

            void CreateGLView(const HWND & thWnd, const TSInt & tWidth, const TSInt & tHeight, const TTextString & tViewName);
            void InitViews();

            void ResizeGLWindows(const TSInt & tWidth, const TSInt & tHeight, const TTextString & tViewName);

            void Render(const TTextString & tViewName);

            HDC hDC(const TTextString & tViewName);

            TGLWindow * GLWindow(const TTextString & tViewName);
            TGLView * GLView(const TTextString & tViewName);

            TBool SelectView  (const TTextString & tViewName);
            void UpdateCurrentView();
            void UpdateViews();

            void InitGLTextPage(const TTextString & tViewName);
            void InitGLResoundingMapPage(const TTextString & tViewName);
            void InitGLAssonancesMapPage(const TTextString & tViewName);

            void SelectPage(const TUInt & tIndex);
            void SelectNextPage();
            void SelectLastPage();
            void SelectPrevPage();
            void SelectFirstPage();

            void SetResoundingMapRules(const TRulesProxy & tProxy);
            void SetAssonansesMapRules(const TRulesProxy & tProxy);

            void  OnResoundingMapClick(const TUInt & tMouseX, const TUInt & tMouseY);
            void  OnAssonancesMapClick(const TUInt & tMouseX, const TUInt & tMouseY);

            void ClearAll();
            void DrawAll();

            TTextString GetResoundigRulesList();
            TTextString GetAssonancesRulesList();

            TBool ReadyToWork() const;

            TTextDataProvider * TextDataProvider();

            TTextResoundingAnalyser();
           ~TTextResoundingAnalyser();
    };



#endif
