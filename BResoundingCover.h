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
#ifndef BResoundingCoverH
#define BResoundingCoverH
//---------------------------------------------------------------------------


#include "BValuesCover.h"
#include "BResoundingBatch.h"
#include "CRangeItem.h"
#include "CErrorSpecificators.h"

    class TResoundingCover : public TErrorSpecificators
    {
         private:

            TResoundingBatch    _Batch;
            TValuesCover        _BaseCover;
            TRangeItem          _Range;         //Участок текста, для которого построено полотно благозвучия.

            TValuesCover   _MergedCover;
            TValuesCover   _SmoothedCover;

            TBool          _IsCalculatedMergedCover;
            TBool          _IsCalculatedSmoothedCover;

            void _MergedCoverCalc();
            void _ClearMergedCover();
            void _ClearSmoothedCover();

            TUInt   _SmoothingRate;

         public:

            TBool Intersects(const TRangeItem & tRange);

            TResoundingBatch & Batch();
            TRangeItem         Range() const;
            void			   Range(const TRangeItem & tRange);

            void		Merge();
            void		Smooth();
            void		Smooth(const TUInt & tSmoothingRate);


            TValuesCover & BaseCover();
            TValuesCover   MergedCover ();
            TValuesCover   MergedCover (const TRangeItem & tTextRange);
            TValuesCover   SmoothedCover ();
            TValuesCover   SmoothedCover (const TRangeItem & tTextRange);
            TValuesCover   SmoothedCover (const TUInt & tSmoothingRate);
            TValuesCover   SmoothedCover (const TRangeItem & tTextRange, const TUInt & tSmoothingRate);

            TResoundingCover & operator << (const TValuesCover & tBaseCover);
            TResoundingCover & operator << (const TResoundingBatch & tBatch);

            void Clear();


            TResoundingCover()
            	:	_SmoothingRate(0), _IsCalculatedMergedCover(false), _IsCalculatedSmoothedCover(false)
                {};

            TResoundingCover(const TRangeItem & tRange)
            	: _Range(tRange), _SmoothingRate(0), _IsCalculatedMergedCover(false), _IsCalculatedSmoothedCover(false)
                {};

           ~TResoundingCover(){ Clear(); };
    };



#endif
