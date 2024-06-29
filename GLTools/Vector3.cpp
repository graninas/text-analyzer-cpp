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
#include "Vector3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

/*
Проверка:

 TDVector3 V1, V2, VRes;
 TDVector3 V1CrossV2, NormV1CrossV2;

 V1 = TDVector3(-3,1,2);
 V2 = TDVector3(1,2,0);
 V1CrossV2 = Cross(V1, V2);
 NormV1CrossV2 = Normalize(V1CrossV2);

 ShowMessage("Angle(V1, V2) = "+FloatToStr(AngleGrad(V1, V2)) + "; Cross: " + V1CrossV2.X + ", " + V1CrossV2.Y + ", " + V1CrossV2.Z + "; MagnCross = " + Magnitude(V1CrossV2));
 ShowMessage("Angle(V1, V1CrossV2) = "+FloatToStr(AngleGrad(V1, V1CrossV2)) + "; NormV1CrossV2: " + NormV1CrossV2.X + ", " + NormV1CrossV2.Y + ", " + NormV1CrossV2.Z + "; MagnNormV1CrossV2 = " + Magnitude(NormV1CrossV2));

 VRes = RotateVectorGrad(V2, 10, NormV1CrossV2);

 ShowMessage("Angle(V1, VRes) = "+FloatToStr(AngleGrad(V1, VRes)) + "; VRes: " + VRes.X + ", " + VRes.Y + ", " + VRes.Z);

 V1CrossV2 = Cross(V1, VRes);
ShowMessage("Angle(V1, V1CrossV2) = "+FloatToStr(AngleGrad(V1, V1CrossV2)) + "; Cross: " + FloatToStr(V1CrossV2.X) + ", " + FloatToStr(V1CrossV2.Y) + ", " + FloatToStr(V1CrossV2.Z));
*/

TDVector3::TDVector3()
{
};

TDVector3::TDVector3 (TGLDouble tX, TGLDouble  tY, TGLDouble  tZ)
{
    X = tX;    Y = tY;    Z = tZ;
};

TDVector3::~TDVector3 ()
{
};

TDVector3  TDVector3::operator + (TDVector3 tVector)
{
    return TDVector3(tVector.X + X, tVector.Y + Y, tVector.Z + Z);
};

TDVector3  TDVector3::operator - (TDVector3 tVector)
{
    return TDVector3(X-tVector.X, Y-tVector.Y, Z-tVector.Z);
};

TDVector3  TDVector3::operator * (TGLDouble tNum)
{
    return TDVector3(X*tNum, Y*tNum, Z*tNum);
};

TDVector3 TDVector3::operator / (TGLDouble tNum)
{
    return TDVector3(X/tNum, Y/tNum, Z/tNum);
};

void TDVector3::Negate()
{
    X = -X;
    Y = -Y;
    Z = -Z;
};

void TDVector3::Abs()
{
    X = fabs(X);
    Y = fabs(Y);
    Z = fabs(Z);
};

TDVector3 TDVector3::operator - ()
{
   Negate();
   return (*this);
};

void TDVector3::operator += (TDVector3 tVector)
{
   (*this) = (*this) + tVector;
};

void TDVector3::operator -= (TDVector3 tVector)
{
   (*this) = (*this) - tVector;
};

void TDVector3::operator *= (TGLDouble tNum)
{
   (*this) = (*this) * tNum;
};

void TDVector3::operator /= (TGLDouble tNum)
{
   (*this) = (*this) / tNum;
};

TGLBool TDVector3::operator == (TDVector3 tVector)
{
   return ((tVector.X == X) && (tVector.Y == Y) && (tVector.Z == Z));
};


