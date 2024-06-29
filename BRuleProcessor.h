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
#ifndef BRuleProcessorH
#define BRuleProcessorH
//---------------------------------------------------------------------------

#include "BRuleInstance.h"
#include "CErrorSpecificators.h"
#include "BResoundingBatch.h"
#include "BRulesProxy.h"

#include "UReportFunctionsTypes.h"

     template <class SourceType> class TRuleProcessor : public TErrorSpecificators
     {
         public:

            typedef vector<TRuleInstance>    TRuleInstances;

         private:

            TRuleInstances    _RuleInstances;
            TResoundingBatch  _Batch;

            SourceType        _Source;
            TUInt             _Iterator;
            TUInt             _Begin;
            TUInt             _End;
            TUInt             _CurrentInstance;

            PProgressFunc _ProgressFunc;
            TUInt  		  _ReportStep;
            TUInt		  _GlobalBegin;
            TUInt		  _GlobalEnd;

            void _SetProgressFunc(PProgressFunc tProgressFunc)
            {
                _ProgressFunc = tProgressFunc;
            };

            void _SetReportIndicators()
            {
		_Begin = _Source.Begin();
		_End   = _Source.End();
		_Iterator = _Begin;
    //            _GlobalBegin =  _Source.Begin();
  //              _GlobalEnd   = (_Source.End() - _Source.Begin()) * _RuleInstances.size();
//                _ReportStep  = TUInt(TSFloat(_GlobalEnd) / 100.0f); //%
                _ReportStep  = TUInt((_End - _Begin) / 100.0f); //%
            };

            void _Report()
            {
               //	if (((_Iterator*_CurrentInstance) % _ReportStep) == 0)
                 //	_ProgressFunc(_GlobalBegin, _GlobalEnd, _Iterator*_CurrentInstance);

                 _ProgressFunc(_Begin, _End, _Iterator);
            };


            void _ProcessForwardDifferential(const TUInt & tInstanceIndex)
            {
            TUInt i = tInstanceIndex;
            _Begin = _Source.Begin();
            _End   = _Source.End();

                for (_Iterator=_Begin; _Iterator<=_End; _Iterator++)
                {
                     _RuleInstances[i].AcceptForwardDifferential(_Source.SubString(_Iterator, _RuleInstances[i].Rule()->Influence()), _Iterator);

                if (_RuleInstances[i].Finished() && _RuleInstances[i].Excited())
                    _Batch.Merge(i, _RuleInstances[i].ResoundingItem());
                };
            };

            void _ProcessForward(const TUInt & tInstanceIndex)
            {
            TUInt i = tInstanceIndex;
            _Begin = _Source.Begin();
            _End   = _Source.End();

                for (_Iterator=_Begin; _Iterator<=_End; _Iterator++)
                {
                     _RuleInstances[i].Accept(_Source[_Iterator], _Iterator);

                if (_RuleInstances[i].Finished() && _RuleInstances[i].Excited())
                    _Batch.Merge(i, _RuleInstances[i].ResoundingItem());
                };
            };

            void _ProcessBackwardDifferential(const TUInt & tInstanceIndex)
            {
            TUInt i = tInstanceIndex;
            _Begin = _Source.Begin();
            _End   = _Source.End();

                for (_Iterator=_End; _Iterator>=_Begin; _Iterator--)
                {
                     _RuleInstances[i].AcceptForwardDifferential(_Source.SubString(_Iterator-_RuleInstances[i].Rule()->Influence(), _RuleInstances[i].Rule()->Influence()), _Iterator);

                if (_RuleInstances[i].Finished() && _RuleInstances[i].Excited())
                    _Batch.Merge(i, _RuleInstances[i].ResoundingItem());
                };
            };

            void _ProcessBackward(const TUInt & tInstanceIndex)
            {
            TUInt i = tInstanceIndex;
            _Begin = _Source.Begin();
            _End   = _Source.End();

                for (_Iterator=_End; _Iterator>=_Begin; _Iterator--)
                {
                     _RuleInstances[i].Accept(_Source[_Iterator], _Iterator);

                if (_RuleInstances[i].Finished() && _RuleInstances[i].Excited())
                    _Batch.Merge(i, _RuleInstances[i].ResoundingItem());
                };
            };


             void  _AddInstance   (const TRule & tRule)
             {
              _RuleInstances.push_back(TRuleInstance(tRule));

              _Batch.AddInstance(tRule.Value(), tRule.Number());
             };

             TBool _Find(const TRule & tRule, TUInt * tIndex)
             {
                 for (TUInt i=0; i<_RuleInstances.size(); i++)
                     if (tRule == (*_RuleInstances[i].Rule()))
                     {
                         *tIndex = i;
                         return true;
                     }
             return false;
             };

         public:

             TResoundingBatch ResoundingBatch() { return _Batch; }

             TRuleProcessor & Process()
             {
             if (!InstancesCount()) throw ENoRulesLoaded();

                for (TUInt i=0; i<_RuleInstances.size(); i++)
                {
                _CurrentInstance = i;
                      if (_RuleInstances[i].Rule()->Direction() == rd_Forward)
                      {
                           if (_RuleInstances[i].Rule()->Differential())
                                     _ProcessForwardDifferential(i);
                           else      _ProcessForward(i);
                      }
                      else
                      {
                           if (_RuleInstances[i].Rule()->Differential())
                                     _ProcessBackwardDifferential(i);
                           else      _ProcessBackward(i);
                      }
                };

             return *this;
             };


TRuleProcessor & Process(PProgressFunc tProgressFunc)
{
	if (!InstancesCount()) throw ENoRulesLoaded();

	_SetProgressFunc(tProgressFunc);
    _SetReportIndicators();
	_Report();

	for (TUInt i=0; i<_RuleInstances.size(); i++)
	{
    _Report();
		_CurrentInstance = i;
		if (_RuleInstances[i].Rule()->Direction() == rd_Forward)
		{
			if (_RuleInstances[i].Rule()->Differential())	_ProcessForwardDifferential(i);
			else      _ProcessForward(i);
        }
		else
		{
			if (_RuleInstances[i].Rule()->Differential())	_ProcessBackwardDifferential(i);
			else      _ProcessBackward(i);
		}
	};

    _Report();
return *this;
};

            TRuleProcessor<SourceType> & operator << (const TRule & tRule)
            {
            TUInt index;
                if (! _Find(tRule, &index)) _AddInstance(tRule);
            return *this;
            };

            TRuleProcessor<SourceType> & operator << (TRulesProxy tRulesProxy)
            {
            TUInt index;

                for (TUInt i=0; i<tRulesProxy.Count(); i++)
                    if (! _Find(tRulesProxy[i], &index))
                       _AddInstance(tRulesProxy[i]);

            return *this;
            };


            TUInt InstancesCount() const { return _RuleInstances.size(); }
            void  Clear()
            {
                _RuleInstances.clear();
                _Batch.Clear();
            }

            void GetProcessInfo(TUInt * tBegin, TUInt * tEnd, TUInt * tCurrent)
            {
                 *tCurrent  = _Iterator + _CurrentInstance*_End;
                 *tBegin    = _Begin;
                 *tEnd      = _End * InstancesCount();
            };

     TRuleProcessor(const SourceType & tSource) : _Source(tSource), _CurrentInstance(0), _Iterator(0), _Begin(0), _End(0){};
    ~TRuleProcessor(){ };
     };




#endif

