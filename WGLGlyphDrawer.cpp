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
#include "WGLGlyphDrawer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"

   void  TGLGlyphDrawer::_CalcCellDimentions()
   {
       TAbstractGLGlyphDrawer::_CalcCellDimentions();
   };

      TGLView * TGLGlyphDrawer::View() { return TAbstractGLGlyphDrawer::View(); };



    TBool   TGLGlyphDrawer::Select (const TUInt & tWinX, const TUInt & tWinY)
    {
     TDVector3 v;

         View()->GetCoords(tWinX, tWinY, &v);

         v.X -= cSideField;
         v.Y -= cSideField;

         TBool found = false;

         _GLGlyphs.UnSelectAll();

         for (TUInt i=0; i<_GLGlyphs.Count(); i++)
           if (_GLGlyphs[i]->Intersects(v.X, v.Y))
           {
              _GLGlyphs[i]->Select();
               found = true;
           };

    return found;
    };


    TBool   TGLGlyphDrawer::Select (const TUInt & tIndex)
    {
    _GLGlyphs.UnSelectAll();
         return _GLGlyphs.Select(tIndex);
    };

     TBool  TGLGlyphDrawer::SelectedIndex (TUInt * tIndex)
     {
         for (TUInt i=0; i<_GLGlyphs.Count(); i++)
             if (_GLGlyphs[i]->Selected())
             {
                *tIndex = i;
             return true;
             }

     return false;
     };

     TBool  TGLGlyphDrawer::SelectedLinkDot (TUInt * tLinkDot)
     {
      return false;
     };

     TBool TGLGlyphDrawer::Draw()
     {
        return TAbstractGLGlyphDrawer::Draw();
     }


        TGLFloat TGLGlyphDrawer::CellWidth()  const { return TAbstractGLGlyphDrawer::CellWidth(); };
        TGLFloat TGLGlyphDrawer::CellHeight() const { return TAbstractGLGlyphDrawer::CellHeight(); };


     TGLGlyphDrawer & TGLGlyphDrawer::operator << (TGLView * tView)
     {
         TAbstractGLGlyphDrawer::operator << (tView);
     return *this;
     };

     void TGLGlyphDrawer::Clear()
     {
         _GLGlyphs.Free();
     };

 