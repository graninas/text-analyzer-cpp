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
#ifndef GLInitH
#define GLInitH
//---------------------------------------------------------------------------

#include "GLStructs.h"

//==============================================================================
//==================ФУНКЦИИ ИНИЦИАЛИЗАЦИИ GL, ПРОЕКЦИИ, ПРОЕКЦИОННОЙ КАМЕРЫ=====
//==============================================================================

//Функция, имитирующая камеру посредством изменения матрицы проекции.
//Параметры изменяются на величины, лежащие в tCamMods.
//Не использовать как камеру - невыгодный вариант. Для камеры использовать модельно-видовую матрицу.

void GLInitProjCameraParams(TAphineModificationsf tCamMods);

//Настройка проекции, границ сцены.
//Версия 2: добавил функцию gluPerspective. Теперь установка параметров перспективы действительно
//универсальная.

void GLInitProjectionParams(TSInt tw, TSInt th, TClippingRegion tCR, TProjectionTypes tProjType);

//Функция, настраивающая проекцию, границы сцены и камеру.

void GLInitProjectionAndProjCamera (TSInt tw, TSInt th, TClippingRegion tCR, TProjectionTypes tProjType, TAphineModificationsf tCamMods);
void GLInitProjectionAndProjCamera (TProjMatrix tProjMatrix, TAphineModificationsf tCamMods);

void GLInitModelViewMatrix   (TModelMatrix tModelMatrix);
void GLInitProjectionMatrix (TProjMatrix tProjMatrix);

//------------------------------------------------------------------------------

TBool GLCreateDeviceContext(HWND thWnd, HDC *thDC);
TBool GLCreateGLRenderingContext(HDC thDC, HGLRC *thrc);

//Функция, очищающая контекст рендеринга OpenGL.
void  GLDeleteGLRenderingContext(HGLRC thGLRC);
void  GLDeleteDeviceContext(HDC thDC);

TBool GLMakeCurrentContext(const HDC & thDC, const HGLRC & thGLRC);

//==============================================================================
//=======ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ПО РАБОТЕ С НАСТРОЙКАМИ ПРОЕКЦИИ, КАМЕРЫ=======
//==============================================================================

//Функция вызывает glGetDoublev() для получения трех матриц: проекционной, видовой, viewport.
void GetFullProjectionInformation(TModelMatrix tModelMatrix, TProjMatrix tProjMatrix, TViewport tViewport);

TGLBool GetGLCoords(TGLDouble tWinX, TGLDouble tWinY, TGLDouble tWinZ, TDVector3 *tRes);
TGLBool GetWinCoords(TGLDouble tObjX, TGLDouble tObjY, TGLDouble tObjZ, TDVector3 *tRes);

#endif
