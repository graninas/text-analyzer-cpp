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
#include "WGLGlyph.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"



////////////////////////////////////////////////////////////////////////////////

      void TAbstractGLGlyphDrawer::_CalcCellDimentions()
      {
      TGLRect tGLWndRect = _View->Rect();

        TGLFloat regionWidth  = tGLWndRect.Point2().X() - tGLWndRect.Point1().X();
        TGLFloat regionHeight = tGLWndRect.Point2().Y() - tGLWndRect.Point1().Y();

        _CellWidth  = regionWidth  - cSideField*2;
        _CellHeight = regionHeight - cSideField*2;
      };


      TGLView * TAbstractGLGlyphDrawer::View() { return _View; };

        TGLFloat TAbstractGLGlyphDrawer::CellWidth()  const { return _CellWidth; };
        TGLFloat TAbstractGLGlyphDrawer::CellHeight() const { return _CellHeight; };

      TBool TAbstractGLGlyphDrawer::Draw()
      {
         if (!_View) return false;
      return (_View->MakeCurrent());
      };

     TAbstractGLGlyphDrawer & TAbstractGLGlyphDrawer::operator << (TGLView * tView)
     {
         _View = tView;
     return *this;
     };

////////////////////////////////////////////////////////////////////////////////


    void TGLGlyph::_SetColor(const TGLColor3f tColor)
    {
        _Color[0] = tColor[0];
        _Color[1] = tColor[1];
        _Color[2] = tColor[2];
    }

    void TGLGlyph::_CalculateBorders()
    {
      TSFloat cellW = _Drawer->CellWidth();
      TSFloat cellH = _Drawer->CellHeight();

         TGLFloat cellCorner1X = _ColIndex * cellW;
         TGLFloat cellCorner1Y = _RowIndex * cellH;

        _CellRect.Point1().XY.X = cellCorner1X;
        _CellRect.Point1().XY.Y = cellCorner1Y;
       _CellRect.Point2().XY.X = cellCorner1X + cellW;
       _CellRect.Point2().XY.Y = cellCorner1Y + cellH;
    };


    TBool TGLGlyph::Selected() const
    {
        return _Selected;
    };

    void  TGLGlyph::Select()
    {
        _Selected = true;
    };

    void  TGLGlyph::UnSelect()
    {
        _Selected = false;
    };

    TBool TGLGlyph::Intersects(const TGLFloat & tX, const TGLFloat & tY)
    {
      if
      (
        ((_CellRect.Point1().X() <= tX) &&
        (_CellRect.Point2().X() >= tX) &&

        (_CellRect.Point1().Y() <= tY) &&
        (_CellRect.Point2().Y() >= tY))

        ||

       ((_CellRect.Point1().X() >= tX) &&
        (_CellRect.Point2().X() <= tX) &&

        (_CellRect.Point1().Y() >= tY) &&
        (_CellRect.Point2().Y() <= tY))
      )
      return true;

    return false;
    };


    void TGLGlyph::Draw()
    {

    };

    void TGLGlyph::Color(TGLColor3f tColor)
    {
        tColor[0] = _Color[0];
        tColor[1] = _Color[1];
        tColor[2] = _Color[2];
    };


     TGLRect TGLGlyph::CellRect()  const { return _CellRect;  };
     TUInt   TGLGlyph::RowIndex()  const { return _RowIndex;  };
     TUInt   TGLGlyph::ColIndex()  const { return _ColIndex;  };

////////////////////////////////////////////////////////////////////////////////


