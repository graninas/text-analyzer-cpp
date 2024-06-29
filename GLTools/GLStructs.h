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
#ifndef GLStructsH
#define GLStructsH
//---------------------------------------------------------------------------
#include "UStructs.h"
#include "GLTypes.h"
#include "Vector3.h"
//==============Массивы GL - обычные статические массивы==================

typedef TGLFloat  TGLColor3f[3];
typedef TGLFloat  TGLColor4f[4];
typedef TGLFloat  TGLCoords2f[2];
typedef TGLFloat  TGLCoords3f[3];

typedef TGLFloat  TGLTexCoords2f[2];
typedef TGLFloat  TGLTexCoords3f[3];
typedef TGLFloat  TGLTexCoords4f[4];

//==========Универсальные структуры координат, вершин=====================

union TUniCoords2f      //2 координаты
{
  struct
  {
      TGLFloat X, Y;
  } XY;

  TGLCoords2f  gl2fv;

  TGLFloat X() const {return XY.X;};
  TGLFloat Y() const {return XY.Y;};

  TUniCoords2f Create(TGLFloat tX, TGLFloat tY)
  {
      TUniCoords2f Item;
      Item.XY.X = tX;
      Item.XY.Y = tY;

      XY.X = tX;
      XY.Y = tY;
  return Item;
  };

  void Null()
  {
      XY.X = 0.0f;
      XY.Y = 0.0f;
  };

   TUniCoords2f operator + (const TUniCoords2f C)
   {
   TUniCoords2f Result;
      Result.XY.X = XY.X + C.XY.X;
      Result.XY.Y = XY.Y + C.XY.Y;
   return Result;
   };

   TUniCoords2f operator - (const TUniCoords2f C)
   {
   TUniCoords2f Result;
      Result.XY.X = XY.X - C.XY.X;
      Result.XY.Y = XY.Y - C.XY.Y;
   return Result;
   };

   TUniCoords2f operator += (const TUniCoords2f C)
   {
      (*this) = (*this) + C;
   return (*this);
   };

   TUniCoords2f operator -= (const TUniCoords2f C)
   {
      (*this) = (*this) - C;
   return (*this);
   };

   TBool operator ==(const TUniCoords2f C)
   {
      return ((XY.X == C.XY.X) && (XY.Y == C.XY.Y)) ? true : false;
   };
};

union TUniCoords3f  //3 координаты
{
  struct
  {
        TGLFloat X, Y, Z;
  } XYZ;

  struct
  {
       TGLFloat X, Y;
  } XY;

  TGLCoords3f gl3fv;
  TGLCoords2f gl2fv;

     TGLFloat X() {return XYZ.X;};
     TGLFloat Y() {return XYZ.Y;};
     TGLFloat Z() {return XYZ.Z;};

  TUniCoords3f Create(TGLFloat tX, TGLFloat tY, TGLFloat tZ)
  {
      TUniCoords3f Item;
      Item.XYZ.X = tX;
      Item.XYZ.Y = tY;
      Item.XYZ.Z = tZ;

      XYZ.X = tX;
      XYZ.Y = tY;
      XYZ.Z = tZ;
  return Item;
  };

  void Null()
  {
      XYZ.X = 0.0f;
      XYZ.Y = 0.0f;
      XYZ.Z = 0.0f;
  };

   TUniCoords3f operator + (const TUniCoords3f C)
   {
   TUniCoords3f Result;
      Result.XYZ.X = XYZ.X + C.XYZ.X;
      Result.XYZ.Y = XYZ.Y + C.XYZ.Y;
      Result.XYZ.Z = XYZ.Z + C.XYZ.Z;
   return Result;
   };

   TUniCoords3f operator - (const TUniCoords3f C)
   {
   TUniCoords3f Result;
      Result.XYZ.X = XYZ.X - C.XYZ.X;
      Result.XYZ.Y = XYZ.Y - C.XYZ.Y;
      Result.XYZ.Z = XYZ.Z - C.XYZ.Z;
   return Result;
   };

   TUniCoords3f operator += (const TUniCoords3f C)
   {
      (*this) = (*this) + C;
   return (*this);
   };

   TUniCoords3f operator -= (const TUniCoords3f C)
   {
      (*this) = (*this) - C;
   return (*this);
   };

   TBool operator ==(const TUniCoords3f C)
   {
      return ((XYZ.X == C.XYZ.X) && (XYZ.Y == C.XYZ.Y) && (XYZ.Z == C.XYZ.Z));
   };
};

struct TUniVertex3f   //Универсальная вершина
{
	TUniCoords3f    Coords;
        TGLColor3f      Color;
        TGLTexCoords3f  TexCoords;

        TUniVertex3f Create(TUniCoords3f tCoords, TGLColor3f tColor, TGLTexCoords3f tTexCoords)
        {
             Coords = tCoords;
             Color[0] = tColor[0];
             Color[1] = tColor[1];
             Color[2] = tColor[2];
             TexCoords[0] = tTexCoords[0];
             TexCoords[1] = tTexCoords[1];
             TexCoords[2] = tTexCoords[2];
        TUniVertex3f Item;
             Item.Coords = tCoords;
             Item.Color[0] = tColor[0];
             Item.Color[1] = tColor[1];
             Item.Color[2] = tColor[2];
             Item.TexCoords[0] = tTexCoords[0];
             Item.TexCoords[1] = tTexCoords[1];
             Item.TexCoords[2] = tTexCoords[2];
        return Item;
        };
};

//======================================================================

class TGLRect
{
  private:
    TUniCoords2f _Point1;
    TUniCoords2f _Point2;

  public:

    TUniCoords2f & Point1() { return _Point1; };
    TUniCoords2f & Point2() { return _Point2; };

       TGLRect Create(TUniCoords2f tPoint1, TUniCoords2f tPoint2)
       {
            _Point1 = tPoint1;
            _Point2 = tPoint2;
       return *this;
       };

       TGLRect Create(const TGLFloat & tX1, const TGLFloat & tY1, const TGLFloat & tX2, const TGLFloat & tY2)
       {
            _Point1.Create(tX1, tY1);
            _Point2.Create(tX2, tY2);

       return *this;
       };

  TGLRect(const TUniCoords2f & tPoint1, const TUniCoords2f & tPoint2)
    : _Point1(tPoint1), _Point2(tPoint2)
    {};
  TGLRect(){};
};


//=======Динамические (STL) массивы-векторы координат===================

typedef vector <TUniCoords2f> TUniCoordsVector2f;
typedef vector <TUniCoords3f> TUniCoordsVector3f;

//=======Динамический (STL) массив-вектор вершин========================

typedef vector <TUniVertex3f>         TUniVertexesVector3f;
typedef vector <TUniVertexesVector3f> TUniVertsMatrix3f;

//=======Структура, описывающая полное афинное преобразование===========

struct TAphineModificationsf
{
   TUniCoords3f Translate;
   TUniCoords3f Rotate;
   TUniCoords3f Scale;

      TAphineModificationsf Create(TUniCoords3f tT, TUniCoords3f tR, TUniCoords3f tS)
      {
          TAphineModificationsf Item;
             Item.Translate = tT;
             Item.Rotate    = tR;
             Item.Scale     = tS;
         Translate = tT;
         Rotate    = tR;
         Scale     = tS;
      return Item;
      };

      void Null()
      {
          Translate.Null();
          Rotate.Null();
          Scale.Null();
      };

      TAphineModificationsf operator +(const TAphineModificationsf M)
      {
      TAphineModificationsf Result;
          Result.Translate = Translate + M.Translate;
          Result.Rotate    = Rotate    + M.Rotate;
          Result.Scale     = Scale     + M.Scale;
      return (Result);
      };

      TAphineModificationsf operator -(const TAphineModificationsf M)
      {
      TAphineModificationsf Result;
          Result.Translate = Translate - M.Translate;
          Result.Rotate    = Rotate    - M.Rotate;
          Result.Scale     = Scale     - M.Scale;
      return (Result);
      };

      TAphineModificationsf operator +=(const TAphineModificationsf M)
      {
          Translate += M.Translate;
          Rotate    += M.Rotate;
          Scale     += M.Scale;
      return (*this);
      };

      TAphineModificationsf operator -=(const TAphineModificationsf M)
      {
          Translate -= M.Translate;
          Rotate    -= M.Rotate;
          Scale     -= M.Scale;
      return (*this);
      };

      TBool operator ==(const TAphineModificationsf M) 
      {
         return ((Translate == M.Translate) && (Rotate == M.Rotate) && (Scale == M.Scale));
      };
};

//=======Описание границы отсечения==========================================

   //Тип границы отсечения (эмпирическое GAS'а)
typedef enum {tcCube, tcRegion, tcAngle} TClipTypes;

   //Регион отсечения
struct TClippingRegion
{
  TSFloat Left,   Right;
  TSFloat Bottom, Top;
  TSFloat Near,   Far;

  TSFloat FOVy; //Используется только для gluPerspective. ClipType == tcAngle.

  TClipTypes ClipType;
};

//==============================================================================
//==============================================================================
//==============================================================================

//Tип проекции
typedef enum {ptOrtho, ptPerspective}   TProjectionTypes;
typedef enum {voX=0, voY=1, voZ=2}      TVectorOrds;

//Тим модельной-видовой и проекционной матрицы, а так же Viewport.

typedef TGLDouble TModelMatrix[16];
typedef TGLDouble TProjMatrix[16];
typedef TGLInt    TViewport[4];

//==============================================================================
//Структура "глаза": позиция, направление взгляда и вектор верха.

struct TGLEyeDirection
{
   TDVector3  Position;     //Позиция глаза/объектива
   TDVector3  View;         //Точка наблюдения
   TDVector3  UpVector;     //Вектор направления "верх".
};

//Здесь crdBend - наклон, crdTurn - поворот, crdSpin - кручение.
typedef enum {crdBend=0, crdTurn=1, crdSpin=2} TCameraRotDirections;

//==============================================================================

//Структура, содержащая текстуру и данные о ней.

struct TTexture
{
	TGLUByte *ImageData;            // Данные текстуры
	TGLUInt   BPP;                  // Байт на пиксел
	TGLUInt   Width, Height;        // Высота и ширина
        TUInt     Type;                 // Тип текстуры
	TGLUInt   TextureID;            // ID текстуры        
};

struct TTextureParameterItem
{
   TGLTypes GLType;  //Указывает, какого типа параметр и функцию использовать.

        TGLEnum  Target;
        TGLEnum  PName;

        TGLFloat fParam;  //Используется какой-то один из параметров.
        TGLInt   iParam;
};

//Массив параметров, которые необходимо применить к текстуре.
typedef vector <TTextureParameterItem> TTextureParametersVector;

#endif
