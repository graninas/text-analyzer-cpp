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
#include "WGLView.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"

          TGLView::SpecificatorType TGLView::Specificator() const { return _Alias; }


            void TGLView::_GetGLViewRect()
            {
               TGLRect rect;
               TDVector3 v1,v2;

                  GetGLCoords(0, 0, 0, &v1);
                  GetGLCoords(_GLWindow->Width(), _GLWindow->Height(), 0, &v2);

                  rect.Create(v1.X, v1.Y, v2.X, v2.Y);
                     
            _GLViewRect = rect;
            };

            TBool TGLView::CanUpdate() const
            {
               return _CanUpdate;
            };

            void  TGLView::ForbidUpdate()
            {
               _CanUpdate = false;
            };

            void  TGLView::AllowUpdate()
            {
               _CanUpdate = true;
            };

            TGLModelviewCamera & TGLView::Camera()
            {
                return _Camera;
            }

            void  TGLView::Camera(const TGLModelviewCamera & tCamera)
            {
                *this << tCamera;
            }

            TGLView & TGLView::operator << (const TGLModelviewCamera & tCamera)
            {
                _Camera = tCamera;
            return *this;
            }

            TGLWindow * TGLView::Window() { return _GLWindow; };
            void        TGLView::Window(TGLWindow * tGLWindow)   { *this << tGLWindow; }

            TGLView &   TGLView::operator << (TGLWindow * tGLWindow)
            {
              _GLWindow = tGLWindow;
              
                 MakeCurrent();

              _GetGLViewRect();

               if (_UseCornerCenteredCoordinates)
               {
                   TDVector3 gl;

                       if (!GetGLCoords(0, _GLWindow->Height(), 0, &gl)) throw EInvalidGLCoords();

                   gl.Z = 0.0f;

                   TGLEyeDirection eye = _Camera.Eye();

                       eye.Position += gl;
                       eye.View     += gl;

               _Camera.LookAt(eye);
               };

            return *this;
            }

            void TGLView::Render()
            {
                _GLWindow->ClearDC();
                _Camera.Render();
            };

            void TGLView::Update()
            {
            if (!CanUpdate()) return;
                _GLWindow->UpdateDC();
            };

            TBool TGLView::MakeCurrent()
            {
                if (!_GLWindow->MakeCurrent()) return false;
            Render();
            return true;
            };

            void TGLView::Release()
            {
                _GLWindow->Free();
            };

            void TGLView::Resize(const TUInt & tNewWidth, const TUInt & tNewHeight)
            {
                _GLWindow->Resize(tNewWidth, tNewHeight);
                *this << _GLWindow;
            };


            TSInt   TGLView::Width()     const { return _GLWindow->Width();  };
            TSInt   TGLView::Height()    const { return _GLWindow->Height(); };
            TGLRect TGLView::Rect()      const { return _GLViewRect;         };
            TTextString TGLView::Alias() const { return _Alias;              };

            TBool TGLView::GetCoords(const TUInt & tX, const TUInt & tY, TDVector3 * tTarget)
            {
               //if (!GetGLCoords(tX, tY, cDefaultZValue, tTarget)) return false;
               tTarget->X = tX;
               tTarget->Y = tY;
            return true;
            }

            HDC     TGLView::hDC()      const { return _GLWindow->hDC(); }


         TGLView & TGLView::operator << (TGLViewConfigurer * tConfigurer)
         {
             _Camera = tConfigurer->Camera();
             _UseCornerCenteredCoordinates = tConfigurer->UseCornerCenteredCoordinates();
         return *this;
         };





