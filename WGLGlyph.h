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
#ifndef WGLGlyphH
#define WGLGlyphH
//---------------------------------------------------------------------------

#include "WGLView.h"
#include "GLStructs.h"


class TGLGlyph;


    class TAbstractGLGlyphDrawer
    {
       protected:

           TGLView  * _View;

            TGLFloat _CellWidth;
            TGLFloat _CellHeight;

           virtual void  _ComposeGlyphs() = 0;
           virtual void  _CalcCellDimentions() = 0;

       public:

          virtual TGLView * View() = 0;

          virtual TAbstractGLGlyphDrawer & operator << (TGLView * tView) = 0;

          virtual TBool Draw() = 0;

          virtual TGLFloat CellWidth()  const = 0;
          virtual TGLFloat CellHeight() const = 0;

          virtual void    DrawText(const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString) = 0;
          virtual void    DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor) = 0;
          virtual void    DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor) = 0;

          TAbstractGLGlyphDrawer() : _View(NULL), _CellWidth(0.0f), _CellHeight(0.0f) {};
          TAbstractGLGlyphDrawer(TGLView * tView) : _View(tView), _CellWidth(0.0f), _CellHeight(0.0f){};
    };

////////////////////////////////////////////////////////////////////////////////
 
    class TGLGlyph
    {
       protected:

          TGLColor3f  _Color;
          TGLRect     _CellRect;

          TUInt _RowIndex;
          TUInt _ColIndex;

          TBool    _Selected;

          TAbstractGLGlyphDrawer * _Drawer;

          virtual void _SetColor(const TGLColor3f tColor);

          virtual void _CalculateBorders();

       public:

          virtual TBool Selected() const;
          virtual void  Select();
          virtual void  UnSelect();
          virtual TBool Intersects(const TGLFloat & tX, const TGLFloat & tY);

          virtual void Draw();

          virtual void Color(TGLColor3f tColor);


          virtual TGLRect CellRect()  const;
          virtual TUInt   RowIndex()  const;
          virtual TUInt   ColIndex()  const;



          TGLGlyph(const TGLColor3f tColor, TAbstractGLGlyphDrawer * tDrawer, const TUInt & tRowIndex,
                   const TUInt & tColIndex)
          : _Drawer(tDrawer), _RowIndex(tRowIndex), _ColIndex(tColIndex), _Selected(false)
          {
             _SetColor(tColor);
             _CalculateBorders();
          };
    };






#endif


