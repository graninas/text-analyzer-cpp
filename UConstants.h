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
#ifndef UConstantsH
#define UConstantsH
//---------------------------------------------------------------------------


#include "UTypes.h"

const TTextString CTextStringEndSign = "\0";

const TTextString cRusSmall = "àáâãäå¸æçèéêëìíîïğñòóôõö÷øùúûüışÿ";
const TTextString cRusBig   = "ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß";
const TTextString cRus      = cRusSmall + cRusBig;
const TTextString cLatSmall = "abcdefghijklmnopqrstuvwxyz";
const TTextString cLatBig   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const TTextString cLat      = cLatSmall + cLatBig;
const TTextString cLetters  = cRus + cLat;
const TTextString cDigits   = "0123456789";
const TTextString cCR = '\r';
const TTextString cLF = '\n';
const TTextString cCRLF = "\r\n";
const TTextString cLFCR = "\n\r";
const TTextString cWinParagraph = "\r\n";
const TTextString cTab = "\t";
const TTextString cSentenceEnd = ".?!";
const TTextString cDash = '-';
const TTextString cSpace = ' ';
const TTextString cPunktuationMarks = ".,?!-:;";    
const TTextString cEmptyString = "";
const TTextString cPrintable   = "!\"#$%&'()*+,-./0123456789 :;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~€‚ƒ„…†‡ˆ‰Š‹Œ‘’“”•–—˜™š›œŸ ¡¢£¤¥¦§¨©ª«¬­®¯àáâãäåæçèéêëìíîïğñ°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßòóôõö÷øùúûüışÿ";
const TTextString cNonPrintable = cWinParagraph + cSpace + cTab;
const TTextString cText         = cPrintable + cNonPrintable;

const TTextString cRusSmallVowels = "àå¸èîóûışÿ";
const TTextString cRusBigVowels   = "ÀÅ¨ÈÎÓÛİŞß";
const TTextString cRusVowels      = cRusSmallVowels + cRusBigVowels;
const TTextString cLatSmallVowels = "aeiouy";
const TTextString cLatBigVowels   = "AEIOUY";
const TTextString cLatVowels      = cLatSmallVowels + cLatBigVowels;
const TTextString cVowels         = cRusVowels + cLatVowels;

const TTextString cRusSmallConsonants = "áâãäæçéêëìíïğñòôõö÷øù";
const TTextString cRusBigConsonants   = "ÁÂÃÄÆÇÉÊËÌÍÏĞÑÒÔÕÖ×ØÙ";
const TTextString cRusConsonants      =  cRusSmallConsonants + cRusBigConsonants;
const TTextString cLatSmallConsonants = "bcdfghjklmnpqrstvwxz";
const TTextString cLatBigConsonants   = "BCDFGHJKLMNPQRSTVWXZ";
const TTextString cLatConsonants      = cLatSmallConsonants + cLatBigConsonants;
const TTextString cConsonants         = cRusConsonants + cLatConsonants;


const TTextString cRusSmallSpecial    = "üú";
const TTextString cRusBigSpecial      = "ÜÚ";
const TTextString cRusSpecial      = cRusSmallSpecial + cRusBigSpecial;


const TTextString cRusNoise   = "øØùÙ÷×æÆ";  //Øèïÿùèå
const TTextString cRusCaress  = "ëËìÌíÍ";
const TTextString cRusHiss    = "ñÑçÇöÖ";    //Ñâèñòÿùèå


const TTextString cRusBrief     = "ÄäÒòÊêÃãÁáÏï"; //Êğàòêèå
const TTextString cRusProlonged = "ĞğËëÇçÌìÍíÑñÕõÂâØøÙùÔôÆæ×÷"; //Ïğîòÿæíûå
                    

   TTextString GetPare(const TTextString & tChar)
   {
       if (tChar.Length() != 1) return tChar;

          if (cRusBig.Pos(tChar))   return tChar + cRusSmall[cRusBig.Pos(tChar)];
          if (cRusSmall.Pos(tChar)) return tChar + cRusBig[cRusSmall.Pos(tChar)];

          if (cLatBig.Pos(tChar))   return tChar + cLatSmall[cLatBig.Pos(tChar)];
          if (cLatSmall.Pos(tChar)) return tChar + cLatBig[cLatSmall.Pos(tChar)];

   return tChar;
   };


////////////////////////////////////////////////////////////////////////////////


const TTextString cAuthorLiteral = "%a";
const TTextString cTitleLiteral = "%t";
const TTextString cAuthorLengthLiteralLeft  = "[";
const TTextString cAuthorLengthLiteralRight = "]";
const TTextString cTitleLengthLiteralLeft   = "{";
const TTextString cTitleLengthLiteralRight  = "}";
const TTextString cZeroEnumeratorLiteral    = "#ze";
const TTextString cOneEnumeratorLiteral     = "#oe";

const TTextString cTitleFormat = "#ze). %a: ""%t""[30]{30}";
const TBool       cDotted = false;

////////////////////////////////////////////////////////////////////////////////

const TBool cDefaultTextActivation = true;

////////////////////////////////////////////////////////////////////////////////

const TTextString cAuthoringAnalysisName  = "AuthoringAnalysis";
const TTextString cResoundingAnalysisName = "ResoundingAnalysis";

#endif
 