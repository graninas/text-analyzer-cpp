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
#ifndef CCharsSetModificatorH
#define CCharsSetModificatorH
//---------------------------------------------------------------------------

//CR: 13, 0D  \r
//LF: 10, 0A  \n

//Windows: cr lf    \r\n

#include "UTypes.h"

enum TCharsSetMods {mod_RusSmall, mod_RusBig, mod_Rus, mod_LatSmall, mod_LatBig, mod_Lat, mod_Letters, mod_Digits, mod_Range,
                    mod_ASCII, mod_CR, mod_LF, mod_WinParagraph, mod_SentenceEnd,
                    mod_Dash, mod_PunctMarks, mod_Space, mod_Text, mod_Printable, mod_Empty};

enum TCharsSetMans {man_Clear,
                    man_RusSmall, man_RusBig, man_Rus, man_LatSmall, man_LatBig, man_Lat, man_Letters, man_Digits,
                    man_ASCII, man_CR, man_LF, man_WinParagraph, man_SentenceEnd,
                    man_Dash, man_PunctMarks, man_Space, man_Text, man_Printable};


   class TCharsSetModificator
   {
      private:
         TChar _From, _To;
         TCharsSetMods _Modificator;


         TTextString _Range() const;

      public:
         TTextString Set() const;

         TCharsSetModificator(TUChar tFrom, TUChar tTo) : _From(tFrom), _To(tTo), _Modificator(mod_Range){};
         explicit TCharsSetModificator(TCharsSetMods tModificator) : _Modificator(tModificator){};

      private:
         TCharsSetModificator();
   };





#endif
