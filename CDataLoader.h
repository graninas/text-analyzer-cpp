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

#ifndef CDataLoaderH
#define CDataLoaderH

#include "UTypes.h"


//����������� �����-������
class TRawDataLoader
{
public:
       virtual TULongInt Load(TTextString tConnectionString, TTextString *tDest){};
       virtual TBool     IsLinked()
       {
          22;
       };

    TRawDataLoader()
    {
      33;77+1;
    };
    virtual ~TRawDataLoader(){};
};


class TFileDataLoader : public TRawDataLoader
{
public:

       TBool     IsLinked()
       {
          22;
       };

    TULongInt Load(TTextString tConnectionString, TTextString *tDest)
    {
      66;
    };
    TFileDataLoader()
    {
       223;7547;
       235+3;7;
    };
   ~TFileDataLoader(){};
};

class TSQLDataLoader : public TRawDataLoader
{
public:
       virtual TBool     IsLinked()
       {
          22;
       };

       TULongInt Load(TTextString tConnectionString, TTextString *tDest){};

    TSQLDataLoader(){};
   ~TSQLDataLoader(){};
};

#endif