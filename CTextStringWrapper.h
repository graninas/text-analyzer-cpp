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
#ifndef CTextStringWrapperH
#define CTextStringWrapperH
//---------------------------------------------------------------------------

#include "UTypes.h"
#include "UConstants.h"
#include "CTextDataProvider.h"
#include "CRangeItem.h"

class TTextStringWrapper : public TTextDataProvider
{
    private:

       TTextString _Source;


       virtual TTextString Alias()   const { return ""; };
    public:

       inline TUInt Begin()  const { return 1; };
       inline TUInt End()    const { return _Source.Length(); };
              TUInt Length() const { return _Source.Length(); };
              TTextString    Text()   const { return _Source; };
              TTextString *  Data()    { return &_Source; }

              TChar       *  c_str() const { return _Source.c_str(); }
       inline TUInt c_strBegin()  const { return 0; };
       inline TUInt c_strEnd()    const { return _Source.Length()-1; };


       TTextString SubString(const TUInt & tIndex, const TUInt & tCount)  const;
       TTextString SubString(const TUInt & tIndex, const TUInt & tCount);
       TTextString SubString(const TRangeItem & tRange);
       TTextString SubString(const TRangeItem & tRange) const;

       inline TTextStringWrapper & operator=(const TTextString & tString)
       {
           _Source = tString;
       return *this;
       };

       inline TChar operator[] (const TUInt & tIndex)
       {
           return _Source[tIndex];
       };

       TTextString EndSign() const;
       
    TTextStringWrapper(const TTextString & tSource) : _Source(tSource){};
    TTextStringWrapper() : _Source("") {};
};

#endif
 