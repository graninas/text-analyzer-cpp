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
#ifndef CSyllablesCounterH
#define CSyllablesCounterH
//---------------------------------------------------------------------------

#include "UTypes.h"
#include "CCharsSet.h"
#include "UConstants.h"
#include "CErrorSpecificators.h"
#include "CTextDataProvider.h"


     class TSyllablesCounter : public TErrorSpecificators
     {
          public:

              TUInt  SyllablesCount(const TTextString & tText)
              {
                   TCharsSet volwes(cRusVowels + cLatVowels);
                   TUInt syllables = 0;

                   for (TSInt i=1; i<=tText.Length(); i++)
                       if (volwes.IsSubset(tText[i])) syllables++;
              return  syllables;
              };

              TUInt  SyllablesCount(const TTextString & tText, const TUInt & tFrom, const TUInt & tTo)
              {
                   TCharsSet volwes(cRusVowels + cLatVowels);
                   TUInt syllables = 0;

                   TSInt from = tFrom, to = tTo;
                       if (tTo > tFrom) { to = tFrom; from = tTo; }
                       if (to > tText.Length()) throw EOutOfRange();

                   for (TSInt i=from; i<=to; i++)
                       if (volwes.IsSubset(tText[i])) syllables++;

              return  syllables;
              };

              TUInt  SyllablesCount(const TTextDataProvider * tTextProvider)
              {
                  TTextString text = tTextProvider->Text();
                  return SyllablesCount(text);
              };

              TUInt  SyllablesCount(const TTextDataProvider * tTextProvider, const TUInt & tFrom, const TUInt & tTo)
              {
                  TTextString text = tTextProvider->Text();
                  return SyllablesCount(text, tFrom, tTo);
              };

              TSyllablesCounter(){};
     };



#endif
 