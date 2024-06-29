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
#ifndef VCLConstantsH
#define VCLConstantsH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "UTypes.h"

const TThreadPriority cPrimaryProcessThreadPriority = tpNormal;
const TThreadPriority cMainUpdateThreadPriority     = tpNormal;

////////////////////////////////////////////////////////////////////////////////

const TTextString cTextViewName = "TextView";
const TTextString cMapView1Name = "MapView1";
const TTextString cMapView2Name = "MapView2";
const TTextString cFleschViewName = "FleschView";

////////////////////////////////////////////////////////////////////////////////

const TTextString cCurrentTextInfo        = "CurrentTextInfo";
const TTextString cCurrentTextControls    = "CurrentTextControls";
const TTextString cKeyTextInfo            = "KeyTextInfo";
const TTextString cKeyTextControls        = "KeyTextControls";

const TTextString cSelectedTextInfo       = "SelectedTextInfo";

const TTextString cKeyTextDefinedLabel    = "KeyTextDefinedLabel";
const TTextString cKeyTextNotDefinedLabel = "KeyTextNotDefinedLabel";

const TTextString cSelectedTextPreview    = "SelectedTextPreview";
const TTextString cAllViews				  = "AllViews";

////////////////////////////////////////////////////////////////////////////////

#endif
