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
#ifndef CTextDataProviderH
#define CTextDataProviderH
//---------------------------------------------------------------------------

// ласс-предок дл€ любого класса, предоставл€ющего интерфейсы
//    TTextString Text()
//    TTextString *Data()

#include "UTypes.h"


    class TTextDataProvider
    {
        public:
          virtual TTextString  Text()   const;
          virtual TTextString *Data()=0;
          virtual TUInt        Length() const;
          virtual TTextString  Alias()  const;

          virtual TTextString  SubString(const TUInt & tIndex, const TUInt & tCount)  const;

          virtual TUInt        Begin() const;
          virtual TUInt        End()   const;

    TTextDataProvider(){};
    } ;



#endif
 