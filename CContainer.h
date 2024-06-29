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
#ifndef CContainerH
#define CContainerH
//---------------------------------------------------------------------------


#include "UStructs.h"
#include "CErrorSpecificators.h"

template <class ItemType> class TContainer : public TErrorSpecificators
{
public:
   typedef vector<ItemType> TItems;

protected:

   TItems _Items;

public:

   TBool IsValidIndex(const TUInt & tIndex) const
   {
       if (tIndex >= _Items.size()) return false;
       else return true;
   };


    ItemType & Item(const TUInt & tIndex)
    {
      if (!IsValidIndex(tIndex)) throw EInvalidIndex();

    return _Items[tIndex];
    };

    ItemType * PItem(const TUInt & tIndex)
    {
      if (!IsValidIndex(tIndex)) throw EInvalidIndex();

    return &_Items[tIndex];
    };


    TItems & Items() { return _Items; };


    inline ItemType & operator [] (const TUInt & tIndex)
    {
        if (!IsValidIndex(tIndex)) throw EOutOfRange();

        return _Items[tIndex];
    };


      TUInt AddItem(const ItemType & tItem)
      {
         _Items.push_back(tItem);
         return _Items.size()-1;
      };

      TUInt AddItem(const ItemType * tItem)
      {
         _Items.push_back(*tItem);
         return _Items.size()-1;
      };


      TBool DeleteItem(const TUInt & tIndex)
      {
      if (!IsValidIndex(tIndex)) return false;

         _Items.erase(&_Items[tIndex]);
      return true;
      };

      TUInt Count() const
      {
         return _Items.size();
      };

    void Clear()
    {
       _Items.clear();
    };


     TContainer(){};
    ~TContainer(){ Clear(); };
};



#endif
 