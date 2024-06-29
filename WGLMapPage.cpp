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
#include "WGLMapPage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"

      void  TGLMapPage::_GenerateColor(const TUInt tLinkDot, TGLColor3f tColor)
      {
          TSFloat value = _CoveredPage.Value(tLinkDot);

            if (value < 0)
            {
               //_tmpfloat0 = (value * cDefaultMapItemColor[0]) / _MaxValue;
               _tmpfloat1 = (value * cDefaultMapItemColor[1]) / _MinValue;
               _tmpfloat2 = (value * cDefaultMapItemColor[2]) / _MinValue;

               tColor[0] = cDefaultMapItemColor[0];
               tColor[1] = 1 - _tmpfloat1;
               tColor[2] = 1 - _tmpfloat2;
            }
            else
            {
               _tmpfloat0 = (value * cDefaultMapItemColor[0]) / _MaxValue;
               _tmpfloat1 = (value * cDefaultMapItemColor[1]) / _MaxValue;
               _tmpfloat2 = (value * cDefaultMapItemColor[2]) / _MaxValue;

          /*     if (_tmpfloat0 >= cColorChangeValue)
               {
                    tColor[0] = 1 - _tmpfloat0;
                    tColor[1] = 1 - _tmpfloat1;
                    tColor[2] = cDefaultMapItemColor[2];
               }
               else
               {
                    tColor[0] = 1 - _tmpfloat0;
                    tColor[1] = cDefaultMapItemColor[1];
                    tColor[2] = 1 - _tmpfloat2;
               }  */

                    tColor[0] = 1 - _tmpfloat0;
                    tColor[1] = 1 - _tmpfloat1;
                    tColor[2] = cDefaultMapItemColor[2];
            }
      };

      void TGLMapPage::_ComposeGlyphs()
      {
      if (!_TextDataProvider) throw EInvalidDataProvider();
      if (!_CoveredPage.IsReady()) throw ECoveredPageNotReady();

      View()->ForbidUpdate();

          _MinValue = _CoveredPage.MinValue() + cMinValueDivOnZeroProtection;
          _MaxValue = _CoveredPage.MaxValue() + cMaxValueDivOnZeroProtection;


      _GLGlyphs.Free();

       TGLMapGlyph * pGlyph;
       TGLColor3f    color;
       TUInt linkDot;

           for (TUInt i=0; i<_CoveredPage.Page()->Count(); i++)
           {
                for (TUInt j=0; j<_CoveredPage.Page()->RowLength(i); j++)
                {
                linkDot = _CoveredPage.Page()->TextIndex(i, j);
                _GenerateColor(linkDot, color);

                    pGlyph = new TGLMapGlyph(linkDot, i, j, color, this);

                   _GLGlyphs.AddGlyph(pGlyph);
                };
           };
      View()->AllowUpdate();
      };

      void TGLMapPage::_CalcCellDimentions()
      {
           TGLGlyphDrawer::_CalcCellDimentions();

          _CellWidth  = _CellWidth  / _CoveredPage.Page()->MaxRowLength();
          _CellHeight = _CellHeight / _CoveredPage.Page()->RowsCount();
      };

     TGLView           * TGLMapPage::View() { return TGLGlyphDrawer::View(); };
     TTextDataProvider * TGLMapPage::TextDataProvider() { return _TextDataProvider; };

     TGLMapPage & TGLMapPage::operator << (const TCoveredPage & tCoveredPage)
     {
         _CoveredPage = tCoveredPage;
         _CalcCellDimentions();
         _ComposeGlyphs();
     return *this;
     };

     TGLMapPage & TGLMapPage::operator << (TTextDataProvider * tTextDataProvider)
     {
         _TextDataProvider = tTextDataProvider;
     return *this;
     };

     TGLMapPage & TGLMapPage::operator << (TGLView * tView)
     {
         TGLGlyphDrawer::operator<<(tView);
     return *this;
     };

     void TGLMapPage::Init(TTextDataProvider * tTextDataProvider, TGLView * tView)
     {
         *this << tTextDataProvider;
         *this << tView;
     };

        TGLFloat TGLMapPage::CellWidth()  const { return TGLGlyphDrawer::CellWidth(); };
        TGLFloat TGLMapPage::CellHeight() const { return TGLGlyphDrawer::CellHeight(); };


   void  TGLMapPage::DrawText          (const TGLFloat & tX, const TGLFloat & tY, TGLColor3f tColor, const TTextString & tString)
   {
   };

   void  TGLMapPage::DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2, const TGLFloat & tZ, TGLColor3f tColor)
   {
       _View->Window()->DrawRectangle(tX1, tY1, tX2, tY2, tZ, tColor);
   };

   void  TGLMapPage::DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2,  const TGLFloat & tZ, TGLColor3f tColor)
   {
       _View->Window()->DrawEmptyRectangle(tX1, tY1, tX2, tY2, tZ, tColor);
   };


          TBool  TGLMapPage::Select (const TUInt & tWinX, const TUInt & tWinY)
          {
              return TGLGlyphDrawer::Select (tWinX, tWinY);
          };
          TBool  TGLMapPage::Select (const TUInt & tIndex)
          {
              return TGLGlyphDrawer::Select (tIndex);
          };
          TBool  TGLMapPage::SelectedIndex (TUInt * tIndex)
          {
              return TGLGlyphDrawer::SelectedIndex (tIndex);
          };
          TBool  TGLMapPage::SelectedLinkDot (TUInt * tLinkDot)
          {
          TUInt index;
              if (!SelectedIndex (&index)) return false;

              (*tLinkDot) = _CoveredPage.Page()->TextIndex(_GLGlyphs[index]->RowIndex(), _GLGlyphs[index]->ColIndex());
          return true;
          };

     TBool  TGLMapPage::Draw()
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

     void TGLMapPage::Clear()
     {
         TGLGlyphDrawer::Clear();
         _CoveredPage.Clear();
     };




