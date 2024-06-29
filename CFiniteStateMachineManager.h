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
#ifndef CFiniteStateMachineManagerH
#define CFiniteStateMachineManagerH

#include "CStateMachineDescriptor.h"

#include "UReportFunctionsTypes.h"


 template <class EventType, class FiniteStateMachineType, class StateMachineDescriptorType, class SourceType>
   class TFiniteStateMachineManager
   {
      private:

            StateMachineDescriptorType     _Descriptor;
            SourceType                     _Source;

            TUInt                          _Begin;
            TUInt                          _End;
            TUInt                          _Iterator;


            PProgressFunc _ProgressFunc;
            TUInt  		  _ReportStep;

            void _SetProgressFunc(PProgressFunc tProgressFunc)
            {
                _ProgressFunc = tProgressFunc;
            };

            void _SetReportStep()
            {
                _ReportStep = TUInt((_End - _Begin) / 100.0f); //%
            };

            void _Report()
            {
            	if ((_Iterator % _ReportStep) == 0)
                	_ProgressFunc(_Begin, _End, _Iterator);
            };

      public:

       TFiniteStateMachineManager & Process()
       {
       _Begin = _Source.Begin();
       _End   = _Source.End();

       FiniteStateMachineType  _Machine(_Descriptor.StartState(), _Descriptor.Proxy());

           for (_Iterator=_Begin; _Iterator<=_End; _Iterator++)
           {
                _Machine << EventType(_Source[_Iterator], _Iterator);
           };

         _Machine << EventType(_Source.EndSign(), _End+1);

       return *this;
       };


       TFiniteStateMachineManager & Process(PProgressFunc tProgressFunc)
       {
       _Begin = _Source.Begin();
       _End   = _Source.End();
       _Iterator = _Begin;

       _SetProgressFunc(tProgressFunc);
       _SetReportStep();
       _Report();

       FiniteStateMachineType  _Machine(_Descriptor.StartState(), _Descriptor.Proxy());

           for (_Iterator=_Begin; _Iterator<=_End; _Iterator++)
           {
                _Machine << EventType(_Source[_Iterator], _Iterator);

           _Report();
           };

       _Report();
       _Machine << EventType(_Source.EndSign(), _End+1);

       return *this;
       };


       void GetProcessInfo(TUInt * tBegin, TUInt * tEnd, TUInt * tIterator)
       {
          *tBegin = _Begin;
          *tEnd   = _End;
          *tIterator = _Iterator;
       };

   TFiniteStateMachineManager( const StateMachineDescriptorType & tDescriptor, const SourceType & tSource)
      : _Descriptor(tDescriptor), _Source(tSource), _ReportStep(0), _ProgressFunc(NULL)
      {};

   private:
      TFiniteStateMachineManager(){};
   };

//---------------------------------------------------------------------------
#endif




/*
   Протестированы основные функции. Работает.

   Пример использования - в UParSentWordFSM.h
*/
