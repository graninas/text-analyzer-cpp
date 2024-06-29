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

#ifndef WGLAssonancesPageH
#define WGLAssonancesPageH
//---------------------------------------------------------------------------
#endif


#include "BResoundingBatch.h"
#include "APage.h"

#include "CTextDataProvider.h"

#include "WGLGlyphs.h"
#include "WGLMapGlyph.h"

#include "CErrorSpecificators.h"

    class TGLAssonancesPage : public TGLGlyphDrawer, public TErrorSpecificators
    {
        private:

            TResoundingBatch  _AssonancesBatch;
            ns_Page::TPage    _Page;

            TBool _PageLoaded;
            TBool _BatchLoaded;

            TTextDataProvider * _TextDataProvider;

            virtual void  _ComposeGlyphs();
            virtual void  _CalcCellDimentions();

            TBool _IsReady() const;

        public:

           virtual   TGLView * View();
           TTextDataProvider * TextDataProvider();

           TGLAssonancesPage & operator << (const TResoundingBatch & tAssonancesBatch);
           TGLAssonancesPage & operator << (const ns_Page::TPage & tPage);

           TGLAssonancesPage & operator << (TTextDataProvider * tTextDataProvider);

           virtual TGLAssonancesPage & operator << (TGLView * tView);

           void Init(TTextDataProvider * tTextDataProvider, TGLView * tView);

              virtual TGLFloat CellWidth()  const;
              virtual TGLFloat CellHeight() const;

              virtual void    DrawText          (const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString);
              virtual void    DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor);
              virtual void    DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor);

              virtual TBool   Select (const TUInt & tWinX, const TUInt & tWinY);
              virtual TBool   Select (const TUInt & tIndex);
              virtual TBool   SelectedIndex (TUInt * tIndex);
              virtual TBool   SelectedLinkDot (TUInt * tLinkDot);

              virtual TBool    Draw();

              virtual void    Clear();


           TGLAssonancesPage() : _PageLoaded(false), _BatchLoaded(false)
           { };

           TGLAssonancesPage(TGLView * tView, TTextDataProvider * tTextDataProvider)
           : _PageLoaded(false), _BatchLoaded(false)
           { };

          ~TGLAssonancesPage() { Clear(); };
    };









