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
#ifndef CLogicalTextItemH
#define CLogicalTextItemH
//---------------------------------------------------------------------------

#include "CRawDataItem.h"

class TMPLogicalTextItem;

   class TLogicalTextItem  : public TTextDataProvider
   {
   friend class TMPLogicalTextItem;
      public:

          class EInvalidRawDataPointer {};

          typedef TTextString SpecificatorType;
             SpecificatorType Specificator() const { return _Alias; };

      private:

         //TRawDataItem   * _RawData;
         TMPRawDataItem  _RawData;

         TTextString   _Alias;
         TTextString   _Author;
         TTextString   _Title;
         TULongInt     _CRC;

         TBool _IsValidRawDataPointer()
         {
//             if (_RawData == NULL) return false;

             try
             {
                TTextString RawDataAlias = _RawData->Alias();
                if (RawDataAlias != _Alias) return false;
             }
             catch(...)
             {
                 return false;
             };
         return true;
         };


         TLogicalTextItem(){};

      public:

         TTextString   Alias() const { return _Alias; };
         TULongInt     CRC()  const  { return _CRC;   };

         TTextString * Data()  { return _RawData->Data();   };
         TTextString   Text()  const { return _RawData->Text();   };
         TUInt         Length() const { return _RawData->Length(); };

         TTextString   SubString(const TUInt & tIndex, const TUInt & tCount)  const { return _RawData->SubString(tIndex, tCount); };

         TTextString   Author() const { return _Author; };
         void          Author(const TTextString & tAuthor) { _Author = tAuthor; };
           TTextString Title() const { return _Title; };
           void        Title(const TTextString & tTitle)   { _Title = tTitle; };

         TLogicalTextItem(const TTextString & tAlias, const TTextString & tAuthor, const TTextString & tTitle, const TULongInt & tCRC, TRawDataItem * tRawData)
           : _RawData(tRawData), _Alias(tAlias), _Author(tAuthor), _Title(tTitle), _CRC(tCRC)
           {
               if (!_IsValidRawDataPointer()) throw EInvalidRawDataPointer();
           };
   };


////////////////////////////////////////////////////////////////////////////////


    class TMPLogicalTextItem
    {
        public:

            typedef TTextString SpecificatorType;
            SpecificatorType Specificator() const { return _Item->Alias(); }

        private:

            TUInt _InstancesCounter;

            TLogicalTextItem  * _Item;

            void _AddInstance()    { _InstancesCounter++; };
            void _DeleteInstance() { _InstancesCounter--; }

        public:

           TLogicalTextItem * operator->() const { return _Item; }
           TLogicalTextItem * LogicalTextItem()       const { return _Item; }


         void  Delete()
         {
             if (_Item) delete _Item;
         }

         TMPLogicalTextItem & operator=(const TMPLogicalTextItem & tMP)
         {
             if (&tMP != this)
             {
                 delete _Item;
                 _Item = new TLogicalTextItem(*(tMP._Item));
             }
         return *this;
         }


         TMPLogicalTextItem(TLogicalTextItem * tItem) : _Item(tItem), _InstancesCounter(0)
         {
            _AddInstance();
         };

         TMPLogicalTextItem(const TMPLogicalTextItem & tItem) : _Item(new TLogicalTextItem(*(tItem._Item))), _InstancesCounter(0)
         {
            _AddInstance();
         };

         TMPLogicalTextItem () : _Item(new TLogicalTextItem()), _InstancesCounter(0)
         {
            _AddInstance();
         };

          ~TMPLogicalTextItem ()
           {
              _DeleteInstance();
           };
    };




#endif
