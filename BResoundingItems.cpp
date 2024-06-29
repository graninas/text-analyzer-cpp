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
#include "BResoundingItems.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



          TBool TResoundingItems::IsValidIndex(const TUInt & tIndex) const
          {
              if (tIndex>=_Items.size()) return false;
          return true;
          };

          TResoundingItems & TResoundingItems::operator << (const TResoundingItem & tResoundingItem)
          {
              _Items.push_back(tResoundingItem);
          return *this;
          };

          TResoundingItem & TResoundingItems::operator[](const TUInt & tIndex)
          {
              if (!IsValidIndex(tIndex)) throw EOutOfRange();
          return _Items[tIndex];
          };

          TUInt TResoundingItems::Count() const
          {
              return _Items.size();
          };

          void  TResoundingItems::Clear()
          {
             _Items.clear();
          };

 