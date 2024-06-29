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
#include "GLInit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//------------------------------------------------------------------------------

#include "GLConstants.h"

//==============================================================================
//==================ФУНКЦИИ ИНИЦИАЛИЗАЦИИ GL, ПРОЕКЦИИ, ПРОЕКЦИОННОЙ КАМЕРЫ=====
//==============================================================================

void GLInitProjCameraParams(TAphineModificationsf tCamMods)
{
    glMatrixMode(GL_PROJECTION);

        glTranslatef(tCamMods.Translate.X(), tCamMods.Translate.Y(), tCamMods.Translate.Z());
          glRotatef(tCamMods.Rotate.X(), 1.0f, 0.0f, 0.0f);
          glRotatef(tCamMods.Rotate.Y(), 0.0f, 1.0f, 0.0f);
          glRotatef(tCamMods.Rotate.Z(), 0.0f, 0.0f, 1.0f);
            glScalef(tCamMods.Scale.X(), tCamMods.Scale.Y(), tCamMods.Scale.Z());

    glMatrixMode(GL_MODELVIEW);
};

void GLInitProjectionParams(TSInt tw, TSInt th, TClippingRegion tCR, TProjectionTypes tProjType)
{
  glViewport(0, 0, tw, th);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

    if (tProjType == ptOrtho)
    {
        glOrtho ( tCR.Left, tCR.Right, tCR.Bottom, tCR.Top, tCR.Near, tCR.Far );
    }
    else  //tProjType == ptPerspective
    {
       if (tCR.ClipType == tcAngle)

           if (tw <= th)
               gluPerspective ( tCR.FOVy, (double)th/(double)tw, tCR.Near, tCR.Far );
           else
               gluPerspective ( tCR.FOVy, (double)tw/(double)th, tCR.Near, tCR.Far );

       else     //tCR.ClipType == tcCube; tCR.ClipType == tcRegion

           glFrustum ( tCR.Left, tCR.Right, tCR.Bottom, tCR.Top, tCR.Near, tCR.Far );
    }

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
};

void GLInitProjectionAndProjCamera(TSInt tw, TSInt th, TClippingRegion tCR, TProjectionTypes tProjType, TAphineModificationsf tCamMods)
{
  GLInitProjectionParams (tw, th, tCR, tProjType);
  GLInitProjCameraParams     (tCamMods);
};


void GLInitProjectionAndProjCamera(TProjMatrix tProjMatrix, TAphineModificationsf tCamMods)
{
  GLInitProjectionMatrix (tProjMatrix);
  GLInitProjCameraParams     (tCamMods);
};

void GLInitProjectionMatrix(TProjMatrix tProjMatrix)
{
  glMatrixMode(GL_PROJECTION);
       glLoadMatrixd(tProjMatrix);
  glMatrixMode(GL_MODELVIEW);
};

void GLInitModelViewMatrix(TModelMatrix tModelMatrix)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(tModelMatrix);
};

//------------------------------------------------------------------------------

HDC GLCreateContext(HWND thWnd)
{
	GLuint		PixelFormat;
        HDC             hDC;
        HGLRC           hRC;

        TBool           IsSetedPixelFormat;
        TBool           IsCurrentContext;

	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};


        hDC = GetDC(thWnd);      //Берем контекст устройства, где будем рисовать.

        PixelFormat = ChoosePixelFormat(hDC,&pfd);     //Выбираем пиксель-формат.
        	if (!PixelFormat) return 0;

        IsSetedPixelFormat = SetPixelFormat(hDC,PixelFormat,&pfd); //Устанавливаем пиксель-формат.
	        if(!IsSetedPixelFormat) return 0;

        hRC = wglCreateContext(hDC);      //Создаем контекст рендеринга OpenGL
        	if (!hRC) return 0;

        IsCurrentContext = wglMakeCurrent(hDC,hRC); //Делаем контекст текущим.
        	if(!IsCurrentContext) return 0;

return hDC;
};

TBool GLCreateDeviceContext(HWND thWnd, HDC *thDC)
{
	GLuint		PixelFormat;
        HDC             hDC;
        HGLRC           hRC;

        TBool           IsSetedPixelFormat;

	static	PIXELFORMATDESCRIPTOR pfd=
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

        hDC = GetDC(thWnd);      //Берем контекст устройства, где будем рисовать.

        PixelFormat = ChoosePixelFormat(hDC,&pfd);     //Выбираем пиксель-формат.
        	if (!PixelFormat) return false;

        IsSetedPixelFormat = SetPixelFormat(hDC,PixelFormat,&pfd); //Устанавливаем пиксель-формат.
	        if(!IsSetedPixelFormat) return false;

      (*thDC) = hDC;
return true;
};


TBool GLCreateGLRenderingContext(HDC thDC, HGLRC *thrc)
{
HGLRC  hRC;
    hRC = wglCreateContext(thDC);      //Создаем контекст рендеринга OpenGL
   	if (!hRC) return false;
(*thrc) = hRC;
return true;
}

void GLDeleteGLRenderingContext(HGLRC thGLRC)
{
    wglMakeCurrent (NULL, NULL) ;
    wglDeleteContext (thGLRC);
};

void  GLDeleteDeviceContext(HDC thDC)
{
    DeleteDC(thDC);
};

TBool GLMakeCurrentContext(const HDC & thDC, const HGLRC & thGLRC)
{
    return wglMakeCurrent(thDC, thGLRC);
};

//==============================================================================
//=======ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ПО РАБОТЕ С НАСТРОЙКАМИ ПРОЕКЦИИ, КАМЕРЫ=======
//==============================================================================

void GetFullProjectionInformation(TModelMatrix tModelMatrix, TProjMatrix tProjMatrix, TViewport tViewport)
{
    glGetIntegerv(GL_VIEWPORT,          tViewport);
    glGetDoublev (GL_MODELVIEW_MATRIX,  tModelMatrix);
    glGetDoublev (GL_PROJECTION_MATRIX, tProjMatrix);
};

TGLBool GetGLCoords(TGLDouble tWinX, TGLDouble tWinY, TGLDouble tWinZ, TDVector3 *tRes)
{
TModelMatrix modelMatrix;
TProjMatrix  projMatrix;
TViewport    viewport;
                                                 
   GetFullProjectionInformation(modelMatrix, projMatrix, viewport);

   TGLDouble objx, objy, objz;
  if (gluUnProject(tWinX, tWinY, tWinX, modelMatrix, projMatrix, viewport, &objx, &objy, &objz))
  {
      (*tRes) = TDVector3(GLX(objx), GLY(objy), GLZ(objz));
      return true;
  }
return false;
}

TGLBool GetWinCoords(TGLDouble tObjX, TGLDouble tObjY, TGLDouble tObjZ, TDVector3 *tRes)
{
TModelMatrix modelMatrix;
TProjMatrix  projMatrix;
TViewport    viewport;

   GetFullProjectionInformation(modelMatrix, projMatrix, viewport);

   TGLDouble winx, winy, winz;
  if (gluProject(tObjX, tObjY, tObjZ, modelMatrix, projMatrix, viewport, &winx, &winy, &winz))
  {
      (*tRes) = TDVector3(winx, winy, winz);
      return true;
  }

return false;
};

