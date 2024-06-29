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
#ifndef CStateMachineDescriptorH
#define CStateMachineDescriptorH
//---------------------------------------------------------------------------

#include "FiniteStateMachine.h"
#include "UStructs.h"



    template <class StateType, class EventType> class TStateMachineDescriptor
    {
       public:

          typedef FSM::SFiniteStateMachineProxy<StateType, EventType> TProxy;

          class ENoSuchState{};

       private:

          TProxy        _Proxy;
          StateType     _StartState;

          TTextString   _Name;


          FSM::SStatesListProxy<StateType>             _StatesProxy;
          FSM::STransitionsProxy<StateType, EventType> _TransitionsProxy;

          TBool   _EventLoaded;
          TBool   _StatesAccepted;




          StateType _GetStateFromStatesProxy(StateType::NameType tName)
          {
              vector<StateType> States = _StatesProxy.GetStates();
              for (TUInt i=0; i<States.size(); i++)
                if (States[i].Name() == tName) return States[i];

          throw ENoSuchState();
          };


          void _AcceptStates()
          {
              _Proxy << _StatesProxy;
              _StatesAccepted = true;
          };

          void _AcceptTransitions()
          {
              if (!_StatesAccepted) _AcceptStates();

              _Proxy << _TransitionsProxy;
              _TransitionsProxy.Clear();
              _EventLoaded = false;
          };

       public:

              TTextString Name() const { return _Name(); };
              void        Name(const TTextString & tName) { _Name() = tName; };

              TProxy      Proxy() const { return _Proxy; };
              void        Proxy(const TProxy & tProxy) { _Proxy = tProxy; };

              StateType   StartState() { return _StartState; };
              void        StartState(const StateType & tStartState) { _StartState  = tStartState; };


            TStateMachineDescriptor & operator << (const StateType & tState)
            {
                _StatesProxy << tState;
                return *this;
            };

            TStateMachineDescriptor & operator << (const EventType & tEvent)
            {
                _TransitionsProxy << tEvent;
                _EventLoaded = true;

                return *this;
            };

            TStateMachineDescriptor & operator << (const StateType::NameType & tStateName)
            {
                _TransitionsProxy << _GetStateFromStatesProxy(tStateName);

                if ((_TransitionsProxy.StatesCount() == _StatesProxy.Count()) && _EventLoaded)
                    _AcceptTransitions();

                return *this;
            };


       /*   void  Clear()
          {
              _StatesProxy.clear();
              _TransitionsProxy.clear();
          };      */


          TStateMachineDescriptor(const StateType & tStartState, const TTextString & tSMDescriptorName) : _StartState(tStartState), _Name(tSMDescriptorName), _EventLoaded(false), _StatesAccepted(false) {};

          TStateMachineDescriptor(const TProxy & tProxy, const StateType & tStartState, const TTextString & tSMDescriptorName)
             : _Proxy(tProxy), _StartState(tStartState), _Name(tSMDescriptorName), _EventLoaded(false), _StatesAccepted(false) {};

         ~TStateMachineDescriptor(){};

       private:
          TStateMachineDescriptor(){};
    };

#endif

/*
     Протестировано. Паботает.

     Пример использования в UParSentWordFSM.h.
*/
 