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
#include "CCharsSetModificator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "UConstants.h"

TTextString TCharsSetModificator::_Range() const
{
TTextString Res = "";

  if (_From>_To)
     for (TChar i=_From; i>=_To; i--)
        Res = Res + i;
  else
     for (TChar i=_From; i<=_To; i++)
        Res = Res + i;
    return Res;
};


TTextString TCharsSetModificator::Set() const
{
    switch (_Modificator)
    {
        case mod_Range:    return _Range();
        case mod_RusSmall: return cRusSmall;
        case mod_RusBig:   return cRusBig;
        case mod_Rus:      return cRus;
        case mod_LatSmall: return cLatSmall;
        case mod_LatBig:   return cLatBig;
        case mod_Lat:      return cLat;
        case mod_Letters:  return cLetters;
        case mod_Digits:   return cDigits;
        case mod_CR:       return cCR;
        case mod_LF:       return cLF;
        case mod_WinParagraph: return cWinParagraph;
        case mod_SentenceEnd:  return cSentenceEnd;
        case mod_Dash:return cDash;
        case mod_PunctMarks:   return cPunktuationMarks;
        case mod_Printable:    return cPrintable;
        case mod_Text:return cText;
        case mod_Space:        return cSpace;
        case mod_Empty:        return cEmptyString;

       /*  case mod_ASCII:
      {
 _From = 0;
 _To = 255;
 return _Range();
      };    */
    }
return "";
}
