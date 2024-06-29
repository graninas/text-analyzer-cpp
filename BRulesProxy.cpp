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
#include "BRulesProxy.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


            TUInt TRulesProxy::IsValidIndex(const TUInt & tIndex)
            {
                if (tIndex >= _Rules.size()) return false;
            return true;
            };

            TUInt TRulesProxy::Count() const { return _Rules.size(); }

            TRulesProxy & TRulesProxy::operator << (const TRule & tRule)
            {
               _Rules.push_back(tRule);
            return *this;
            };

            TRulesProxy & TRulesProxy::operator << (const TRulesProxy & tRulesProxy)
            {
               for (TUInt i=0; i<tRulesProxy._Rules.size(); i++)
                   _Rules.push_back(tRulesProxy._Rules[i]);
            return *this;
            };

            void TRulesProxy::Clear(){ _Rules.clear(); }


