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
#ifndef WGLWindowH
#define WGLWindowH
//---------------------------------------------------------------------------

#include "GLInit.h"
#include "WGLWindowConfigurer.h"
#include "CErrorSpecificators.h"

#include "GLText.h"

class TMPGLWindow;

   class TGLWindow : public TErrorSpecificators
   {
   friend class TMPGLWindow;

      public:

          typedef TTextString SpecificatorType;
          SpecificatorType Specificator() const;

      private:

          HWND   _hWnd;

          HDC    _hDC;
          HGLRC  _hRC;


           TSInt                  _Width;
           TSInt                  _Height;
           TClippingRegion        _ClippingRegion;
           TProjectionTypes       _ProjectionType;
           TAphineModificationsf  _ProjectionSets;

           TGLColor4f    _ClearingColor;

           TBool _GLDepthTest;
           TBool _GLCullFace;
           TUInt _FrontFace;
           TUInt _ShadeModel;

          TTextString _Alias;
          TBool       _InitializedDC;
          TBool       _InitializedRC;
          TBool       _InitializedProjection;


          void _AssertError(const TUInt & tError);

          void _EnableGLCapabilities();

          void _InitProjAndCamera();

          void _GetGLWindowRect();

          TBool _InitRC();

          TBool _InitProjection();

      public:

         TBool IsInitializedDC() const ;
         TBool IsInitializedRC() const ;
         TBool IsCurrent()       const ;
         TBool IsInitializedProjection() const ;

         TBool Init();

         TBool MakeCurrent();

         void  Free();

         TBool ClearDC();

         TBool UpdateDC();

         void  Resize(const TUInt & tNewWidth, const TUInt & tNewHeight);

         TGLWindow & operator << (TGLWindowConfigurer * tConfigurer);

         HDC hDC() const;

         TSInt   Width()  const;
         TSInt   Height() const;


         TTextString Alias() const;


         void DrawText(const TGLFloat & tRastX, const TGLFloat & tRastY, const TGLFloat & tRastZ, TGLColor3f tColor, const char * tText, TGLText * tGLText);
         void DrawRectangle     (const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2, const TGLFloat & tZ, TGLColor3f tColor);
         void DrawEmptyRectangle(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2, const TGLFloat & tZ, TGLColor3f tColor);


         ~TGLWindow()
          {
              Free();
          }

      private:

          TGLWindow() : _InitializedRC(false), _InitializedDC(false), _InitializedProjection(false){}
   };




    class TMPGLWindow
    {
        public:

            typedef TTextString SpecificatorType;
            SpecificatorType Specificator() const { return _Window->Alias(); }

        private:

            TUInt _InstancesCounter;

            TGLWindow  * _Window;

            void _AddInstance()    { _InstancesCounter++; };
            void _DeleteInstance() { _InstancesCounter--; }

        public:

           TGLWindow * operator->() const { return _Window; }
           TGLWindow * Window()     const { return _Window; }


         TMPGLWindow & operator << (TGLWindowConfigurer * tConfigurer)
         {
             (*_Window) << tConfigurer;
         return *this;
         };

         void  Delete()
         {
             if (_Window) delete _Window;
         }

         TMPGLWindow & operator=(const TMPGLWindow & tMP)
         {
             if (&tMP != this)
             {
                 delete _Window;
                 _Window = new TGLWindow(*(tMP._Window));
             }
         return *this;
         }

         TMPGLWindow(const TMPGLWindow & tMPGLWindow) : _Window(new TGLWindow(*(tMPGLWindow._Window))), _InstancesCounter(0)
         {
            _AddInstance();
         };

         TMPGLWindow () : _Window(new TGLWindow()), _InstancesCounter(0)
         {
            _AddInstance();
         };

          ~TMPGLWindow ()
           {
              _DeleteInstance();
           };
    };



#endif
