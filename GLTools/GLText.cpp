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
#include "GLText.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"

            void TGLText::_BuildDefaultFont()
            {
                 _DefaultFont.BuildFont(cDefaultFontSize, cDefaultCharSet,  cDefaultFont.c_str(),
                       cDefaultFontBold, cDefaultItalic, cDefaultUnderline, cDefaultStriked);
            };


           TGLFont * TGLText::Font() { return _Font; }

           void TGLText::DrawText(const char *fmt, ...)
           {
             //     if (!fmt) return;

               va_start(ap, fmt);
                  vsprintf(text, fmt, ap);
               va_end(ap);

               glPushAttrib(GL_LIST_BIT);
                  glListBase(_Font->Base());
                  glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
               glPopAttrib();
           };


           void TGLText::Font(TGLFont * tFont)
           {
              _Font = tFont;
           };

