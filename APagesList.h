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
#ifndef APagesListH
#define APagesListH
//---------------------------------------------------------------------------

#include "APage.h"
#include "CTextDataProvider.h"

   class TPagesList : public TErrorSpecificators
   {
       public:

           typedef vector<ns_Page::TPage> TPages;

       private:

          TPages  _Pages;

       public:

           TPages & Pages() { return _Pages; }

           TBool IsValidIndex(const TUInt & tIndex) const
           {
               if (tIndex >= _Pages.size()) return false;
           return true;
           }

           ns_Page::TPage & operator[] (const TUInt & tIndex)
           {
               if (!IsValidIndex(tIndex)) throw EOutOfRange();
           return _Pages[tIndex];
           };

           TPagesList & operator << (const ns_Page::TPage & tPage)
           {
              _Pages.push_back(tPage);
           return *this;
           };

           TUInt Count() const { return _Pages.size(); }
           void  Clear()       { _Pages.clear(); };

           ns_Page::TPage & First()
           {
              if (!_Pages.size()) throw ENoChildItems();
           return _Pages[0];
           };

           ns_Page::TPage & Last()
           {
              if (!_Pages.size()) throw ENoChildItems();
           return _Pages[_Pages.size()-1];
           };

           TPagesList(){};
          ~TPagesList(){ Clear(); };
   };



#endif
 