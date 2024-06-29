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
#ifndef WGLGlyphDrawerH
#define WGLGlyphDrawerH
//---------------------------------------------------------------------------

#include "WGLGlyphs.h"


    class TGLGlyphDrawer : public TAbstractGLGlyphDrawer
    {
       protected:

           TGLGlyphs  _GLGlyphs;

           virtual void  _ComposeGlyphs() = 0;
           virtual void  _CalcCellDimentions() = 0;

       public:

          virtual TGLView * View() = 0;

          virtual TGLGlyphDrawer & operator << (TGLView * tView) = 0;

          virtual TBool Draw() = 0;

          virtual TGLFloat CellWidth()  const = 0;
          virtual TGLFloat CellHeight() const = 0;

          virtual void    DrawText(const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString) = 0;
          virtual void    DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor) = 0;
          virtual void    DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor) = 0;


          virtual TBool   Select (const TUInt & tWinX, const TUInt & tWinY);
          virtual TBool   Select (const TUInt & tIndex);
          virtual TBool   SelectedIndex (TUInt * tIndex);
          virtual TBool   SelectedLinkDot (TUInt * tLinkDot);

          virtual void    Clear();

          TGLGlyphDrawer() : TAbstractGLGlyphDrawer() {};
          TGLGlyphDrawer(TGLView * tView) : TAbstractGLGlyphDrawer(){};
    };



#endif
