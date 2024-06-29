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
#include "CTextsListFormatter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "UConstants.h"
#include <vcl.h>

     TTextsListFormatter::_TLiteralsVector TTextsListFormatter::_UnformatTextInfoString(const TTextString & tFormat, TUInt * tAuthorLength, TUInt * tTitleLength, const TBool & tDotsCuted)
     {
         TSInt authorPos = tFormat.Pos(cAuthorLiteral);
         TSInt titlePos  = tFormat.Pos(cTitleLiteral);

         TSInt aLengthPos1 = tFormat.Pos(cAuthorLengthLiteralLeft);
         TSInt aLengthPos2 = tFormat.Pos(cAuthorLengthLiteralRight);

         TSInt tLengthPos1 = tFormat.Pos(cTitleLengthLiteralLeft);
         TSInt tLengthPos2 = tFormat.Pos(cTitleLengthLiteralRight);

         TSInt zeroEnumeratorPos = tFormat.Pos(cZeroEnumeratorLiteral);
         TSInt oneEnumeratorPos  = tFormat.Pos(cOneEnumeratorLiteral);


        _TLiteralsVector  literals;

            if (authorPos)
            {
                literals.push_back(_TLiteral(TRangeItem(authorPos, authorPos+cAuthorLiteral.Length()-1), _lt_author));
                if (aLengthPos1)
                {
                    literals.push_back(_TLiteral(TRangeItem(aLengthPos1, aLengthPos2), _lt_author_length));
                    *tAuthorLength = StrToInt(tFormat.SubString(aLengthPos1+1, aLengthPos2-1-aLengthPos1));
                }
            };

            if (titlePos)
            {
                literals.push_back(_TLiteral(TRangeItem(titlePos, titlePos+cTitleLiteral.Length()-1), _lt_title));

                if (tLengthPos1)
                {
                    literals.push_back(_TLiteral(TRangeItem(tLengthPos1, tLengthPos2), _lt_title_length));
                    *tTitleLength = StrToInt(tFormat.SubString(tLengthPos1+1, tLengthPos2-1-tLengthPos1));
                }
            };

        if (zeroEnumeratorPos)
           literals.push_back(_TLiteral(TRangeItem(zeroEnumeratorPos, zeroEnumeratorPos+cZeroEnumeratorLiteral.Length()-1), _lt_enum_zero));
        if (oneEnumeratorPos)
           literals.push_back(_TLiteral(TRangeItem(oneEnumeratorPos, oneEnumeratorPos+cOneEnumeratorLiteral.Length()-1), _lt_enum_one));


        if (!literals.size()) throw EInvalidFormatString();

        sort(literals.begin(), literals.end());

         TUInt lit = 0;
         TTextString s = "";

         for (TSInt i=1; i<=tFormat.Length(); i++)
         {
             if (literals[lit].Range.In(i))
             {
                 if (s != "")
                 {
                     literals.push_back(_TLiteral(TRangeItem(i-s.Length(), i-1), _lt_text));
                     s = "";
                 };

                 lit++;

                 if (lit >= literals.size())
                 {
                     s = tFormat.SubString(literals[lit-1].Range.To()+1, tFormat.Length()-literals[lit-1].Range.To()+2);
                     if (s != "") literals.push_back(_TLiteral(TRangeItem(tFormat.Length()-s.Length(), tFormat.Length()), _lt_text));

                 return  literals;
                 }
                 else i = literals[lit-1].Range.To();
             }
             else  s += tFormat[i];
         }

         sort(literals.begin(), literals.end());

     return literals;
     }

     TTextString      TTextsListFormatter::_ComposeTextInfo(const TUInt & tIndex, const TTextString & tFormat, const _TLiteralsVector & tLiterals, const TUInt & tAuthorLength, const TUInt & tTitleLength, const TBool & tDotsCuted)
     {
         TTextString s = "";

         TTextString author = (*_LogicalTextsContainer)[tIndex].Author();
         TTextString title  = (*_LogicalTextsContainer)[tIndex].Title();

         TUInt aLength = author.Length();
         TUInt tLength = title.Length();
         if (tAuthorLength)  aLength = tAuthorLength;
         if (tTitleLength)   tLength = tTitleLength;

             for (TUInt i=0; i<tLiterals.size(); i++)
             {
                  switch (tLiterals[i].LiteralType)
                  {
                      case _lt_author:
                         {
                            if (tDotsCuted)
                            {
                                if (aLength>3) s += author.SubString(1, aLength-3) + "...";
                                else           s += "...";
                            }
                            else  s += author.SubString(1, aLength);

                         }; break;

                      case _lt_title:
                      {
                            if (tDotsCuted)
                            {
                                if (tLength>3) s += title.SubString(1, tLength-3) + "...";
                                else           s += "...";
                            }
                            else  s += title.SubString(1, tLength);

                      };    break;

                      case _lt_author_length: case _lt_title_length: break;

                      case _lt_enum_zero: s += IntToStr(tIndex);   break;
                      case _lt_enum_one:  s += IntToStr(tIndex+1); break;
                      case _lt_text:      s += tFormat.SubString(tLiterals[i].Range.From(), tLiterals[i].Range.Count());
                  };
             };
     return s;
     };

     TTextStringList   TTextsListFormatter::FullTitlesList(const TTextString & tFormat, const TBool & tDotsCuted)
     {
     if (!_LogicalTextsContainer) throw EInvalidTextsContainer();

         TUInt authorLength;
         TUInt titleLength;
        _TLiteralsVector  literals = _UnformatTextInfoString(tFormat, &authorLength, &titleLength, tDotsCuted);

         TTextStringList list;

         for (TUInt i=0; i<_LogicalTextsContainer->Count(); i++)

             list.AddItem(_ComposeTextInfo(i, tFormat, literals, authorLength, titleLength, tDotsCuted));
     return list;
     };

     TTextStringList TTextsListFormatter::FullTitlesList(const TTextString & tFormat, const TBool & tDotsCuted, TLogicalTextsContainer * tLogicalTextsContainer)
     {
         _LogicalTextsContainer = tLogicalTextsContainer;
     return FullTitlesList(tFormat, tDotsCuted);
     };


TTextsInfoStrings  TTextsListFormatter::FullTitlesInfoStrings(const TTextString & tFormat, const TBool & tDotsCuted)
{
     if (!_LogicalTextsContainer) throw EInvalidTextsContainer();

         TUInt authorLength;
         TUInt titleLength;
        _TLiteralsVector  literals = _UnformatTextInfoString(tFormat, &authorLength, &titleLength, tDotsCuted);

         TTextsInfoStrings strings;

         for (TUInt i=0; i<_LogicalTextsContainer->Count(); i++)

             strings.AddItem(TTextInfoStringFormat((*_LogicalTextsContainer)[i].Alias(), _ComposeTextInfo(i, tFormat, literals, authorLength, titleLength, tDotsCuted)));
return strings;
};

TTextsInfoStrings  TTextsListFormatter::FullTitlesInfoStrings(const TTextString & tFormat, const TBool & tDotsCuted, TLogicalTextsContainer * tLogicalTextsContainer)
{
	_LogicalTextsContainer = tLogicalTextsContainer;
return FullTitlesInfoStrings(tFormat, tDotsCuted);
};

