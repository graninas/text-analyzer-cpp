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
#include "BRulesContainer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)



             TBool TRulesContainer::_Find(const TRule & tRule, TUInt * tIndex)
             {
                 for (TUInt i=0; i<_Items.size(); i++)
                     if (tRule == _Items[i])
                     {
                         *tIndex = i;
                         return true;
                     }
             return false;
             };

             TBool TRulesContainer::_Find(const TUInt & tNumber, TUInt * tIndex)
             {
                 for (TUInt i=0; i<_Items.size(); i++)
                     if (tNumber == _Items[i].Number())
                     {
                         *tIndex = i;
                         return true;
                     }
             return false;
             };


            TBool  TRulesContainer::GetRule(const TUInt & tNumber, TRule * tRule)
            {
                TUInt index;
                if (!_Find(tNumber, &index)) return false;

            *tRule = _Items[index];
            return true;
            };

            TRulesContainer & TRulesContainer::operator << (const TRule & tRule)
            {
            TUInt index;
                if (! _Find(tRule, &index)) _Items.push_back(tRule);
            return *this;
            };


