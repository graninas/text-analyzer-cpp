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
#include "WGLAssonancesPage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"


      TBool TGLAssonancesPage::_IsReady() const
      {
          return (_PageLoaded && _BatchLoaded) ? true : false;
      };

      void TGLAssonancesPage::_ComposeGlyphs()
      {
      if (!_TextDataProvider) throw EInvalidDataProvider();
      View()->ForbidUpdate();
      
      _GLGlyphs.Free();

       TGLMapGlyph * pGlyph;
       TGLColor3f    color;
       TUInt linkDot;

          color[0] = cDefaultAssonancesItemColor[0];
          color[1] = cDefaultAssonancesItemColor[1];
          color[2] = cDefaultAssonancesItemColor[2];

           for (TUInt i=0; i<_Page.Count(); i++)
              for (TUInt j=0; j<_Page.RowLength(i); j++)
              {
                 linkDot = _Page.TextIndex(i,j);

                 if (_AssonancesBatch.Intersects(linkDot))
                 {
                      pGlyph = new TGLMapGlyph(linkDot, i, j, color, this);
                     _GLGlyphs.AddGlyph(pGlyph);
                 };
              };

      View()->AllowUpdate();
      };

      void TGLAssonancesPage::_CalcCellDimentions()
      {
           TGLGlyphDrawer::_CalcCellDimentions();

          _CellWidth  = _CellWidth  / _Page.MaxRowLength();
          _CellHeight = _CellHeight / _Page.RowsCount();
      };

     TGLView           * TGLAssonancesPage::View() { return TGLGlyphDrawer::View(); };
     TTextDataProvider * TGLAssonancesPage::TextDataProvider() { return _TextDataProvider; };

     TGLAssonancesPage & TGLAssonancesPage::operator << (const ns_Page::TPage & tPage)
     {
         _Page = tPage;
         _PageLoaded = true;

         if (_IsReady())
         {
             _CalcCellDimentions();
             _ComposeGlyphs();
         }

     return *this;
     };

     TGLAssonancesPage & TGLAssonancesPage::operator << (const TResoundingBatch & tAssonancesBatch)
     {
         _AssonancesBatch = tAssonancesBatch;
         _BatchLoaded = true;

         if (_IsReady())
         {
             _CalcCellDimentions();
             _ComposeGlyphs();
         }
     return *this;
     };

     TGLAssonancesPage & TGLAssonancesPage::operator << (TTextDataProvider * tTextDataProvider)
     {
         _TextDataProvider = tTextDataProvider;
     return *this;
     };

     TGLAssonancesPage & TGLAssonancesPage::operator << (TGLView * tView)
     {
         TGLGlyphDrawer::operator<<(tView);
     return *this;
     };

     void TGLAssonancesPage::Init(TTextDataProvider * tTextDataProvider, TGLView * tView)
     {
         *this << tTextDataProvider;
         *this << tView;
     };

        TGLFloat TGLAssonancesPage::CellWidth()  const { return TGLGlyphDrawer::CellWidth(); };
        TGLFloat TGLAssonancesPage::CellHeight() const { return TGLGlyphDrawer::CellHeight(); };


   void  TGLAssonancesPage::DrawText          (const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString)
   {
   };

   void  TGLAssonancesPage::DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2, const TGLFloat & tZ, TGLColor3f tColor)
   {
       _View->Window()->DrawRectangle(tX1, tY1, tX2, tY2, tZ, tColor);
   };

   void  TGLAssonancesPage::DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor)
   {
       _View->Window()->DrawEmptyRectangle(tX1, tY1, tX2, tY2, tZ, tColor);
   };


     TBool TGLAssonancesPage::Draw()
     {
     if (!TGLGlyphDrawer::Draw()) return false;
     View()->ForbidUpdate();

       glPushMatrix();
       glTranslatef(cSideField, cSideField, 0.0f);

         for (TUInt i=0; i<_GLGlyphs.Count(); i++)
         {
           _GLGlyphs[i]->Draw();
         };
       glPopMatrix();

     View()->AllowUpdate();
     return true;
     };

     void TGLAssonancesPage::Clear()
     {
         _GLGlyphs.Free();
         _Page.Clear();
         _AssonancesBatch.Clear();
         _PageLoaded = false;
         _BatchLoaded = false;
     };


          TBool  TGLAssonancesPage::Select (const TUInt & tWinX, const TUInt & tWinY)
          {
              return TGLGlyphDrawer::Select (tWinX, tWinY);
          };
          TBool  TGLAssonancesPage::Select (const TUInt & tIndex)
          {
              return TGLGlyphDrawer::Select (tIndex);
          };
          TBool  TGLAssonancesPage::SelectedIndex (TUInt * tIndex)
          {
              return TGLGlyphDrawer::SelectedIndex (tIndex);
          };
          TBool  TGLAssonancesPage::SelectedLinkDot (TUInt * tLinkDot)
          {
          TUInt index;
              if (!SelectedIndex (&index)) return false;

              (*tLinkDot) = _Page.TextIndex(_GLGlyphs[index]->RowIndex(), _GLGlyphs[index]->ColIndex());
          return true;
          };
