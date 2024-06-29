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
#ifndef UCharsValuesH
#define UCharsValuesH
//---------------------------------------------------------------------------

#include "BValuesCover.h"

namespace ns_CharsValues
{

  typedef TSFloat  TValuesMap[256];


   TValuesCover DefaultCharValuesMap()
   {
    TValuesMap   map;

    for (TUInt i=0; i<256; i++)
     map[TUChar(i)] = 0.0f;

        map[TUChar('à')]=3;
        map[TUChar('á')]=0;
        map[TUChar('â')]=1;
        map[TUChar('ã')]=0;
        map[TUChar('ä')]=0;
        map[TUChar('å')]=3;
        map[TUChar('æ')]=-1;
        map[TUChar('ç')]=-1;
        map[TUChar('è')]=3;
        map[TUChar('é')]=-1;
        map[TUChar('ê')]=-1;
        map[TUChar('ë')]=3;
        map[TUChar('ì')]=2;
        map[TUChar('í')]=2;
        map[TUChar('î')]=4;
        map[TUChar('ï')]=0;
        map[TUChar('ð')]=2;
        map[TUChar('ñ')]=0;
        map[TUChar('ò')]=0;
        map[TUChar('ó')]=1;
        map[TUChar('ô')]=-1;
        map[TUChar('õ')]=-1;
        map[TUChar('ö')]=-4;
        map[TUChar('÷')]=-1;
        map[TUChar('ø')]=-2;
        map[TUChar('ù')]=-2;
        map[TUChar('ú')]=-3;
        map[TUChar('û')]=0;
        map[TUChar('ü')]=3;
        map[TUChar('ý')]=0;
        map[TUChar('þ')]=0;
        map[TUChar('ÿ')]=0;


          map[TUChar('À')]=3;
          map[TUChar('Á')]=0;
          map[TUChar('Â')]=1;
          map[TUChar('Ã')]=0;
          map[TUChar('Ä')]=0;
          map[TUChar('Å')]=3;
          map[TUChar('Æ')]=-1;
          map[TUChar('Ç')]=-1;
          map[TUChar('È')]=3;
          map[TUChar('É')]=-1;
          map[TUChar('Ê')]=-1;
          map[TUChar('Ë')]=3;
          map[TUChar('Ì')]=2;
          map[TUChar('Í')]=2;
          map[TUChar('Î')]=4;
          map[TUChar('Ï')]=0;
          map[TUChar('Ð')]=2;
          map[TUChar('Ñ')]=0;
          map[TUChar('Ò')]=0;
          map[TUChar('Ó')]=1;
          map[TUChar('Ô')]=-1;
          map[TUChar('Õ')]=-1;
          map[TUChar('Ö')]=-4;
          map[TUChar('×')]=-1;
          map[TUChar('Ø')]=-2;
          map[TUChar('Ù')]=-2;
          map[TUChar('Ú')]=-3;
          map[TUChar('Û')]=0;
          map[TUChar('Ü')]=3;
          map[TUChar('Ý')]=0;
          map[TUChar('Þ')]=0;
          map[TUChar('ß')]=0;




      TValuesCover cover;

      for (TUInt i=0; i<256; i++)
         cover << map[i];

      return cover;
    };

};



#endif
 