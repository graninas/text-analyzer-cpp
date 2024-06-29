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
#ifndef BRuleInstanceH
#define BRuleInstanceH
//---------------------------------------------------------------------------

#include "BRule.h"
#include "BResoundingItem.h"

    class  TRuleInstance
    {
    private:
        TRule _Rule;

         TUInt     _StartIndex;
         TUInt     _Excit;

         TResoundingItem _ResoundingItem;

         TBool       _Finished;
         TBool       _Reseting;

         TBool       _TimeBackReseting;
         TTextString _TimeBackChar;
         TUInt       _TimeBackIndex;

         TFilteringResult _Result;

    public:

        TUInt            StartIndex()     const { return _StartIndex; }
        TUInt            Excit()          const { return _Excit; }

        TResoundingItem  ResoundingItem() const { return _ResoundingItem; }
        TBool            Finished()       const { return _Finished; }
        TBool            Excited()        const { return (_Excit >= _Rule.CriticalExcit()) ? true : false; };
        TRule *          Rule()                 { return &_Rule; };


        void CheckOnFinish(const TUInt & tIndex)
        {
            if (_Finished) return;

            if ((_Rule.Influence() != 0) && ((tIndex - _StartIndex+1) >= _Rule.Influence()))
            {
                _Finished = true;
                _Reseting = true;
            };
     };

     void EndProcedure()
     {
        _Finished = true;
        _Reseting = true;
     };

     void TimeBackProcedure(TTextString tChar, const TUInt & tIndex)
     {
         _TimeBackChar  = tChar;
         _TimeBackIndex = tIndex;
         _TimeBackReseting = true;
         _Finished = true;
     };

     void TurnTimeBack()
     {
         Reset();
        _TimeBackReseting = false;
        _StartIndex = _TimeBackIndex;

        _Result = _Rule.Accept(_TimeBackChar);

            if (_Result.Skip())    ;
            if (_Result.Excit())   _Excit++;
            if (_Result.LinkDot()) _ResoundingItem << _TimeBackIndex;
            if (_Result.Define())  _Rule.Define(_Result.FilterSubIndex(), TCharsSet(_TimeBackChar));
            if (_Result.Transit()) _Rule.Transit(_Result.TransitIndex());
            if (_Result.Reset())   _Reseting = true;
            if (_Result.EndProc())  EndProcedure();

     CheckOnFinish(_TimeBackIndex);
     };

     void   Reset()
     {
         _Rule.Reset();
         _ResoundingItem.Clear();
         _Finished = false;
         _Excit = 0;
         _Reseting = false;
         _StartIndex = 0;
     };

        void   Accept(TTextString tChar, const TUInt & tIndex)
        {
             if (_Reseting)  Reset();
             if (_TimeBackReseting) TurnTimeBack();

             if (!_StartIndex) _StartIndex = tIndex;

             _Result = _Rule.Accept(tChar);

                if (_Result.Skip())    ;
                if (_Result.Excit())   _Excit++;
                if (_Result.LinkDot()) _ResoundingItem << tIndex;
                if (_Result.Define())  _Rule.Define(_Result.FilterSubIndex(), TCharsSet(tChar));
                if (_Result.Transit()) _Rule.Transit(_Result.TransitIndex());
                if (_Result.Reset())   _Reseting = true;
                if (_Result.EndProc())  EndProcedure();
                if (_Result.TimeBackReset()) TimeBackProcedure(tChar, tIndex);

           CheckOnFinish(tIndex);
        };

        void AcceptForwardDifferential(const TTextString & tString, const TUInt & tIndex)
        {
             for (TSInt i=1; i<=tString.Length(); i++)   Accept(tString[i], tIndex+i-1);
        };

        void AcceptBackwardDifferential(const TTextString & tString, const TUInt & tIndex)
        {
             for (TSInt i=tString.Length(); i>=1; i--)   Accept(tString[i], tIndex+i-1);
        };


       TRuleInstance(const TRule & tRule)
       : _Rule(tRule), _Excit(0), _Finished(false), _StartIndex(0), _Reseting(false), _TimeBackReseting(false){};
    };




#endif
