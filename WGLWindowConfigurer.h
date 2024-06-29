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
#ifndef WGLWindowConfigurerH
#define WGLWindowConfigurerH
//---------------------------------------------------------------------------

#include "GLStructs.h"

    class TGLWindowConfigurer
    {
        public:

          virtual TSInt                 WndWidth()  = 0;
          virtual TSInt                 WndHeight() = 0;
          virtual TClippingRegion       ClippingRegion() = 0;
          virtual TProjectionTypes      ProjectionType() = 0;
          virtual TAphineModificationsf ProjectionSets() = 0;

          virtual TBool GLDepthTest() = 0;
          virtual TBool GLCullFace() = 0;
          virtual TUInt FrontFace() = 0;
          virtual TUInt ShadeModel() = 0;

          virtual void ClearColor(TGLColor4f tClearColor) = 0;

          virtual HWND  hWnd() = 0;
          virtual TBool Initialized() = 0;
          virtual TTextString Alias() = 0;

    TGLWindowConfigurer(){};
    };



#endif
