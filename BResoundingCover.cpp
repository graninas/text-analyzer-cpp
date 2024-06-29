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
#include "BResoundingCover.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


    void TResoundingCover::_MergedCoverCalc()
    {
         if (_Range.Count() != _BaseCover.Count()) throw EInvalidValuesCover();

         if (_Range.To() == 1440)
         _Range = _Range;

    TValuesCover        mergedCover = _BaseCover;
    TUInt  i,j,k;
    TRuleResoundingItems        ruleResItems;
    TSFloat             value;
    TResoundingItem::TLinkDots  linkDots;
    TUInt               firstRangeIndex = _Range.From();

         for (i=0; i<_Batch.Count(); i++)
         {
             ruleResItems = _Batch[i];
             value = ruleResItems.Value();

             for (j=0; j<ruleResItems.Count(); j++)
             {
                if (!_Range.Intersects(ruleResItems[j].AffectedRange())) throw EInvalidResoundingBatch();

                  linkDots = ruleResItems[j].LinkDots();

                for (k=0; k<linkDots.size(); k++)
                    mergedCover.Merge(value, linkDots[k] - firstRangeIndex);
             };
         };

    _MergedCover = mergedCover;
    _IsCalculatedMergedCover = true;
    };


    void TResoundingCover::_ClearMergedCover()
    {
    _ClearSmoothedCover();
        _MergedCover.Clear();
        _IsCalculatedMergedCover = false;
    };

    void TResoundingCover::_ClearSmoothedCover()
    {
        _SmoothedCover.Clear();
        _IsCalculatedSmoothedCover = false;
    };


    TBool TResoundingCover::Intersects(const TRangeItem & tRange) { return _Range.Intersects(tRange); }

    TResoundingBatch & TResoundingCover::Batch()       { return _Batch; }
    TRangeItem         TResoundingCover::Range() const { return _Range; }
    void			   TResoundingCover::Range(const TRangeItem & tRange)
    {
		_Range = tRange;
    };

void TResoundingCover::Merge()
{
	if (!_IsCalculatedMergedCover) _MergedCoverCalc();
};

void TResoundingCover::Smooth()
{
	if (!_IsCalculatedSmoothedCover)
	{
		_SmoothedCover = MergedCover().Smoothed();
        _SmoothingRate = 1;
	}
};

void TResoundingCover::Smooth(const TUInt & tSmoothingRate)
{
	if (_SmoothingRate != tSmoothingRate)
	{
		_SmoothedCover = MergedCover().Smoothed(tSmoothingRate);
        _SmoothingRate = tSmoothingRate;
	}
};


    TValuesCover & TResoundingCover::BaseCover()  { return _BaseCover; }

    TValuesCover   TResoundingCover::MergedCover ()
    {
        Merge();
    return _MergedCover;
    };

    TValuesCover   TResoundingCover::MergedCover (const TRangeItem & tTextRange)
    {
        Merge();
    return _MergedCover.Part(tTextRange.From() - _Range.From(), tTextRange.To() - _Range.From());
    };


    TValuesCover   TResoundingCover::SmoothedCover ()
    {
		Smooth();
    return _SmoothedCover;
    };

    TValuesCover   TResoundingCover::SmoothedCover (const TRangeItem & tTextRange)
    {
		Smooth();
    return _SmoothedCover.Part(tTextRange.From() - _Range.From(), tTextRange.To() - _Range.From());
    };

    TValuesCover   TResoundingCover::SmoothedCover (const TUInt & tSmoothingRate)
    {
		Smooth(tSmoothingRate);
    return _SmoothedCover;
    };

    TValuesCover   TResoundingCover::SmoothedCover (const TRangeItem & tTextRange, const TUInt & tSmoothingRate)
    {
		Smooth(tSmoothingRate);
    return _SmoothedCover.Part(tTextRange.From() - _Range.From(), tTextRange.To() - _Range.From());
    };

    TResoundingCover & TResoundingCover::operator << (const TValuesCover & tBaseCover)
    {
       _BaseCover = tBaseCover;
       _ClearMergedCover();
        return *this;
    };

    TResoundingCover & TResoundingCover::operator << (const TResoundingBatch & tBatch)
    {
       _Batch = tBatch;
       _ClearMergedCover();
        return *this;
    };

    void TResoundingCover::Clear()
    {
        _Batch.Clear();
        _BaseCover.Clear();
        _ClearMergedCover();
        _SmoothingRate = 0;
    };


