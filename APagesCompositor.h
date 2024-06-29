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
#ifndef APagesCompositorH
#define APagesCompositorH
//---------------------------------------------------------------------------

#include "APagesList.h"

     class TPagesCompositor
     {
         private:

             TUInt  _RowLength;
             TUInt  _RowsCount;

             TUInt  _Iterator;
             TUInt  _Length;

         public:

           TPagesList Compose(const TUInt & tTextLength)
           {
               ns_Page::TPage      page;
               TPagesList newList;
               TRangeItem range;

               _Length = tTextLength;
               
                   TUInt totalRows = tTextLength / _RowLength;

               TUInt row = 1;

               for (_Iterator=0; _Iterator<totalRows; _Iterator++)
               {
                   range.From(_Iterator*_RowLength + 1);
                   range.To(_Iterator*_RowLength + _RowLength);

                   page << range;

                   if (page.Count() == _RowsCount)
                   {
                       newList << page;
                       page.Clear();
                   };
               };

           if ((totalRows * _RowLength) == tTextLength) return newList;

               range.From(totalRows * _RowLength + 1);
               range.To(tTextLength);

               page << range;
               newList << page;
           return  newList;
           };


           void GetProcessInfo(TUInt * tBegin, TUInt * tEnd, TUInt * tIterator)
           {
                *tBegin = 1;
                *tEnd   = _Length;
                *tIterator = _Iterator;
           };

         TPagesCompositor(const TUInt & tRowLength, const TUInt & tRowsCount)
         : _RowLength(tRowLength), _RowsCount(tRowsCount){};
     };

#endif
 