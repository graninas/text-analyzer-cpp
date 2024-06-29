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
#ifndef GLConstantsH
#define GLConstantsH
//---------------------------------------------------------------------------

#include "GLStructs.h"
//Настройки проекции и камеры по умолчанию.

const TGLFloat cGLEyePosX = 0.0f;
const TGLFloat cGLEyePosY = 0.0f;
const TGLFloat cGLEyePosZ = -10.0f;
   const TGLFloat cGLEyeViewX = 0.0f;
   const TGLFloat cGLEyeViewY = 0.0f;
   const TGLFloat cGLEyeViewZ = 0.0f;
      const TGLFloat cGLEyeUpVectorX = 0.0f;
      const TGLFloat cGLEyeUpVectorY = -1.0f;
      const TGLFloat cGLEyeUpVectorZ = 0.0f;


const TProjectionTypes cGLProjectionType = ptOrtho;

const cGLClippingRegionNear = 1;
const cGLClippingRegionFar  = 100;


//Константы масштабирования, приводящие координаты GL и оконные координаты почти
//в полное соответствие при данных настройках проекции и камеры.
//Все остальные координаты "проекционной камеры" должны быть 0.0f
/*const TGLFloat cGLXProportionalScale = 0.92f;
const TGLFloat cGLYProportionalScale = 0.956f;
const TGLFloat cGLZProportionalScale = 1.0f;       */

const TGLFloat cGLXProportionalScale = 1.0f;
const TGLFloat cGLYProportionalScale = 1.0f;
const TGLFloat cGLZProportionalScale = 1.0f;


const TGLBool  cUseCornerCenteredCoordinates = true;

/////////////////////////////////////////////////////////////

TGLFloat GLX(TGLFloat tX)
{
    if (cGLEyeUpVectorX >= 0)
      return tX;
return -tX;
};

TGLFloat GLY(TGLFloat tY)
{
    if (cGLEyeUpVectorY >= 0)
      return tY;
return -tY;
};

TGLFloat GLZ(TGLFloat tZ)
{
    if (cGLEyeUpVectorZ >= 0)
      return tZ;
return -tZ;
};
/////////////////////////////////////////////////////////////


const TGLColor4f cGLClearColor = {0.0f, 0.0f, 0.0f, 1.0f};

const cDefaultFrontFace       = GL_CW;
const cDefaultShadeModel      = GL_SMOOTH;

/////////////////////////////////////////////////////////////

const TGLColor3f cDefaultTextColor    = {0.8f, 0.8f, 0.8f};
const TGLColor3f cDefaultMapItemColor = {0.8f, 0.8f, 0.8f};
const TGLColor3f cDefaultAssonancesItemColor = {0.3f, 0.8f, 0.3f};
const TGLColor3f cMapBorderColor      = {0.0f, 0.0f, 1.0f};
const TGLColor3f cMapSelectedColor    = {1.0f, 1.0f, 1.0f};
const TGLColor3f cMapSelectedBorderColor = {0.0f, 1.0f, 0.0f};
const TGLColor3f cTextSelectedColor   = {1.0f, 0.0f, 0.0f};

const TGLFloat   cColorChangeValue    = cDefaultMapItemColor[2] / 2;

const TGLFloat   cDefaultZValue = -1.0f;

const TGLFloat   cMapBorderZTranslation  = cDefaultZValue - 0.01;

const TGLFloat   cMinValueDivOnZeroProtection = -0.1;
const TGLFloat   cMaxValueDivOnZeroProtection =  0.1;

const TGLFloat cCellWSpacingPercent = 1 - 0.02f;
const TGLFloat cCellHSpacingPercent = 1 - 0.02f;

const TGLFloat cCellWSpacingDoublePercent = 2 * cCellWSpacingPercent;
const TGLFloat cCellHSpacingDoublePercent = 2 * cCellHSpacingPercent;


const TGLFloat cSideField           = 10.0f;

const TGLUInt      cDefaultFontSize  = -11;
const TTextString  cDefaultFont      = "Courier New";
const DWORD        cDefaultCharSet   = DEFAULT_CHARSET;//ANSI_CHARSET; //OEM_CHARSET , DEFAULT_CHARSET

const DWORD        cDefaultFontBold  = FW_BOLD;
const DWORD        cDefaultItalic    = 0;
const DWORD        cDefaultUnderline = 0;
const DWORD        cDefaultStriked   = 0;

/////////////////////////////////////////////////////////////////////////////

const TUInt cDefaultRowLength  = 30;
const TUInt cDefaultRowsCount  = 16;

const TUInt cSmoothingRate     = 1;

/////////////////////////////////////////////////////////////////////////////

enum  TFontCalcType {fct_ByCell, fct_ByGlyph};

const TFontCalcType cFontCalcType = fct_ByGlyph;

const TGLFloat cWCellFontRatio = 0.6514f;
const TGLFloat cHCellFontRatio = 0.7815f;

   TGLUInt cGetFontSize(const TGLFloat & tCellWidth, const TGLFloat & tCellHeight)
   {
       TGLUInt   res;
       TGLFloat  hRatio = tCellHeight / cHCellFontRatio;
       TGLFloat  wRatio = tCellWidth /  cWCellFontRatio;

//       TGLFloat  averageRatio = (hRatio + wRatio) / 2;
         TGLFloat  smallest = wRatio;

           if (hRatio < wRatio) smallest = hRatio;

       res = TGLUInt(smallest);
   return res;
   };


const TGLFloat cHFontRasterPosRatio = 0.3526f;
const TGLFloat cWFontRasterPosRatio = 0.3901F;

   TGLUInt cGetHRasterPos(const TGLUInt & tFontSize)
   {
       TGLUInt   res;
       TGLFloat  hRatio = tFontSize * cHFontRasterPosRatio;

       res = TGLUInt(hRatio);
   return res;
   };

   TGLUInt cGetWRasterPos(const TGLUInt & tFontSize)
   {
       TGLUInt   res;
       TGLFloat  wRatio = tFontSize * cWFontRasterPosRatio;

       res = TGLUInt(wRatio);
   return res;
   };


#endif
