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
#include "BValuesCover.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


     TBool  TValuesCover::IsValidIndex(const TUInt & tIndex) const
     {
         if (tIndex >= _Values.size()) return false;
     return true;
     }

     TUInt          TValuesCover::Count() const { return _Values.size(); }
     TValuesCover::TValues  TValuesCover::Values()       { return _Values; }
     void           TValuesCover::Clear()       { _Values.clear(); }

     TSFloat  TValuesCover::Value(const TUInt & tIndex) const
     {
        if (!IsValidIndex(tIndex)) throw EOutOfRange();
     return _Values[tIndex];
     };

     TValuesCover TValuesCover::Part(const TUInt & tFromItem, const TUInt & tToItem)
     {
         if ((tFromItem>=_Values.size()) || (tToItem>_Values.size())) throw EOutOfRange();

     return TValuesCover(TValues(&_Values[tFromItem], &_Values[tToItem+1]));
     };

     TValuesCover & TValuesCover::operator << (const TSFloat & tValue)
     {
        _Values.push_back(tValue);
         return *this;
     };

     TValuesCover & TValuesCover::operator << (const TValues & tValues)
     {
        for (TUInt i=0; i<tValues.size(); i++)
        _Values.push_back(tValues[i]);
     return *this;
     };


     void TValuesCover::Merge(const TSFloat & tValue, const TUInt & tIndex)
     {
         if (!IsValidIndex(tIndex)) throw EInvalidIndex();
     _Values[tIndex] += tValue;
     }

     TValuesCover  TValuesCover::Smoothed() { return Smoothed(1); }


     TValuesCover  TValuesCover::Smoothed(const TUInt & tSmoothStrength)
     {
     if (!_Values.size())  throw EInvalidValuesCover();
     if (_Values.size() == 1) return TValuesCover(_Values);
     if (!tSmoothStrength)    return TValuesCover(_Values);

       TValues smoothed = _Values;
       TUInt i,j;

     if (smoothed.size() == 2)
     {
       for (j=0; j<tSmoothStrength; j++)
       {
         smoothed[0] = (smoothed[0]+smoothed[1])/2.0f;
         smoothed[1] = (smoothed[0]+smoothed[1])/2.0f;
       }
     return  TValuesCover(smoothed);
     };


       for (j=0; j<tSmoothStrength; j++)
       {
          smoothed[0] = (smoothed[0]+smoothed[1])/2.0f;
              for (i=1; i<smoothed.size()-1; i++)
           smoothed[i] = (smoothed[i-1]+smoothed[i]+smoothed[i+1])/3.0f;
          smoothed[smoothed.size()-1] = (smoothed[smoothed.size()-2]+smoothed[smoothed.size()-1])/2.0f;
       };

     return TValuesCover(smoothed);
     };


