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
#ifndef WGLGlyphsH
#define WGLGlyphsH
//---------------------------------------------------------------------------

#include "WGLGlyph.h"
#include "CContainer.h"

    class TGLGlyphs
    {
        public:

           typedef TGLGlyph * PGlyph;
           typedef TContainer<PGlyph> TGLPGlyphs;

        private:

           TGLPGlyphs _PGlyphs;

        public:

           void AddGlyph(PGlyph tGlyph)
           {
              _PGlyphs.AddItem(tGlyph);
           };

           PGlyph Glyph(const TUInt & tIndex)
           {
               return _PGlyphs[tIndex];
           };

           TUInt Count()
           {
               return _PGlyphs.Count();
           };

           void  Free()
           {
               for (TUInt i=0; i<_PGlyphs.Count(); i++)
                   delete _PGlyphs[i];
           _PGlyphs.Clear();
           };

           PGlyph operator[](const TUInt & tIndex)
           {
               return _PGlyphs[tIndex];
           };

           void UnSelectAll()
           {
               for (TUInt i=0; i<_PGlyphs.Count(); i++)
                 _PGlyphs[i]->UnSelect();
           }

           TBool Select(const TUInt & tIndex)
           {
               if (!_PGlyphs.IsValidIndex(tIndex)) return false;
           _PGlyphs[tIndex]->Select();
           return true;
           };


           TGLGlyphs(){};
          ~TGLGlyphs(){ Free(); };
    };


#endif
 