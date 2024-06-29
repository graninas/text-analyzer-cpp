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

#ifndef fPrimaryTextLoadingH
#define fPrimaryTextLoadingH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------

#include "ATextResoundingAnalyser.h"

class TPrimaryTextLoading : public TForm
{
__published:	// IDE-managed Components
    TPanel *PTextDataEntering;
    TPanel *PPrimapyProcess;
    TLabel *LPrimaryProcessInfo;
    TPanel *PReadyBtn;
    TButton *BtnReady;
    TProgressBar *PBPrimaryProcessProgress;
    TLabel *LPrimaryProcessPercent;
    TLabel *LDataEnteringInfo;
    TEdit *EAuthorName;
    TEdit *ETitle;
    TImage *IPrimaryProcessDemo;
    TLabel *LAuthorName;
    TLabel *LTextTitle;
    TPanel *PPrimaryProcessInfoAlign;
    TActionList *PrimaryTextLoadingActions;
    TAction *AReadyClick;
    TImageList *ILProcess;
    TAction *AEnableReady;
    TButton *Button1;
    TAction *ACalcel;
    void __fastcall AEnableReadyExecute(TObject *Sender);
    void __fastcall AReadyClickExecute(TObject *Sender);
private:	// User declarations

    int _CurBitmapIndex;

    int _NextBitmapIndex();

    TTextResoundingAnalyser * _Analyser;

public:		// User declarations
    __fastcall TPrimaryTextLoading(TComponent* Owner);


    void   __fastcall UpdateProcess(const int & tMax, const int & tCurrent);

    void              SetAnalyser(TTextResoundingAnalyser * tAnalyser);

    void   __fastcall GoPrimaryProcess();
};
//---------------------------------------------------------------------------
extern PACKAGE TPrimaryTextLoading *PrimaryTextLoading;
//---------------------------------------------------------------------------
#endif
