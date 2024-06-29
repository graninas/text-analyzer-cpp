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
#ifndef CTextInfoStringFormatH
#define CTextInfoStringFormatH
//---------------------------------------------------------------------------


#include "UStructs.h"

	class TTextInfoStringFormat
    {
    public:

    	typedef TTextString SpecificatorType;

     	SpecificatorType    Specificator() { return _Alias; }

    private:

    	TTextString _Alias;
        TTextString _Format;

    public:

    	TTextString Alias() const { return _Alias; }
        TTextString Format() const { return _Format; }

        TTextInfoStringFormat(const TTextString & tAlias, const TTextString & tFormat)
        : _Alias(tAlias), _Format(tFormat)
        {}
    };

#endif
 