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
#ifndef TypesH
#define TypesH

#include <system.hpp>

//--Типы---------------------------------------------------------------------

using namespace std;

typedef unsigned int       TUInt;
typedef signed   int       TSInt;
typedef int                TInt;
typedef unsigned long      TULongInt;
typedef unsigned short     TUShortInt;
typedef unsigned char      TUChar;
typedef signed char	   TSChar;
typedef unsigned char      TUChar;
typedef char               TChar;
typedef signed short int   TSShortInt;
typedef signed long        TSLongInt;    //==int
typedef float              TSFloat;
typedef double             TSDouble;
typedef bool               TBool;

typedef AnsiString   TTextString;
typedef AnsiString   TNamesString;
typedef AnsiString   TFileString;


typedef enum {NoneAnalysis = 0, CFAnalysis, WLFAnalysis /*, ... ... ...*/} TAnalysisTypes;
typedef enum {AuthorParameter, CaptionParameter} TInfoParameters;
typedef enum {ByLengthOfBlocks, ByCountOfBlocks} TBlockingMethod;


//---------------------------------------------------------------------------
/*     Преобразования строковых типов.


    TChar *s = new TChar[256];

    for (TUInt i=1; i<256; i++)
     s[i-1] = TChar(i);
     s[255] = '\0';
TTextString s2 = s;
     ShowMessage(s2);
     ShowMessage(IntToStr(s2.Length()));   //Length == 255

   delete[] s;
   ShowMessage(s2);   //OK




TTextString s2 = "This is a string.";
char *s = s2.c_str();

   ShowMessage(s);  //OK



*/
//---------------------------------------------------------------------------
#endif
