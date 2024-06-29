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
#ifndef WGLViewH
#define WGLViewH
//---------------------------------------------------------------------------

#include "WGLWindow.h"
#include "WGLViewConfigurer.h"
#include "CErrorSpecificators.h"

   class TGLView : public TErrorSpecificators
   {
      public:

          typedef TTextString SpecificatorType;
          SpecificatorType Specificator() const;

      private:

           TGLModelviewCamera  _Camera;

           TGLWindow * _GLWindow;

           TGLRect     _GLViewRect;
           TBool       _UseCornerCenteredCoordinates;

           TBool    _CanUpdate;

           TTextString _Alias;


           void  _GetGLViewRect();

      public:

            TBool CanUpdate() const;
            void  ForbidUpdate();
            void  AllowUpdate();

            TGLModelviewCamera & Camera();
            void                 Camera(const TGLModelviewCamera & tCamera);
            TGLView & operator << (const TGLModelviewCamera & tCamera);

            TGLWindow * Window();
            void        Window(TGLWindow * tGLWindow);
            TGLView & operator << (TGLWindow * tGLWindow);



            void  Render();
            void  Update();
            TBool MakeCurrent();
            void  Release();

            void  Resize(const TUInt & tNewWidth, const TUInt & tNewHeight);

            TBool GetCoords(const TUInt & tX, const TUInt & tY, TDVector3 * tTarget);

            TSInt   Width()    const ;
            TSInt   Height()   const ;
            TGLRect Rect()     const ;

            HDC     hDC()      const ;

            TTextString Alias() const;


         TGLView & operator << (TGLViewConfigurer * tConfigurer);

         TGLView(const TTextString & tAlias) : _Alias(tAlias), _CanUpdate(true){};
         TGLView() : _Alias(""){};
        ~TGLView() {  };
   };


#endif
