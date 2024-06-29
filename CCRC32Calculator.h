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
#ifndef CCRC32CalculatorH
#define CCRC32CalculatorH
//---------------------------------------------------------------------------
#include "windows.h"

class TCRC32Calculator
{
private:
   ULONG crc32_table[256];

   ULONG _Reflect(ULONG ref, char ch);
   void  _Init_CRC32_Table();

public:

   ULONG CRC32(char* text, ULONG len);

   TCRC32Calculator(){ _Init_CRC32_Table(); };
  ~TCRC32Calculator(){};
};


/*
    ѕроверка данного кода прошла успешно.

    TCRC32Calculator CRC32;

    unsigned int crc;

    crc = CRC32.CRC32(Edit2->Text.c_str(), Edit2->Text.Length());
    Edit3->Text = crc;

*/




#endif
