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
#include "GLModelviewCamera.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "math.h"

TGLModelviewCamera::TGLModelviewCamera(TBool tUseLookAt)
{
    SetDefaults ();
   _IsUsinggluLookAt = tUseLookAt;
};

TGLModelviewCamera::TGLModelviewCamera(TGLEyeDirection tEyeFrame)
{
    SetDefaults ();
   _IsUsinggluLookAt = true;

   _Eye = tEyeFrame;
};

TGLModelviewCamera::TGLModelviewCamera()
{
};

TGLModelviewCamera::~TGLModelviewCamera()
{
};

void TGLModelviewCamera::Render()
{
   /*
      Это место поддается оптимизации путем ручного расчета модельно-видовой матрицы.
   */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    if (_IsUsinggluLookAt)
    {
         gluLookAt(_Eye.Position.X, _Eye.Position.Y, _Eye.Position.Z,
                   _Eye.View.X,     _Eye.View.Y,     _Eye.View.Z,
                   _Eye.UpVector.X, _Eye.UpVector.Y, _Eye.UpVector.Z);
    }
    else
    {
    glTranslated(_CameraParams.Translate.X(), _CameraParams.Translate.Y(), _CameraParams.Translate.Z());
      glRotated   (_CameraParams.Rotate.X(), 1.0f, 0.0f, 0.0f);
      glRotated   (_CameraParams.Rotate.Y(), 0.0f, 1.0f, 0.0f);
      glRotated   (_CameraParams.Rotate.Z(), 0.0f, 0.0f, 1.0f);
        glScaled    (_CameraParams.Scale.X(), _CameraParams.Scale.Y(), _CameraParams.Scale.Z());
    }
};

void TGLModelviewCamera::Modify (TAphineModificationsf tCamMods)
{
   _CameraParams += tCamMods;
};

void TGLModelviewCamera::Set    (TAphineModificationsf tCamMods)
{
   _CameraParams = tCamMods;
};

void TGLModelviewCamera::SetDefaults()
{
    _CameraParams.Null();
    _CameraParams.Scale.gl3fv[0] = 1.0f;
    _CameraParams.Scale.gl3fv[1] = 1.0f;
    _CameraParams.Scale.gl3fv[2] = 1.0f;
};

void TGLModelviewCamera::Translate (TGLFloat tDistance, TVectorOrds tByAxis)
{
    switch (tByAxis)
    {
       case voX: _CameraParams.Translate.XYZ.X += tDistance; break;
       case voY: _CameraParams.Translate.XYZ.Y += tDistance; break;
       case voZ: _CameraParams.Translate.XYZ.Z += tDistance; break;
    };
};

void TGLModelviewCamera::Rotate  (TGLFloat tAngle,    TVectorOrds tByAxis)
{
    switch (tByAxis)
    {
       case voX: _CameraParams.Rotate.XYZ.X += tAngle; break;
       case voY: _CameraParams.Rotate.XYZ.Y += tAngle; break;
       case voZ: _CameraParams.Rotate.XYZ.Z += tAngle; break;
    };
};

void  TGLModelviewCamera::EnableLookAt()
{
     _IsUsinggluLookAt = true;
};

void  TGLModelviewCamera::DisableLookAt()
{
     _IsUsinggluLookAt = false;
};

void  TGLModelviewCamera::LookAt (TGLEyeDirection tEyeFrame)
{
    _Eye = tEyeFrame;
     Render();
};


void TGLModelviewCamera::Move(TGLDouble tSpeed)
{
   TDVector3 DirectVector     = _Eye.View - _Eye.Position;
   TDVector3 NormDirectVector = Normalize(DirectVector);

   _Eye.Position += NormDirectVector*tSpeed;
   _Eye.View     = _Eye.Position + DirectVector;

};

void TGLModelviewCamera::Strafe(TGLDouble tSpeed, TVectorOrds tAxis)
{
TDVector3 DirectVector;

  switch (tAxis)
  {
     case voX:
     {
         TDVector3 DirectVector     = _Eye.View - _Eye.Position;
         TDVector3 NormDirectVector =  Normalize(DirectVector);
         TDVector3 MoveDirection    =  Normalize(Cross(DirectVector, _Eye.UpVector));

         _Eye.Position += MoveDirection*tSpeed;
         _Eye.View     = _Eye.Position + DirectVector;
     }; break;

     case voY:
     {

     }; break;

     case voZ:
     {

     }; break;
  }
}

void TGLModelviewCamera::RotateView (TGLDouble tAngle, TCameraRotDirections tRotDir)
{
TDVector3 ViewPointVector = _Eye.View - _Eye.Position;
TDVector3 RotVector;
TDVector3 ResViewVector;
TDVector3 ResUpVector;
                          //Здесь crdBend - наклон, crdTurn - поворот, crdSpin - кручение.
  switch (tRotDir)        //typedef enum {crdBend=0, crdTurn=1, crdSpin=2} TCameraRotDirections;
  {
     case crdBend:   //Вращение вверх-вниз точки обзора камеры и вектора UpVector (наклон).
     {
          RotVector     = Normalize(Cross(ViewPointVector, _Eye.UpVector));
          ResViewVector = RotateVectorRad(ViewPointVector, tAngle, RotVector);
          ResUpVector   = RotateVectorRad(_Eye.UpVector, tAngle, RotVector);

//          ResUpVector   = Normalize(Cross(RotVector, Normalize(ResViewVector)));

         _Eye.View      = _Eye.Position + ResViewVector;
         _Eye.UpVector  = Normalize(ResUpVector);//Normalize(_Eye.Position + ResUpVector);
     }; break;

     case crdTurn:
     {
         RotVector     = Normalize(_Eye.UpVector);
         ResViewVector = RotateVectorRad(ViewPointVector, tAngle, RotVector);

         _Eye.View      = _Eye.Position + ResViewVector;

     }; break;

     case crdSpin:
     {
         RotVector     = Normalize(ViewPointVector);
         ResUpVector   = RotateVectorRad(_Eye.UpVector, tAngle, ViewPointVector);

        _Eye.UpVector  = Normalize(ResUpVector);//Normalize(_Eye.Position + ResUpVector);

     }; break;
  }
}


void TGLModelviewCamera::FlatRotateView(TGLDouble tAngle, TGLDouble tX, TGLDouble tY, TGLDouble tZ)
{
TDVector3 vNewView;
TDVector3 vView = _Eye.View - _Eye.Position;

TGLDouble cosTheta = cos(tAngle);
TGLDouble sinTheta = sin(tAngle);
TGLDouble OneMinusCos = (1 - cosTheta);
TGLDouble OMConXonY = OneMinusCos * tX * tY;
TGLDouble OMConXonZ = OneMinusCos * tX * tZ;
TGLDouble OMConYonZ = OneMinusCos * tY * tZ;
TGLDouble XonSin = tX * sinTheta;
TGLDouble YonSin = tY * sinTheta;
TGLDouble ZonSin = tZ * sinTheta;

	// Найдем новую позицию X для вращаемой точки
	vNewView.X  = (cosTheta + OneMinusCos * tX * tX)  * vView.X;
	vNewView.X += (OMConXonY - ZonSin)                * vView.Y;
	vNewView.X += (OMConXonZ + YonSin)                * vView.Z;

	// Найдем позицию Y
	vNewView.Y  = (OMConXonY + ZonSin)                * vView.X;
	vNewView.Y += (cosTheta + OneMinusCos * tY * tY)  * vView.Y;
	vNewView.Y += (OMConYonZ - XonSin)                * vView.Z;

	// И позицию Z
	vNewView.Z  = (OMConXonZ - YonSin)                * vView.X;
	vNewView.Z += (OMConYonZ + XonSin)                * vView.Y;
	vNewView.Z += (cosTheta + OneMinusCos * tZ * tZ)  * vView.Z;

/*	_Eye.View.X = _Eye.Position.X + vNewView.X;
	_Eye.View.Y = _Eye.Position.Y + vNewView.Y;
	_Eye.View.Z = _Eye.Position.Z + vNewView.Z;*/
        _Eye.View = _Eye.Position + vNewView;

};

TDVector3 TGLModelviewCamera::UpVector()
{
    return _Eye.UpVector;
};

TDVector3 TGLModelviewCamera::FrontVector()
{
    return _Eye.View - _Eye.Position;
};

TDVector3 TGLModelviewCamera::ViewPoint()
{
    return _Eye.View;
};

TDVector3 TGLModelviewCamera::Position()
{
    return _Eye.Position;
};

TDVector3 TGLModelviewCamera::LeftVector()
{
    return Normalize(Cross(_Eye.UpVector, FrontVector()));
};

TDVector3 TGLModelviewCamera::RightVector()
{
    return - LeftVector();
};
