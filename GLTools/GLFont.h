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
#ifndef GLFontH
#define GLFontH
//---------------------------------------------------------------------------


#include "GLTypes.h"


    class TGLFont
    {

        private:
            TGLUInt _Base;
            HFONT   _Font;

            TGLBool _Initialized;

        public:

           TGLBool  IsInitialized() const;

           TGLUInt  Base() const;

           void     BuildFont(const TGLInt & tFontSize, const DWORD & tCharSetType, const char* tFontName,
             const DWORD & tBold, const DWORD & tItalic, const DWORD & tUnder, const DWORD & tStriked );

           void     BuildFont(const TGLInt & tFontSize, const char* tFontName);

           TGLBool  SelectFont(const HDC & thDC);

           void     DeleteFont();

         TGLFont() : _Initialized(false){};
        ~TGLFont(){ DeleteFont(); }
    };



#endif
