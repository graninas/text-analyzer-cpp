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
#include "WGLDefaultWndConfigurer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include "GLConstants.h"


           TSInt           TGLDefaultWndConfigurer::WndWidth()   { return _Width; };
           TSInt           TGLDefaultWndConfigurer::WndHeight()  { return _Height; };
           TClippingRegion TGLDefaultWndConfigurer::ClippingRegion()
          {
          TClippingRegion cr;

    /*          cr.Left  =  -_Width/2;
              cr.Right =   _Width/2;
                 cr.Bottom = -_Height/2;
                 cr.Top =     _Height/2;     */

              cr.Left  =  0;
              cr.Right =   _Width;
                 cr.Bottom = 0;
                 cr.Top =     _Height; 

            /*  cr.Left  =  0;
              cr.Right =  2*_Width;
                 cr.Bottom = 0;
                 cr.Top =    2*_Height;  */

           /*   cr.Left  =  -2*_Width;
              cr.Right =  2*_Width;
                 cr.Bottom = -2*_Height;
                 cr.Top =    2*_Height; */

              cr.Near =   cGLClippingRegionNear;
              cr.Far  =   cGLClippingRegionFar;
          return cr;
          };

           TProjectionTypes TGLDefaultWndConfigurer::ProjectionType()  { return ptOrtho; };

           TAphineModificationsf TGLDefaultWndConfigurer::ProjectionSets()
          {
          TAphineModificationsf  am;
             am.Translate.Create(0.0f, 0.0f, 0.0f);
             am.Rotate.Create(0.0f, 0.0f, 0.0f);
             am.Scale.Create(cGLXProportionalScale, cGLXProportionalScale, cGLZProportionalScale);
          return am;
          };

           void TGLDefaultWndConfigurer::ClearColor(TGLColor4f tClearColor)
          {
             tClearColor[0] = cGLClearColor[0];
             tClearColor[1] = cGLClearColor[1];
             tClearColor[2] = cGLClearColor[2];
             tClearColor[3] = cGLClearColor[3];
          };

           TBool TGLDefaultWndConfigurer::GLDepthTest() { return true; };
           TBool TGLDefaultWndConfigurer::GLCullFace()  { return true; };
           TUInt TGLDefaultWndConfigurer::FrontFace()   { return cDefaultFrontFace; };
           TUInt TGLDefaultWndConfigurer::ShadeModel()  { return cDefaultShadeModel; };

           HWND  TGLDefaultWndConfigurer::hWnd()        { return _hWnd; }
           TBool TGLDefaultWndConfigurer::Initialized() { return false; };
           TTextString TGLDefaultWndConfigurer::Alias() { return _Alias; };

