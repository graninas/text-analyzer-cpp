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
#ifndef WGLTextPageH
#define WGLTextPageH
//---------------------------------------------------------------------------


#include "APage.h"
#include "CTextDataProvider.h"

#include "WGLTextGlyph.h"

#include "GLText.h"

#include "CErrorSpecificators.h"

    class TGLTextPage : public TGLGlyphDrawer, public TErrorSpecificators
    {
        private:

            ns_Page::TPage    * _Page;

            TTextDataProvider * _TextDataProvider;

            TGLText  _GLText;
            TGLFont  _GLFont;

            TGLUInt  _FontSize;
            TGLFloat _WRasterPos;
            TGLFloat _HRasterPos;

            void         _ComposeGlyphs();
            void         _BuildFont();

            virtual void _CalcCellDimentions();

        public:

           virtual   TGLView * View();
           TTextDataProvider * TextDataProvider();

           TGLTextPage & operator << (ns_Page::TPage    * tPage);
           TGLTextPage & operator << (TTextDataProvider * tTextDataProvider);

           virtual TGLTextPage & operator << (TGLView   * tView);

           void Init(TTextDataProvider * tTextDataProvider, TGLView * tView);

              virtual TGLFloat CellWidth()  const;
              virtual TGLFloat CellHeight() const;

              virtual void    DrawText          (const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString);
              virtual void    DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor)   {};
              virtual void    DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor)   {};

              virtual TBool    Draw();

              virtual TBool   Select (const TUInt & tWinX, const TUInt & tWinY);
              virtual TBool   Select (const TUInt & tIndex);
              virtual TBool   SelectedIndex (TUInt * tIndex);
              virtual TBool   SelectedLinkDot (TUInt * tLinkDot);

              virtual void    Clear();


           TGLTextPage();

           TGLTextPage(TGLView * tView, TTextDataProvider * tTextDataProvider);

          ~TGLTextPage() { Clear(); };
    };




#endif
