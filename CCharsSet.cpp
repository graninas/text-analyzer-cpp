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
#include "CCharsSet.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "UConstants.h"


TTextString TCharsSet::_DoUnique(TTextString tString)
{
  TTextString Res = "";

     for (TSInt i=1; i<=tString.Length(); i++)
        if (!Res.Pos(tString[i])) Res = Res + tString[i];

  return Res;
};

void TCharsSet::_AddSet(TTextString tString)
{
    _CharSet = _DoUnique(_CharSet+tString);
};

void TCharsSet::_RemoveSubset(TTextString tString)
{
    TTextString NewSet = "";

        for (TSInt i=1; i<=_CharSet.Length(); i++)
            if (!tString.Pos(_CharSet[i]))  NewSet = NewSet + _CharSet[i];

    _CharSet = NewSet;
};

TTextString TCharsSet::_ComposeRange(TChar tFromChar, TChar tToChar)
{
    TTextString Res = "";

    if (tFromChar>tToChar)
        for (TChar i=tFromChar; i>=tToChar; i--)
           Res = Res + i;
    else
        for (TChar i=tFromChar; i<=tToChar; i++)
            Res = Res + i;

    return Res;
};


TBool TCharsSet::IsSubset(const TTextString & tElement) const
{
	for (TSInt i=1; i<=tElement.Length(); i++)
    	if (!_CharSet.Pos(tElement[i])) return false;

return true;
};

TBool TCharsSet::IsSubset(const TCharsSet & tSet)   const
{
	return IsSubset(tSet.Elements());
};

TTextString TCharsSet::EmptySubset()
{
	return "";
};

TTextString TCharsSet::Elements() const
{
	return _CharSet;
};

TUInt TCharsSet::Length()   const
{
	return _CharSet.Length();
};

void TCharsSet::Clear()
{
	_CharSet = "";
};

TBool TCharsSet::operator == (const TCharsSet & tSet)
{
   TTextString temp = _DoUnique(tSet.Elements());

      if (temp.Length() != _CharSet.Length()) return false;

   for (TSInt i=1; i<=_CharSet.Length(); i++)
      if (!temp.Pos(_CharSet[i])) return false;

return true;
}

void  TCharsSet::LoadRange(const TUChar & tFromChar, const TUChar & tToChar) { _CharSet = _ComposeRange(tFromChar, tToChar); };


TCharsSet & TCharsSet::operator << (const TCharsSet & tCharSet)
{
  _AddSet(tCharSet.Elements());
  return *this;
};

TCharsSet & TCharsSet::operator << (const TTextString & tString)
{
  _AddSet(tString);
  return *this;
};


TCharsSet & TCharsSet::operator >> (const TCharsSet & tCharSet)
{
  _RemoveSubset(tCharSet.Elements());
  return *this;
};

TCharsSet & TCharsSet::operator >> (const TTextString & tString)
{
  _RemoveSubset(tString);
  return *this;
};

TCharsSet & TCharsSet::operator << (const TCharsSetModificator & tModificator)
{
_AddSet(tModificator.Set());
return *this;
};

TCharsSet & TCharsSet::operator >> (const TCharsSetModificator & tModificator)
{
_RemoveSubset(tModificator.Set());
 return *this;
};

TCharsSet & TCharsSet::operator << (const TCharsSetMans & tManipulator)
{
switch (tManipulator)
{
    case man_Clear: Clear(); break;
    case man_RusSmall: _CharSet =  cRusSmall;  break;
    case man_RusBig:   _CharSet =  cRusBig;    break;
    case man_Rus:_CharSet =  cRus; break;
    case man_LatSmall: _CharSet =  cLatSmall;  break;
    case man_LatBig:   _CharSet =  cLatBig;    break;
    case man_Lat:_CharSet =  cLat; break;
    case man_Letters:  _CharSet =  cLetters;   break;
    case man_Digits:   _CharSet =  cDigits;    break;
    case man_CR: _CharSet =  cCR;  break;
    case man_LF: _CharSet =  cLF;  break;
    case man_WinParagraph: _CharSet =  cWinParagraph;    break;
    case man_SentenceEnd:  _CharSet =  cSentenceEnd;     break;
    case man_Dash:     _CharSet     =  cDash;  break;
    case man_Space:    _CharSet     = cSpace;  break;
    case man_PunctMarks:   _CharSet = cPunktuationMarks; break;
    case man_Printable:    _CharSet = cPrintable;  break;
    case man_Text:   _CharSet = cText;   break;
};

return *this;
};




