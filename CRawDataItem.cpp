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
#include "CRawDataItem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "CCRC32Calculator.h"
#include "stdlib.h"


void TRawDataItem::_SetVirtual(TBool tIsVirtual)
{
    _IsVirtual = tIsVirtual;
};

void TRawDataItem::_SetConnectionString(TTextString tConnectionString)
{
    _ConnectionString = tConnectionString;
};

void TRawDataItem::_Clear()
{
    _RawData = "";
    _ConnectionString = "";
    _Alias = "";
    _Loader = &_DefaultLoader;
};

void TRawDataItem::_SetLoader(TRawDataLoader *tPLoader)
{
    _Loader = tPLoader;
};

void TRawDataItem::_SetAlias(TTextString tAlias)
{
    _Alias = tAlias;
};

TUChar TRawDataItem::_ModulateChar(TUChar tCh, TUChar tLeft, TUChar tRight)
{
    TSInt dist = tRight - tLeft;
    TSFloat percent = (TSFloat(tCh))/256.0f;
    TSInt res = TSInt(TSFloat(dist)*percent) + tLeft;
return res;
};

TTextString TRawDataItem::_GenerateAlias()
{
if (IsVirtual()) return "";

  TTextString alias = "";
  TULongInt crc32 = CRC();

    TUChar     nbyte;
    TUShortInt nword;

       nword = LOWORD(crc32);
          nbyte = LOBYTE(nword);
              alias += char(_ModulateChar(nbyte, 'A', 'Z'));
          nbyte = HIBYTE(nword);
              alias += char(_ModulateChar(nbyte, 'a', 'z'));

       nword = HIWORD(crc32);
          nbyte = LOBYTE(nword);
              alias += char(_ModulateChar(nbyte, 'A', 'Z'));
          nbyte = HIBYTE(nword);
              alias += char(_ModulateChar(nbyte, 'a', 'z'));

   /*TUChar m_char;

      randomize();
         alias += char(random(25) + 65);
         alias += char(random(25) + 97);
         alias += char(random(25) + 65);
         alias += char(random(25) + 97);    */

return  alias + IntToStr(crc32);
};

TTextString * TRawDataItem::Data() 
{
   if (IsVirtual()) throw ETextIsVirtual();

    return &_RawData;
};

TTextString TRawDataItem::Text() const
{
   if (IsVirtual()) throw ETextIsVirtual();

    return _RawData;
};

TUInt TRawDataItem::Length() const
{
   if (IsVirtual()) throw ETextIsVirtual();

   return _RawData.Length();
};

TUInt TRawDataItem::CRC()
{
   if (IsVirtual()) throw ETextIsVirtual();

  TCRC32Calculator CRC32Calc;

    return CRC32Calc.CRC32(_RawData.c_str(), Length());
};

TTextString TRawDataItem::Alias() const
{
    return _Alias;
};

TTextString TRawDataItem::SubString(const TUInt & tIndex, const TUInt & tCount)  const
{
	return _RawData.SubString(tIndex, tCount);
};

TBool TRawDataItem::IsLinked()
{
   if (!_Loader->IsLinked(&_ConnectionString))   return false;

return true;
};

TBool TRawDataItem::IsVirtual() const
{
   return _IsVirtual;
};

TBool TRawDataItem::Unvirtualize()
{
   if (_Loader->Load(&_ConnectionString, &_RawData))
   {
       _SetVirtual(false);
       _SetAlias(_GenerateAlias());
       return true;
   }

_SetVirtual(true);
return false;
};

TRawDataLoader * TRawDataItem::Loader()
{
   return _Loader;
};

void TRawDataItem::Loader(TRawDataLoader *tPLoader)
{
    if (IsVirtual()) _SetLoader(tPLoader);
    else
    {
       _SetLoader(tPLoader);
       Unvirtualize();
    }
}

TTextString TRawDataItem::ConnectionString()
{
   return _ConnectionString;
};

void TRawDataItem::ConnectionString(TTextString tConnectionString)
{
    _SetConnectionString(tConnectionString);
if (!IsVirtual())  Unvirtualize();
};

TRawDataItem::TRawDataItem()
{
};

TRawDataItem::TRawDataItem(TRawDataLoader *tPLoader, TTextString tConnectionString) :
 _Loader(tPLoader), _IsVirtual(true), _RawData(""), _Alias("")
{
   //_Clear();
   _SetConnectionString(tConnectionString); //Ќе статический член и не может быть инициализирован в заголовке конструктора.
   //_SetVirtual(true);
   //_SetLoader(tPLoader);
};

TRawDataItem::~TRawDataItem()
{
   _Clear();
};

////////////////////////////////////////////////////////////////////////////////


TMPRawDataItem::SpecificatorType TMPRawDataItem::Specificator() const
{
	return _Item->Alias();
};

TRawDataItem * TMPRawDataItem::operator->() const
{
	return _Item;
}

TRawDataItem * TMPRawDataItem::RawDataItem()       const
{
	return _Item;
}

void  TMPRawDataItem::Delete()
{
    if (_Item) delete _Item;
}

TMPRawDataItem & TMPRawDataItem::operator=(const TMPRawDataItem & tMP)
{
    if (&tMP != this)
    {
        delete _Item;
        _Item = new TRawDataItem(*(tMP._Item));
    }
return *this;
}

