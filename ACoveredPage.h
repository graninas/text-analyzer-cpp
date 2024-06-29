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
#ifndef ACoveredPageH
#define ACoveredPageH
//---------------------------------------------------------------------------

#include "APage.h"
#include "BValuesCover.h"
#include "CErrorSpecificators.h"


    class TCoveredPage : public TErrorSpecificators
    {
       private:

           ns_Page::TPage  _Page;
           TValuesCover    _Cover;

            TBool _PageLoaded;
            TBool _CoverLoaded;

            TRangeItem _Range;

       public:

           TRangeItem  Range() const { return _Range; };

           TBool IsReady() const;

           ns_Page::TPage * Page();
           TValuesCover   * Cover();

           TSFloat  Value(const TUInt & tLinkDot);
           TSFloat  MinValue() ;
           TSFloat  MaxValue() ;

           TCoveredPage & operator << (const ns_Page::TPage & tPage);
           TCoveredPage & operator << (const TValuesCover & tCover);

           void Clear();

           TCoveredPage() : _PageLoaded(false), _CoverLoaded(false), _Range(0,0){};
    };





#endif
