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
#include "ACoveredPage.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


    ns_Page::TPage * TCoveredPage::Page()
    {
        return &_Page;
    };

    TValuesCover * TCoveredPage::Cover()
    {
        return &_Cover;
    };

    TSFloat  TCoveredPage::Value(const TUInt & tLinkDot)
    {
        return _Cover[tLinkDot - _Range.From()];
    };

    TSFloat  TCoveredPage::MinValue()
    {
    if (!_CoverLoaded) return 0.0f;

    TSFloat min;

       min = _Cover[0];

        for (TUInt i=1; i<_Cover.Count(); i++)
          if (_Cover[i] < min) min = _Cover[i];
    return min;
    };

    TSFloat  TCoveredPage::MaxValue()
    {
    if (!_CoverLoaded) return 0.0f;

    TSFloat max = _Cover[0];
        for (TUInt i=1; i<_Cover.Count(); i++)
          if (_Cover[i] > max) max = _Cover[i];
    return max;
    };

    TBool TCoveredPage::IsReady() const
    {
        if (!(_PageLoaded && _CoverLoaded)) return false;
        if (_Range.Count() != _Cover.Count()) throw EInvalidCoveredPage();
        
    return true;
    };

    TCoveredPage & TCoveredPage::operator << (const ns_Page::TPage & tPage)
    {
        _Page = tPage;
        _PageLoaded = true;

        _Range = _Page.Range();
        
    return *this;
    };

    TCoveredPage & TCoveredPage::operator << (const TValuesCover & tCover)
    {
        _Cover = tCover;
        _CoverLoaded = true;
    return *this;
    };


    void TCoveredPage::Clear()
    {
    _Page.Clear();
    _Cover.Clear();
        _PageLoaded = false;
        _CoverLoaded = false;
    };
