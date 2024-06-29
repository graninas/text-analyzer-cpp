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
#ifndef WGLDefaultWndConfigurerH
#define WGLDefaultWndConfigurerH
//---------------------------------------------------------------------------

#include "WGLWindowConfigurer.h"

    class TGLDefaultWndConfigurer : public TGLWindowConfigurer
    {
        private:
            TSInt _Width;
            TSInt _Height;
            HWND  _hWnd;

            TTextString _Alias;

        public:

          virtual TSInt           WndWidth();
          virtual TSInt           WndHeight();
          virtual TClippingRegion ClippingRegion();

          virtual TProjectionTypes ProjectionType();

          virtual TAphineModificationsf ProjectionSets();

          virtual void ClearColor(TGLColor4f tClearColor);

          virtual TBool GLDepthTest() ;
          virtual TBool GLCullFace()  ;
          virtual TUInt FrontFace()   ;
          virtual TUInt ShadeModel()  ;

          virtual HWND  hWnd()        ;
          virtual TBool Initialized() ;
          virtual TTextString Alias() ;

       TGLDefaultWndConfigurer(const TSInt & tWidth, const TSInt & tHeight, const TTextString & tAlias, HWND thWnd)
       : _Width(tWidth), _Height(tHeight), _hWnd(thWnd), _Alias(tAlias)   { };
    };



#endif
 