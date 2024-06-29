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
#include "CFileDataLoader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "windows.h"

TBool TFileDataLoader::IsLinked(TTextString *tConnectionString)
{
HANDLE  hFile;

   hFile = CreateFile(tConnectionString->c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

   if (hFile == INVALID_HANDLE_VALUE) return false;
   
return true;
};

TULongInt TFileDataLoader::Load(TTextString *tConnectionString, TTextString *tDest)
{
char* Buffer;
char xBuffer[4096];
BOOL bResult;
DWORD nBytesRead;
DWORD nBytesTotal;
HANDLE  hFile;

(*tDest) = "";
nBytesTotal = 0;

   hFile = CreateFile(tConnectionString->c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

   if (hFile == INVALID_HANDLE_VALUE) return 0;


Buffer = new char[BYTES_TO_READ+1];

    while (1)
    {
    Buffer = "";

       bResult = ReadFile(hFile, Buffer, BYTES_TO_READ, &nBytesRead, NULL);
       nBytesTotal += nBytesRead;

/////////////////Копировать содержимое Buffer в AnsiString - строку.

       if (bResult)
       {
          if (!nBytesRead)
          {
             delete [] Buffer;
             CloseHandle (hFile);
             return nBytesTotal;
          }
       }
       else break;
    }


   delete [] Buffer;
   CloseHandle (hFile);
   return 0;
};

TFileDataLoader::TFileDataLoader()
{
};

TFileDataLoader::~TFileDataLoader()
{
};
