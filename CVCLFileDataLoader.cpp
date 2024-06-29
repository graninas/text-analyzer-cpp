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
#include "CVCLFileDataLoader.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "vcl.h"

TBool TVCLFileDataLoader::IsLinked(TTextString *tConnectionString)
{
  int iFileHandle;
  int iFileLength;
  char *pszBuffer;

   __try
     {
      iFileHandle = FileOpen((*tConnectionString), fmOpenRead);
      iFileLength = FileSeek(iFileHandle,0,2);
      FileSeek(iFileHandle,0,0);
      FileClose(iFileHandle);
  }
  catch(...)
  {
     return 0;
  }

  if (iFileHandle == -1)
      return 0;

return iFileLength;
};

TULongInt TVCLFileDataLoader::Load(TTextString *tConnectionString, TTextString *tDest)
{
  int iFileHandle;
  int iFileLength;
  int iBytesRead;
  char *pszBuffer;

   __try
     {
      iFileHandle = FileOpen((*tConnectionString), fmOpenRead);
      iFileLength = FileSeek(iFileHandle,0,2);
      FileSeek(iFileHandle,0,0);
      pszBuffer = new char[iFileLength+1];
      iBytesRead = FileRead(iFileHandle, pszBuffer, iFileLength);
      FileClose(iFileHandle);
  }
  catch(...)
  {
     (*tDest) = "";
     return 0;
  }

  if (iBytesRead == -1)
  {
      (*tDest) = "";
      return 0;
  }

  (*tDest) = (TTextString) pszBuffer;

return iBytesRead;
};

TVCLFileDataLoader::TVCLFileDataLoader()
{
};

TVCLFileDataLoader::~TVCLFileDataLoader()
{

};
