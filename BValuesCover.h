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
#ifndef BValuesCoverH
#define BValuesCoverH
//---------------------------------------------------------------------------

#include "UStructs.h"
#include "CErrorSpecificators.h"


     class TValuesCover : public TErrorSpecificators
     {
          public:

               typedef vector<TSFloat> TValues;

          private:

               TValues     _Values;

          public:
             TBool  IsValidIndex(const TUInt & tIndex) const;

             TUInt       Count() const;
             TValues     Values();
             void        Clear() ;

             TSFloat     Value(const TUInt & tIndex) const;

             TValuesCover Part(const TUInt & tFromItem, const TUInt & tToItem);

             TValuesCover & operator << (const TSFloat & tValue);
             TValuesCover & operator << (const TValues & tValues);

             inline TSFloat & operator[] (const TUInt & tIndex)
             {
                 if (!IsValidIndex(tIndex)) throw EOutOfRange();
             return _Values[tIndex];
             };

             void Merge(const TSFloat & tValue, const TUInt & tIndex);

             TValuesCover  Smoothed();
             TValuesCover  Smoothed(const TUInt & tSmoothStrength);

             TValuesCover() {};
             TValuesCover(const TValues & tValues) : _Values(tValues) {};
            ~TValuesCover(){ Clear(); };
     };







#endif
 