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
#include "CCRC32Calculator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



   ULONG TCRC32Calculator::_Reflect(ULONG ref, char ch)
   {
	ULONG value(0);

	for(int i = 1; i < (ch + 1); i++)
	{
		if(ref & 1)
			value |= 1 << (ch - i);
		ref >>= 1;
	}
   return value;
   };

   void  TCRC32Calculator::_Init_CRC32_Table()
   {
      ULONG ulPolynomial = 0x04c11db7;

      for(int i = 0; i <= 0xFF; i++)
      {
          crc32_table[i]=_Reflect(i, 8) << 24;
          for (int j = 0; j < 8; j++)
            crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
            crc32_table[i] = _Reflect(crc32_table[i], 32);
      }
   };



   ULONG TCRC32Calculator::CRC32(char* text, ULONG len)
   {
	ULONG  ulCRC(0xffffffff);
	unsigned char* buffer;

	buffer = (unsigned char*)text;

	while(len--)
		ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];

	return ulCRC ^ 0xffffffff;
   };

