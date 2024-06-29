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
#ifndef CCharsSetH
#define CCharsSetH
//---------------------------------------------------------------------------

#include "CCharsSetModificator.h"

   class TCharsSet
   {
       public:

          typedef TTextString TElementType;

       protected:
          TTextString _CharSet;

          TTextString  _DoUnique(TTextString tString);
          void         _AddSet(TTextString tString);
          void         _RemoveSubset(TTextString tString);
          TTextString  _ComposeRange(TChar tFromChar, TChar tToChar);

       public:

          TBool IsSubset(const TTextString & tElement) const;
          TBool IsSubset(const TCharsSet & tSet)   const;
          TTextString EmptySubset();

          TTextString   Elements() const;
          TUInt         Length()   const;
          void          Clear();

          TBool operator == (const TCharsSet & tSet);

          void  LoadRange(const TUChar & tFromChar, const TUChar & tToChar);


			TCharsSet & operator << (const TCharsSet & tCharSet);
			TCharsSet & operator << (const TTextString & tString);
			TCharsSet & operator >> (const TCharsSet & tCharSet);
			TCharsSet & operator >> (const TTextString & tString);
			TCharsSet & operator << (const TCharsSetModificator & tModificator);
			TCharsSet & operator >> (const TCharsSetModificator & tModificator);
            TCharsSet & operator << (const TCharsSetMans & tManipulator);

	friend TBool operator == (const TCharsSet & tSet1, const TCharsSet & tSet2)
	{
    	return (tSet1._CharSet == tSet2._CharSet) ? true : false;
	};



          TCharsSet(const TTextString & tSet) : _CharSet(_DoUnique(tSet)){};
          TCharsSet(const TUChar & tFromChar, const TUChar & tToChar) : _CharSet(_ComposeRange(tFromChar, tToChar)){};
          TCharsSet() : _CharSet(""){};
   };

#endif
