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
#ifndef CRawDataItemH
#define CRawDataItemH
//---------------------------------------------------------------------------

#include "UTypes.h"
#include "CRawDataLoader.h"
#include "CTextDataProvider.h"
#include "CErrorSpecificators.h"

class TMPRawDataItem;

class TRawDataItem : public TTextDataProvider, public TErrorSpecificators
{
friend class TMPRawDataItem;
public:

     class ENotLinked {};

          typedef TTextString SpecificatorType;
             SpecificatorType Specificator() const { return _Alias; };

private:
TRawDataLoader _DefaultLoader;

       TRawDataLoader * _Loader;

       TTextString   _ConnectionString;

       TTextString   _RawData;
       TTextString   _Alias;
       TBool         _IsVirtual;

       void _SetVirtual(TBool tIsVirtual);
       void _SetConnectionString(TTextString tConnectionString);
       void _SetLoader(TRawDataLoader *tPLoader);
       void _SetAlias(TTextString tAlias);

       TUChar      _ModulateChar(TUChar tCh, TUChar tLeft, TUChar tRight);
       TTextString _GenerateAlias();

       void _Clear();

public:

       TTextString * Data();
       TTextString   Text() const;
       TUInt         Length() const;
       TUInt         CRC();
       TTextString   Alias()  const;

       TTextString   SubString(const TUInt & tIndex, const TUInt & tCount)  const;

       TBool IsLinked();
       TBool IsVirtual() const;
       TBool Unvirtualize() ;
       TRawDataLoader * Loader();
       void             Loader(TRawDataLoader *tPLoader);
       TTextString      ConnectionString();
       void             ConnectionString(TTextString tConnectionString);

       TRawDataItem();
       TRawDataItem(TRawDataLoader *tPLoader, TTextString tConnectionString);
       ~TRawDataItem();
};



   class TMPRawDataItem
    {
        public:

            typedef TTextString SpecificatorType;
            SpecificatorType Specificator() const;

        private:

            TUInt _InstancesCounter;

            TRawDataItem  * _Item;

            void _AddInstance()    { _InstancesCounter++; };
            void _DeleteInstance() { _InstancesCounter--; }

        public:

           TRawDataItem * operator->() const;
           TRawDataItem * RawDataItem() const;


         void  Delete();

         TMPRawDataItem & operator=(const TMPRawDataItem & tMP);


         TMPRawDataItem(const TMPRawDataItem & tItem) : _Item(new TRawDataItem(*(tItem._Item))), _InstancesCounter(0)
         {
            _AddInstance();
         };

         TMPRawDataItem(TRawDataItem * tItem) : _Item(tItem), _InstancesCounter(0)
         {
            _AddInstance();
         };

         TMPRawDataItem () : _Item(new TRawDataItem()), _InstancesCounter(0)
         {
            _AddInstance();
         };

          ~TMPRawDataItem ()
           {
              _DeleteInstance();
           };
    };











/*

    Этот код протестирован. Работает.

    Сомнения в генерации Alias. Возникают отрицательные значения crc.

//------------------------------------------------------------------------

#include "CRawDataItem.h"
#include "CVCLFileDataLoader.h"

TVCLFileDataLoader FDL;
      AnsiString FileName;

if (OpenDialog1->Execute()) FileName = OpenDialog1->FileName;

   TRawDataItem RDI(&FDL, FileName);
   RDI.Unvirtualize();
   Edit2->Text = RDI.Alias();

*/


#endif
