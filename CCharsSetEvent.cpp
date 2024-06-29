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
#include "CCharsSetEvent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



TTextString TCharsSetEvent::Name() const
{
	return _Item.Name();
};

TCharsSetEvent::TNamedCharsSetItem * TCharsSetEvent::Item()
{
	return &_Item;
};

TUInt TCharsSetEvent::Iterator()   const
{
	return _Iterator;
};

TCharsSetEvent & TCharsSetEvent::operator<< (const TUInt & tIterator)
{
   _Iterator = tIterator;
   return *this;
};

TBool TCharsSetEvent::operator == (const TCharsSetEvent & tEvent)
{
	return (_Item == tEvent._Item);
};

TBool TCharsSetEvent::operator == (const TNamedCharsSetItem & tNamedSetItem)
{
	return (_Item == tNamedSetItem);
};


