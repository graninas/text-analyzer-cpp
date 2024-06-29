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
#include "WGLMapGlyph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include "GLConstants.h"



    void TGLMapGlyph::_CalculateBorders()
    {
      TSFloat cellW = _Drawer->CellWidth()  * cCellWSpacingDoublePercent;
      TSFloat cellH = _Drawer->CellHeight() * cCellHSpacingDoublePercent;

         TGLFloat cellCorner1X = _ColIndex * cellW + cCellWSpacingPercent;
         TGLFloat cellCorner1Y = _RowIndex * cellH + cCellHSpacingPercent;

        _CellRect.Point1().XY.X = cellCorner1X;
        _CellRect.Point1().XY.Y = cellCorner1Y;
       _CellRect.Point2().XY.X = cellCorner1X + cellW;
       _CellRect.Point2().XY.Y = cellCorner1Y + cellH;
    };


    void TGLMapGlyph::Draw()
    {
      TGLColor3f border;
      TGLColor3f color;

       if (_Selected)
       {
          color[0] = cMapSelectedColor[0];
          color[1] = cMapSelectedColor[1];
          color[2] = cMapSelectedColor[2];

          border[0] = cMapSelectedBorderColor[0];
          border[1] = cMapSelectedBorderColor[1];
          border[2] = cMapSelectedBorderColor[2];
       }
       else
       {
          color[0] = _Color[0];
          color[1] = _Color[1];
          color[2] = _Color[2];

          border[0] = cMapBorderColor[0];
          border[1] = cMapBorderColor[1];
          border[2] = cMapBorderColor[2];
       }

          _Drawer->DrawRectangle(_CellRect.Point1().X(), _CellRect.Point1().Y(), _CellRect.Point2().X(), _CellRect.Point2().Y(), cDefaultZValue, color);
          _Drawer->DrawEmptyRectangle(_CellRect.Point1().X(), _CellRect.Point1().Y(), _CellRect.Point2().X(), _CellRect.Point2().Y(), cMapBorderZTranslation, border);
    };

