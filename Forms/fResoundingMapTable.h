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

#ifndef fResoundingMapTableH
#define fResoundingMapTableH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <ToolWin.hpp>
//---------------------------------------------------------------------------

#include <ActnList.hpp>

#include "VResoundingMapView.h"


class TResoundingMapTable : public TForm
{
__published:	// IDE-managed Components
	TImageList *ILPageNavigationIcons;
	TImageList *ILRuleNavigationIcons;
	TPanel *PMainPanel;
	TSplitter *SMainHorizontalSplitter;
	TPanel *PMainTopPanel;
	TSplitter *STopVerticalSplitter;
	TPanel *PLeftTextPanel;
	TPageControl *PCMainPages;
	TTabSheet *TSText;
	TPanel *PTextPanel;
	TPanel *PRightMapPanel;
	TPageControl *PCMapModePages;
	TTabSheet *TSResoundingMap;
	TPanel *PMapDrawingPanel1;
	TPanel *PMainBottomPanel;
	TSplitter *SBottomVerticalSplitter;
	TPanel *PLeftInfoPanel;
	TToolBar *TBPageNavigation;
	TPanel *PRightInfoPanel;
	TToolBar *TBRulesNavigation;
	TPageControl *PCRules;
	TTabSheet *TSMapRules;
	TMemo *MMapRules;
	TToolButton *ToolButton1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TToolButton *TBPageRightEnd;
	TComboBox *CBPagesList;
	TToolButton *ToolButton5;
	TToolButton *TBPrevRulePage;
	void __fastcall ToolButton2Click(TObject *Sender);
	void __fastcall ToolButton3Click(TObject *Sender);
	void __fastcall PMapDrawingPanel1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
private:	// User declarations


public:		// User declarations
	__fastcall TResoundingMapTable(TComponent* Owner);

        int  _MouseX,  _MouseY;
        
    void Init(TTextDataProvider * tTextDataProvider, TValuesCover tCover, TResoundingCover * tResoundingCover, TRulesProxy tRulesProxy);
    void SetResoundingRulesList(TTextString tRules);
};
//---------------------------------------------------------------------------
extern PACKAGE TResoundingMapTable *ResoundingMapTable;
extern PACKAGE TResoundingMapView   ResoundingMapView;
//---------------------------------------------------------------------------
#endif
