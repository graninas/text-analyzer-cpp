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
//==================������� ������������� GL, ��������, ������������ ������=====
//==============================================================================

//�������, ����������� ������ ����������� ��������� ������� ��������.
//��������� ���������� �� ��������, ������� � tCamMods.
//�� ������������ ��� ������ - ���������� �������. ��� ������ ������������ ��������-������� �������.

void GLInitProjCameraParams(TAphineModificationsf tCamMods);

//��������� ��������, ������ �����.
//������ 2: ������� ������� gluPerspective. ������ ��������� ���������� ����������� �������������
//�������������.

void GLInitProjectionParams(TSInt tw, TSInt th, TClippingRegion tCR, TProjectionTypes tProjType);

//�������, ������������� ��������, ������� ����� � ������.

void GLInitProjectionAndProjCamera (TSInt tw, TSInt th, TClippingRegion tCR, TProjectionTypes tProjType, TAphineModificationsf tCamMods);
void GLInitProjectionAndProjCamera (TProjMatrix tProjMatrix, TAphineModificationsf tCamMods);

void GLInitModelViewMatrix   (TModelMatrix tModelMatrix);
void GLInitProjectionMatrix (TProjMatrix tProjMatrix);

//------------------------------------------------------------------------------

TBool GLCreateDeviceContext(HWND thWnd, HDC *thDC);
TBool GLCreateGLRenderingContext(HDC thDC, HGLRC *thrc);

//�������, ��������� �������� ���������� OpenGL.
void  GLDeleteGLRenderingContext(HGLRC thGLRC);
void  GLDeleteDeviceContext(HDC thDC);

TBool GLMakeCurrentContext(const HDC & thDC, const HGLRC & thGLRC);

//==============================================================================
//=======��������������� ������� �� ������ � ����������� ��������, ������=======
//==============================================================================

//������� �������� glGetDoublev() ��� ��������� ���� ������: ������������, �������, viewport.
void GetFullProjectionInformation(TModelMatrix tModelMatrix, TProjMatrix tProjMatrix, TViewport tViewport);

TGLBool GetGLCoords(TGLDouble tWinX, TGLDouble tWinY, TGLDouble tWinZ, TDVector3 *tRes);
TGLBool GetWinCoords(TGLDouble tObjX, TGLDouble tObjY, TGLDouble tObjZ, TDVector3 *tRes);

#endif
