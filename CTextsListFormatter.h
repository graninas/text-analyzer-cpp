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
#ifndef CTextsListFormatterH
#define CTextsListFormatterH
//---------------------------------------------------------------------------

#include "CTextStringList.h"
#include "CLogicalTextsContainer.h"
#include "CRangeItem.h"

#include "CTextsInfoStrings.h"

	class TTextsListFormatter
    {
    public:

            enum   _TLiteralTypes {_lt_author, _lt_title, _lt_author_length, _lt_title_length, _lt_enum_zero, _lt_enum_one, _lt_text};
            class  _TLiteral
            {
              public:
                  TRangeItem     Range;
                 _TLiteralTypes  LiteralType;

                  friend TBool operator < (const _TLiteral & tItem1, const _TLiteral & tItem2)
                  {
                      return  tItem1.Range < tItem2.Range;
                  };

                 _TLiteral(const TRangeItem & tRange, const _TLiteralTypes & tLiteralType)
                  : Range(tRange), LiteralType(tLiteralType){};
            };

            typedef vector<_TLiteral> _TLiteralsVector;

            class EInvalidTextsContainer{};
            class EInvalidFormatString{};

    private:

            TLogicalTextsContainer * _LogicalTextsContainer;

           _TLiteralsVector _UnformatTextInfoString(const TTextString & tFormat, TUInt * tAuthorLength, TUInt * tTitleLength, const TBool & tDotsCuted);
            TTextString     _ComposeTextInfo(const TUInt & tIndex, const TTextString & tFormat, const _TLiteralsVector & tLiterals, const TUInt & tAuthorLength, const TUInt & tTitleLength, const TBool & tDotsCuted);

    public:

            TTextStringList    FullTitlesList(const TTextString & tFormat, const TBool & tDotsCuted);
            TTextStringList    FullTitlesList(const TTextString & tFormat, const TBool & tDotsCuted, TLogicalTextsContainer * tLogicalTextsContainer);

            TTextsInfoStrings  FullTitlesInfoStrings(const TTextString & tFormat, const TBool & tDotsCuted);
            TTextsInfoStrings  FullTitlesInfoStrings(const TTextString & tFormat, const TBool & tDotsCuted, TLogicalTextsContainer * tLogicalTextsContainer);

    TTextsListFormatter(TLogicalTextsContainer * tLogicalTextsContainer)
    	: _LogicalTextsContainer(tLogicalTextsContainer){}

    TTextsListFormatter()
        : _LogicalTextsContainer(NULL){}
    };

#endif
 