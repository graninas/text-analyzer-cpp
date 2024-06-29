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
#ifndef CRawDataContainerH
#define CRawDataContainerH
//---------------------------------------------------------------------------
#include "CRawDataItem.h"
#include "CDataContainer.h"


   class TRawDataContainer : public TDataContainer<TRawDataItem>
   {
      public:

          void UnvirtualizeAll()
          {
              for (TUInt i=0; i<_Items.size(); i++)
                 _Items[i].Unvirtualize();
          };

          TBool Unvirtualize(const TUInt & tIndex)
          {
              if (IsValidIndex(tIndex))	return _Items[tIndex].Unvirtualize();
          return false;
          };

          TBool Unvirtualize(const TRawDataItem::SpecificatorType & tSpecificator)
          {
          TUInt Index;
              if  (GetIndex(tSpecificator, &Index)) return _Items[Index].Unvirtualize();
          return false;
          };

       TRawDataContainer() : TDataContainer<TRawDataItem>() {};
   };



/*
   Данный код протестирован. Работает.

----------------------------------------------------------------------------

TRawDataContainer RDC;


RDC.Clear();
      TVCLFileDataLoader FDL;
      AnsiString FileName;
      AnsiString Buffer;

if (OpenDialog1->Execute()) FileName = OpenDialog1->FileName;

   TRawDataItem RDI(&FDL, FileName);

   TUInt Index = RDC.AddItem(&RDI);

   RDC.UnvirtualizeAll();

   Buffer = (*RDC.Data(Index));
     Memo2->Text = Buffer;

   Edit2->Text = RDC.Item(Index)->Alias();

----------------------------------------------------------------------------
*/


#endif
