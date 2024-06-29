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
#include "WGLTextPage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"

      void TGLTextPage::_ComposeGlyphs()
      {
      if (!_TextDataProvider) throw EInvalidDataProvider();
      View()->ForbidUpdate();

      _GLGlyphs.Free();

      TTextString s;

      TGLTextGlyph * pGlyph;

           for (TUInt i=0; i<_Page->Count(); i++)
           {
                for (TUInt j=0; j<_Page->RowLength(i); j++)
                {
                    s = _TextDataProvider->SubString(_Page->TextIndex(i,j), 1);

                    pGlyph = new TGLTextGlyph(s, i, j, cDefaultTextColor, this);

                   _GLGlyphs.AddGlyph(pGlyph);
                };
           };

      View()->AllowUpdate();
      };

      void TGLTextPage::_BuildFont()
      {
      if (!_GLGlyphs.Count()) return;

         TGLRect rect;
         TGLUInt fntSize;

            rect = _GLGlyphs[0]->CellRect();

         fntSize = cGetFontSize(fabs(rect.Point1().X()), (rect.Point1().Y()));
        _GLFont.BuildFont(fntSize, cDefaultFont.c_str());
        _GLText.Font(&_GLFont);
        _FontSize = fntSize;

        _WRasterPos = cGetWRasterPos(_FontSize);
        _HRasterPos = cGetHRasterPos(_FontSize);

        //Текст всегад печатается выше и правее заданной точки, поэтому необходимо скорректировать его вниз:
//        _HRasterPos += TGLFloat(_CellHeight);
        _HRasterPos += TGLFloat(fntSize + cSideField);
//         _HRasterPos += TGLFloat(cSideField);
      };

      void TGLTextPage::_CalcCellDimentions()
      {
           TGLGlyphDrawer::_CalcCellDimentions();

          _CellWidth  = _CellWidth  / _Page->MaxRowLength();
          _CellHeight = _CellHeight / _Page->RowsCount();
      }

      

     TGLView * TGLTextPage::View() { return TGLGlyphDrawer::View(); };


     TTextDataProvider * TGLTextPage::TextDataProvider() { return _TextDataProvider; };


     TGLTextPage & TGLTextPage::operator << (ns_Page::TPage * tPage)
     {
         _Page = tPage;

         _CalcCellDimentions();
         _ComposeGlyphs();
         _BuildFont();
     return *this;
     };


     TGLTextPage & TGLTextPage::operator << (TTextDataProvider * tTextDataProvider)
     {
         _TextDataProvider = tTextDataProvider;
     return *this;
     };

     TGLTextPage & TGLTextPage::operator << (TGLView * tView)
     {
         //_View = tView;
         TGLGlyphDrawer::operator<<(tView);
     return *this;
     };

     void TGLTextPage::Init(TTextDataProvider * tTextDataProvider, TGLView * tView)
     {
         *this << tTextDataProvider;
         *this << tView;
     };

        TGLFloat TGLTextPage::CellWidth()  const { return TGLGlyphDrawer::CellWidth(); };
        TGLFloat TGLTextPage::CellHeight() const { return TGLGlyphDrawer::CellHeight(); };


   void    TGLTextPage::DrawText(const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString)
   {
       char * chr = tString.c_str();

      _View->Window()->DrawText(_WRasterPos + tX, _HRasterPos + tY, cDefaultZValue, tColor, chr, &_GLText);
   };

     TBool  TGLTextPage::Draw()
     {
     if (!TGLGlyphDrawer::Draw()) return false;
     View()->ForbidUpdate();

       _GLFont.SelectFont(_View-> hDC());

       glPushMatrix();
       glTranslatef(cSideField, cSideField, 0.0f);

         for (TUInt i=0; i<_GLGlyphs.Count(); i++)
           _GLGlyphs[i]->Draw();

       glPopMatrix();

     View()->AllowUpdate();
     return true;
     };


          TBool  TGLTextPage::Select (const TUInt & tWinX, const TUInt & tWinY)
          {
              return TGLGlyphDrawer::Select (tWinX, tWinY);
          };
          TBool  TGLTextPage::Select (const TUInt & tIndex)
          {
              return TGLGlyphDrawer::Select (tIndex);
          };
          TBool  TGLTextPage::SelectedIndex (TUInt * tIndex)
          {
              return TGLGlyphDrawer::SelectedIndex (tIndex);
          };
          TBool  TGLTextPage::SelectedLinkDot (TUInt * tLinkDot)
          {
          TUInt index;
              if (!SelectedIndex (&index)) return false;

              (*tLinkDot) = _Page->TextIndex(_GLGlyphs[index]->RowIndex(), _GLGlyphs[index]->ColIndex());
          return true;
          };

     void TGLTextPage::Clear()
     {
         TGLGlyphDrawer::Clear();
     };


    TGLTextPage::TGLTextPage() : TGLGlyphDrawer(), _GLText(&_GLFont),
        _WRasterPos(0.0f), _HRasterPos(0.0f)
    {
        _GLFont.BuildFont(cDefaultFontSize, cDefaultFont.c_str());
    }

    TGLTextPage::TGLTextPage(TGLView * tView, TTextDataProvider * tTextDataProvider)
      : TGLGlyphDrawer(tView), _TextDataProvider(tTextDataProvider), _GLText(&_GLFont),
        _WRasterPos(0.0f), _HRasterPos(0.0f)
      {
         _GLFont.BuildFont(cDefaultFontSize, cDefaultFont.c_str());
      };



