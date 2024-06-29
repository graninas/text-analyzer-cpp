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
#include "WGLWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

          TGLWindow::SpecificatorType TGLWindow::Specificator() const { return _Alias; }

          void TGLWindow::_AssertError(const TUInt & tError)
          {
            if (tError)
            {
              char * lpMsgBuf;

                  FormatMessage(
                      FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                      NULL,
                      tError,
                      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
                      (LPTSTR) &lpMsgBuf,
                      0,
                      NULL
                  );
                // Display the string.
                MessageBox( NULL, lpMsgBuf, "Œ¯Ë·Í‡", MB_OK|MB_ICONINFORMATION );
                // Free the buffer.
                LocalFree( lpMsgBuf );
             };
          }

          void TGLWindow::_EnableGLCapabilities()
          {
              if (_GLDepthTest) glEnable(GL_DEPTH_TEST);
              if (_GLCullFace)  glEnable(GL_CULL_FACE);

              glFrontFace(_FrontFace);
              glShadeModel(_ShadeModel);
          };

          void TGLWindow::_InitProjAndCamera()
          {
             GLInitProjectionAndProjCamera (_Width, _Height, _ClippingRegion, _ProjectionType, _ProjectionSets);
          };


          TBool TGLWindow::_InitRC()
          {
              if (!_InitializedDC)
                 if (!Init()) return false;

              if (_InitializedRC) return true;

          _InitializedRC = GLCreateGLRenderingContext(_hDC, &_hRC);
          _InitializedProjection = false;
          return _InitializedRC;
          };

          TBool TGLWindow::_InitProjection()
          {
              _InitProjAndCamera();
              _EnableGLCapabilities();
          _InitializedProjection = true;
          return true;
          };



         TBool TGLWindow::IsInitializedDC() const { return _InitializedDC; }
         TBool TGLWindow::IsInitializedRC() const { return _InitializedRC; }
         TBool TGLWindow::IsCurrent()       const { return (wglGetCurrentDC() == _hDC) ? true : false; }
         TBool TGLWindow::IsInitializedProjection() const { return _InitializedProjection; }

         TBool TGLWindow::Init()
         {
             if (_InitializedDC) return true;
                 _InitializedDC = GLCreateDeviceContext(_hWnd, &_hDC);
                 _AssertError(GetLastError());
         return  _InitializedDC;
         };

         TBool TGLWindow::MakeCurrent()
         {
            if (!_InitRC()) return false;
               if (IsCurrent())
               {
                  if (!_InitializedProjection) _InitProjection();
               return true;
               }
                  if (!GLMakeCurrentContext(_hDC, _hRC)) return false;

         if (!_InitializedProjection) _InitProjection();
         return true;
         };

         void TGLWindow::Free()
         {
             if (_InitializedDC) GLDeleteDeviceContext(_hDC);
             if (_InitializedRC) GLDeleteGLRenderingContext(_hRC);
         _InitializedDC = false;
         _InitializedRC = false;
         _InitializedProjection = false;
         };

         TBool TGLWindow::ClearDC()
         {
         if (!_InitializedProjection) _InitProjection();

            glClearColor(_ClearingColor[0], _ClearingColor[1], _ClearingColor[2], _ClearingColor[3]);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

         return true;
         };

         TBool TGLWindow::UpdateDC()
         {
             return SwapBuffers(_hDC);
         };

         void  TGLWindow::Resize(const TUInt & tNewWidth, const TUInt & tNewHeight)
         {
             _Width  = tNewWidth;
             _Height = tNewHeight;

         _InitProjection();
         };


         TGLWindow & TGLWindow::operator << (TGLWindowConfigurer * tConfigurer)
         {
             _Width  = tConfigurer->WndWidth();
             _Height = tConfigurer->WndHeight();
             _ClippingRegion = tConfigurer->ClippingRegion();
             _ProjectionType = tConfigurer->ProjectionType();
             _ProjectionSets = tConfigurer->ProjectionSets();

             tConfigurer->ClearColor(_ClearingColor);

         _GLDepthTest = tConfigurer->GLDepthTest();
         _GLCullFace  = tConfigurer->GLCullFace();
         _FrontFace   = tConfigurer->FrontFace();
         _ShadeModel  = tConfigurer->ShadeModel();
         _hWnd        = tConfigurer->hWnd();
         _InitializedRC = false;
         _InitializedDC = false;
         _InitializedProjection = false;
         _Alias       = tConfigurer->Alias();

         return *this;
         };

         HDC TGLWindow::hDC() const { return _hDC; }

         TSInt   TGLWindow::Width()  const { return _Width; }
         TSInt   TGLWindow::Height() const { return _Height; }

         TTextString TGLWindow::Alias() const { return _Alias; }


  void TGLWindow::DrawText(const TGLFloat & tRastX, const TGLFloat & tRastY, const TGLFloat & tRastZ, TGLColor3f tColor, const char * tText, TGLText * tGLText)
  {
  glPushMatrix();

     glColor3f(tColor[0], tColor[1], tColor[2]);
     glRasterPos3f(tRastX, tRastY, tRastZ);
         tGLText->DrawTextA(tText);

  glPopMatrix();
  };

  void TGLWindow::DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2, const TGLFloat & tZ, TGLColor3f tColor)
  {
      glColor3f(tColor[0], tColor[1], tColor[2]);

      glBegin(GL_QUADS);

          glVertex3f(tX1, tY1, tZ);
          glVertex3f(tX2, tY1, tZ);
          glVertex3f(tX2, tY2, tZ);
          glVertex3f(tX1, tY2, tZ);

      glEnd();
  };

  void TGLWindow::DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2, const TGLFloat & tZ, TGLColor3f tColor)
  {
      glColor3f(tColor[0], tColor[1], tColor[2]);

      glBegin(GL_LINE_LOOP);

          glVertex3f(tX1, tY1, tZ);
          glVertex3f(tX2, tY1, tZ);
          glVertex3f(tX2, tY2, tZ);
          glVertex3f(tX1, tY2, tZ);

      glEnd();
  };

