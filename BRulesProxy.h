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
#ifndef BRulesProxyH
#define BRulesProxyH
//---------------------------------------------------------------------------


#include "BRule.h"
#include "CErrorSpecificators.h"

     class TRulesProxy  : TErrorSpecificators
     {
         public:

             typedef vector<TRule> TRules;

         private:

              TRules   _Rules;

         public:

            TUInt IsValidIndex(const TUInt & tIndex);

            TUInt Count() const;

            TRule & RuleByNumber(const TUInt & tRuleNumber)
            {
            for (TUInt i=0; i<_Rules.size(); i++)
                  if (_Rules[i].Number() == tRuleNumber) return _Rules[i];
            throw EOutOfRange();
            };

            inline TRule & operator[] (const TUInt & tIndex)
            {
                if (!IsValidIndex(tIndex)) throw EOutOfRange();
                return  _Rules[tIndex];
            };

            inline TRule & operator[] (const TTextString & tRuleName)
            {
                for (TUInt i=0; i<_Rules.size(); i++)
                  if (_Rules[i].Name() == tRuleName) return _Rules[i];
            throw EOutOfRange();
            };


            TRulesProxy & operator << (const TRule & tRule);
            TRulesProxy & operator << (const TRulesProxy & tRulesProxy);

            void Clear();

            TRulesProxy(){};
     };


#endif
 