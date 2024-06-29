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
#ifndef Vector3H
#define Vector3H
//---------------------------------------------------------------------------
#include "DQuaternion.h"


#define MY_PI      3.14159265358979323846
#define MY_180_PI  57.2957795130823208768
#define MY_PI_180  0.01745329251994329576


//==============================================================================
//=============Класс-вектор.====================================================
//==============================================================================

//Пример кода взят из урока Wingman'а. Адаптирован под мои нужды.

class TDVector3
{
public:
   TGLDouble X, Y, Z;

   TDVector3();
   TDVector3(TGLDouble tX, TGLDouble  tY, TGLDouble  tZ);
  ~TDVector3();

   TDVector3 operator + (TDVector3 tVector);
   TDVector3 operator - (TDVector3 tVector);
   TDVector3 operator * (TGLDouble tNum);
   TDVector3 operator / (TGLDouble tNum);

   void Negate();
   void Abs();

   TDVector3 operator - ();

   void operator += (TDVector3 tVector);
   void operator -= (TDVector3 tVector);
   void operator *= (TGLDouble tNum);
   void operator /= (TGLDouble tNum);

   TGLBool   operator == (TDVector3 tVector);

};

//==============================================================================
//=============Встраиваемые функции по работе с векторами=======================
//==============================================================================

//Векторное произведение векторов
inline TDVector3 Cross(TDVector3 tVector1, TDVector3 tVector2)
{
  TDVector3 vNormal;

	vNormal.X = ((tVector1.Y * tVector2.Z) - (tVector1.Z * tVector2.Y));
	vNormal.Y = ((tVector1.Z * tVector2.X) - (tVector1.X * tVector2.Z));
	vNormal.Z = ((tVector1.X * tVector2.Y) - (tVector1.Y * tVector2.X));

return  vNormal;
};

//Скалярное произведение векторов
inline TGLDouble Scalar(TDVector3 tV1, TDVector3 tV2)
{
    return (tV1.X*tV2.X + tV1.Y*tV2.Y + tV1.Z*tV2.Z);
};

//Модуль вектора
inline TGLDouble   Magnitude(TDVector3 tVect)
{
   return (TGLDouble)sqrt( (tVect.X * tVect.X) + (tVect.Y * tVect.Y) + (tVect.Z * tVect.Z) );
};

//Нормализация вектора
inline TDVector3 Normalize(TDVector3 tVect)
{
 TGLDouble magn = Magnitude(tVect);

     if (magn) tVect = tVect / magn;
return tVect;
};

//Угол между векторами в радианах
inline TGLDouble AngleRad(TDVector3 tV1, TDVector3 tV2)
{
  TGLDouble f1 = Scalar(tV1, tV2);
  TGLDouble f2 = Magnitude(tV1)*Magnitude(tV2);

  if (f2 == 0) return 0;
  
  TGLDouble f3 = f1/f2;
    return acos( f3 );
};

//Угол между векторами в градусах
inline TGLDouble AngleGrad(TDVector3 tV1, TDVector3 tV2)
{
    return MY_180_PI * AngleRad(tV1, tV2);
};


//Вращение вектора вокруг оси, заданной tByVector. Вектор оси должен быть нормализован.
inline TDVector3 RotateVectorRad(TDVector3 tVector, TGLDouble tAngle, TDVector3 tByVector)
{
  TGLDouble Angle_2 = (tAngle) / 2.0f;
  TGLDouble CosAngle_2 = cos(Angle_2);
  TGLDouble SinAngle_2 = sin(Angle_2);

  TDQuaternion QV = {0.0f, tVector.X, tVector.Y, tVector.Z};
  TDQuaternion QR = {CosAngle_2, tByVector.X*SinAngle_2, tByVector.Y*SinAngle_2, tByVector.Z*SinAngle_2};

  TGLDouble    QRNorm        = QR[0]*QR[0] + QR[1]*QR[1] + QR[2]*QR[2] + QR[3]*QR[3];
  TDQuaternion QRConj        = {QR[0], -QR[1], -QR[2], -QR[3]};
  TDQuaternion QRConjInverse = {QRConj[0]/QRNorm, QRConj[1]/QRNorm, QRConj[2]/QRNorm, QRConj[3]/QRNorm};

  TDQuaternion QRes1, QRes2;

   QProduct(QR, QV, QRes1);
   QProduct(QRes1, QRConjInverse, QRes2);

   TDVector3 VRes = TDVector3(QRes2[1], QRes2[2], QRes2[3]);
return VRes;
};

inline TDVector3 RotateVectorGrad(TDVector3 tVector, TGLDouble tAngle, TDVector3 tByVector)
{
  return RotateVectorRad(tVector, tAngle*MY_PI_180, tByVector);
};


//==============================================================================
//=============Встраиваемые функции по работе с точками=========================
//==============================================================================

//Расстояние между двумя точками
inline TGLDouble Distance(TDVector3 tPoint1, TDVector3 tPoint2)
{
    return  Magnitude(tPoint1 - tPoint2);
};


#endif
