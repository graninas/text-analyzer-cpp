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
#ifndef BRuleH
#define BRuleH
//---------------------------------------------------------------------------

#include "BFilteringScheme.h"

enum TRuleDifferenceAttribute {rda_Differential, rda_NotDifferential};
enum TRuleDirection           {rd_Forward, rd_Backward, rd_Both};

     class TRule
     {
         private:

            TTextString      _Name;
            TSFloat          _Value;
            TTextString      _Description;
            TUInt            _Number;

            TRuleDifferenceAttribute    _DifferenceAttribute;
            TRuleDirection              _Direction;

            TFilteringScheme _Scheme;

             TUInt     _Influence;
             TUInt     _CriticalExcit;

         public:

                TTextString Name()          const { return _Name; }
                TTextString Description()   const { return _Description; }
                TSFloat     Value()         const { return _Value; }
                TUInt       Number()        const { return _Number; }
                TBool       Differential()  const { return _DifferenceAttribute == rda_Differential; }
                TRuleDirection Direction()  const { return _Direction; }

                TFilteringScheme & Scheme() { return _Scheme; }

                TUInt        Influence()     const { return _Influence; }
                TUInt        CriticalExcit() const { return _CriticalExcit; }

                TFilteringResult  Accept (TTextString tChar) { return _Scheme.Accept(TCharsSet(tChar)); };
                void              Define (const TUInt & tSubIndex, const TCharsSet & tCharsSet) { _Scheme.Define(tSubIndex, tCharsSet); };
                void              Transit(const TUInt & tCascade) { _Scheme.Transit(tCascade); };
                void              Reset  () { _Scheme.Reset(); };


         friend TBool operator == (const TRule & tRule1, const TRule & tRule2)
         {
         return  ((tRule1._Number       == tRule2._Number) &&
                 (tRule1._Name          == tRule2._Name)   &&
                 (tRule1._Value         == tRule2._Value) &&
                 (tRule1._Direction     == tRule2._Direction) &&
                 (tRule1._Influence     == tRule2._Influence) &&
                 (tRule1._CriticalExcit == tRule2._CriticalExcit));
         };


            TRule(const TTextString & tName, const TSFloat & tValue, const TUInt & tNumber,
                  const TRuleDifferenceAttribute & tDifferenceAttribute, const TRuleDirection & tDirection,
                  const TFilteringScheme & tScheme, const TUInt & tCriticalExcit, const TUInt & tInfluence,
                  const TTextString & tDescription)
             : _Name(tName), _Value(tValue), _Scheme(tScheme), _CriticalExcit(tCriticalExcit), _Influence(tInfluence),
               _Description(tDescription), _Number(tNumber), _DifferenceAttribute(tDifferenceAttribute), _Direction(tDirection){};

            ~TRule(){};
     };




#endif
