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
#ifndef GLModelviewCameraH
#define GLModelviewCameraH

#include "GLStructs.h"

//=============================================================================
//========================��������-������� ������==============================
//=============================================================================

class TGLModelviewCamera
{
    TAphineModificationsf _CameraParams;

    TBool _IsUsinggluLookAt;

    TGLEyeDirection _Eye;       //������� "�����" ������������ ������.
    
public:
     TGLModelviewCamera(TBool tUseLookAt);
     TGLModelviewCamera(TGLEyeDirection tEyeFrame);
     TGLModelviewCamera();     
    ~TGLModelviewCamera();

     //�������, ������� ���������� �������� �� ���������� ���� �����. ��������� ��������� ������.
     void   Render();

     void   Modify (TAphineModificationsf tCamMods);  //��������� ������� ��������� ������ � tCamMods.
     void   Set    (TAphineModificationsf tCamMods);  //������������� ���������� ���������.
     void   SetDefaults ();                           //������������� �������� �� ��������� (Rotate � Translate - 0.0f, Scale = 1).

     //������� �������� ������� ����������, � ������� �������� �������.
     //���� ������ ����������� (0,0,0), �� ���������� ������ ��������.
     //�� ������� ���� ������������ ����������� ����������.
     //���� ���� ��� �������������� ������� ��� �������� ������.
     //���� � ��������.
     void   Translate (TGLFloat tDistance, TVectorOrds tByAxis);
     void   Rotate    (TGLFloat tAngle,    TVectorOrds tByAxis);

     void   EnableLookAt();
     void   DisableLookAt();
     void   LookAt (TGLEyeDirection tEyeFrame);

     //������� �������� � �������� ����� ������.
     //��������� ���� tAngle �������� ������� �������.
     void   Move           (TGLDouble tSpeed);
     void   Strafe         (TGLDouble tSpeed, TVectorOrds tAxis);
     void   RotateView     (TGLDouble tAngle, TCameraRotDirections tRotDir);

     void   FlatRotateView (TGLDouble tAngle, TGLDouble tX, TGLDouble tY, TGLDouble tZ);


     TGLEyeDirection Eye() const { return _Eye; }

     TDVector3 UpVector();
     TDVector3 ViewPoint();
     TDVector3 Position();
     TDVector3 FrontVector();
     TDVector3 LeftVector();
     TDVector3 RightVector();
};










#endif
