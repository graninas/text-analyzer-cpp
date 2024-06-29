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

//
// File:    FSM.h
// 
// Date:    23 January 2003
//
// Purpose: Finite State Machine template
// 
// Copyright (c) Serguei Satski 2003
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//


#ifndef _FSMTEMPLATE_
#define _FSMTEMPLATE_

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <deque>
#include <string>
#include <functional>
#include <iterator>
#include <iostream>


#define FSMBEGIN( StartFSMState )  (StartFSMState), \
                                   FSM::SFiniteStateMachineProxy<FSMStateType,FSMEventType>()<<(FSM::SStatesListProxy<FSMStateType>() <<
#define FSMSTATES
#define FSMEVENT( Arg )            ) \
                                   << (FSM::STransitionsProxy<FSMStateType,FSMEventType>( Arg ) <<
#define FSMEND                     )
#define FSMRESET                   FSM::ResetMachine



namespace FSM
{
    enum SMachineManipulator { mm_ResetMachine = 0, mm_Nothing };
    

// Exception definition for the state machine template class

    class SStateMachineException : public std::exception
    {
        private:
            const std::string      _Message;

        public:
            SStateMachineException(const std::string &  tMsg) : _Message( tMsg ) {}
            SStateMachineException(const char *         tMsg) : _Message( tMsg ) {}

            virtual const char * what() const throw() { return _Message.c_str(); }
            virtual ~SStateMachineException() throw () {}

        private:
            SStateMachineException();
    };


// No entry, no exit functions calls strategy

    template <class SState, class SEvent>
    class SEmptyFunctor
    {
        public:
            inline void operator() (SState & tFrom, const SEvent & tEvent, SState & tTo) { return; }
    };


// Entry functions calls strategy

    template <class SState, class SEvent>
    class SOnEnterFunctor
    {
        public:
            inline void operator() (SState & tFrom, const SEvent & tEvent, SState & tTo)
            {
                tTo.OnEnter(tFrom, tEvent);
            }
    };


// Exit functions calls strategy

    template <class SState, class SEvent>
    class SOnExitFunctor
    {
        public:
            inline void operator() (SState & tFrom, const SEvent & tEvent, SState & tTo)
            {
                tFrom.OnExit(tEvent, tTo);
            }
    };


// Both entry and exit functions calls strategy

    template <class SState, class SEvent>
    class SOnMoveFunctor
    {
        public:
            inline void operator() (SState & tFrom, const SEvent & tEvent, SState & tTo)
            {
                tFrom.OnExit(tEvent, tTo); tTo.OnEnter(tFrom, tEvent);
            }
    };


// Throw exception strategy for the unknown event

    template <class SEvent>
    class SThrowStrategy
    {
        public:
            inline void operator() (const SEvent &) const
            {
                throw SStateMachineException( "Unknown event." );
            }
    };


// Ignore strategy for the unknown event

    template <class SEvent>
    class SIgnoreStrategy
    {
        public:
            inline void operator() (const SEvent &) const
            {
                return;
            }
    };


// Temporary class to collect all the registered states

    template <class SState>
    class SStatesListProxy
    {
        private:
            std::vector<SState>    _StatesProxy;

        public:
            SStatesListProxy()
            {
                return;
            }

            SStatesListProxy & operator << (const SState & tState)
            { 
                    // Check whether the state is unique
                if (std::find(_StatesProxy.begin(), _StatesProxy.end(), tState) != _StatesProxy.end())
                    throw SStateMachineException("States must be unique.");

                _StatesProxy.push_back(tState);
                return *this; 
            }

            inline const std::vector<SState> & GetStates() const
            {
                return _StatesProxy;
            }

//--- Модификация GAS ----------------------------------------------------------
            unsigned int Count() const
            {
                return _StatesProxy.size();
            }

            void Clear()
            {
                 _StatesProxy.clear();
            }
//------------------------------------------------------------------------------
    };

    

// Temporary class to collect transitions for a single event
//--- Модификация GAS ----------------------------------------------------------
    template <class SState, class SEvent>
    class STransitionsProxy
    {
        private:
            SEvent                      _Event;
            std::vector<SState>         _NewStates;

        public:
            explicit STransitionsProxy(const SEvent & tEvent) : _Event(tEvent)
            {
                return;
            }

            //Модификация
            STransitionsProxy()
            {
            };
            /////////////

            STransitionsProxy & operator << (const SState & tState)
            {
                _NewStates.push_back(tState);
                return *this;
            }

            //Модификация
            STransitionsProxy & operator << (const SEvent & tEvent)
            {
                _Event = tEvent;
                return *this;
            }
            /////////////

            inline const std::vector<SState> & GetStates() const
            {
                return _NewStates;
            }

            inline const SEvent & GetEvent() const
            {
                return _Event;
            }

            //Модификация
            unsigned int StatesCount() const
            {
                return _NewStates.size();
            };

            void Clear()
            {
                _NewStates.clear();
            };
            /////////////
    };
//------------------------------------------------------------------------------


// Temporary class to collect all the transitions

    template <class SState, class SEvent>
    class SFiniteStateMachineProxy
    {
        private:
            std::vector<SState>                     _MachineStatesProxy;
            bool                                    _HaveStates;
            std::vector<SEvent>                     _MachineEventsProxy;
            std::vector<std::vector<SState> >       _Transitions;
    
        public:
            SFiniteStateMachineProxy() : _HaveStates(false)
            {
                return;
            }

            SFiniteStateMachineProxy & operator << (const SStatesListProxy<SState> & tStates)
            {
                if (_HaveStates) throw SStateMachineException("Too much state lists.");
                _HaveStates = true;
                _MachineStatesProxy = tStates.GetStates();
                return *this;
            }

            SFiniteStateMachineProxy & operator << (const STransitionsProxy<SState,SEvent> & tTransitions)
            {
                if (!_HaveStates) throw SStateMachineException("States must be defined before the transitions.");
            
                if (_MachineStatesProxy.size() != tTransitions.GetStates().size())
                    throw SStateMachineException("Transition states do not coincide to the states list.");

                    // Check that the event is unique
                if (std::find(_MachineEventsProxy.begin(), _MachineEventsProxy.end(), tTransitions.GetEvent()) != _MachineEventsProxy.end())
                    throw SStateMachineException("Events must be unique.");
                    
                    // Check the transition validity
                CheckTransitionValidity(tTransitions.GetStates().begin(), tTransitions.GetStates().end());

                _MachineEventsProxy.push_back(tTransitions.GetEvent());
                _Transitions.push_back(tTransitions.GetStates());
                return *this; 
            }


                // Check that the transitions lead to a registered state

            inline void CheckTransitionValidity(typename std::vector<SState>::const_iterator tFirst, typename std::vector<SState>::const_iterator tLast)
            {
                for ( ; tFirst != tLast; ++tFirst )
                {
                    if (std::find(_MachineStatesProxy.begin(), _MachineStatesProxy.end(), *tFirst) == _MachineStatesProxy.end())
                        throw SStateMachineException("Transition state is not valid.");
                }
            }

            inline const std::vector<SState> & GetStates() const
            {
                return _MachineStatesProxy;
            }

            inline const std::vector< std::vector<SState> > & GetTransitions() const
            {
                return _Transitions;
            }

            inline const std::vector<SEvent> & GetEvents() const
            {
                return _MachineEventsProxy;
            }
    };

            
// Finite state machine template

    template <class SState, class SEvent, class SFunctor = SEmptyFunctor<SState,SEvent>, class SUnknownEventStrategy = SThrowStrategy<SEvent> >
    class SFiniteStateMachine
    {
        public:
            typedef SState     StateType;
            typedef SEvent     EventType;

        private:
            StateType                               _CurrentState;               // Current machine state
            std::vector<StateType>                  _States;                     // A list of the registered states
            std::vector<EventType>                  _Events;                     // A list of the registered events
            std::vector< std::vector<StateType> >   _Transitions;                // A table of transitions between states
            SFunctor                                _Functor;                    // Transition function
            SUnknownEventStrategy                   _UnknownEventStrategy;       // Unknown event strategy
            std::deque<EventType>                   _EventsQueue;                // Internal events queue to support events
                                                                                //   that were generated in the transition functions
            bool                                    _InProcess;                  // To be sure that we are in the process of events
            int                                     _CurrentStateIndex;          // Index of column in a transition table (0 - based)
            StateType                               _InitialState;               // Start machine state

        public:
            SFiniteStateMachine(const StateType &tStartState, const SFiniteStateMachineProxy<StateType,EventType> &tProxyMachine) :
                _CurrentState(tStartState), _States(tProxyMachine.GetStates()),
                _Events(tProxyMachine.GetEvents()), _Transitions(tProxyMachine.GetTransitions()), _InProcess(false),
                _CurrentStateIndex(-1), _InitialState(tStartState)
            {
                    // Check that the start state is valid
                typename std::vector<StateType>::iterator  k(std::find(_States.begin(), _States.end(), tStartState));

                if (k == _States.end()) throw SStateMachineException("Start state is not valid.");
                _CurrentStateIndex = std::distance(_States.begin(), k);
            }

                //
                // Reset the machine to the initial state.
                // Warning: no transition functions will be called if any
                //
            inline SFiniteStateMachine & Reset()
            {
                _CurrentState = _InitialState;
                _CurrentStateIndex = GetStateIndex(_CurrentState);
                _InProcess = false;
                _EventsQueue.clear();
                return *this;
            }

                //
                // Returns the current machine state
                //
            inline StateType GetCurrentState() const
            {
                return _CurrentState;
            }

                //
                // Accepts an event
                //
            SFiniteStateMachine &  AcceptEvent(const EventType & tEvent)
            {
            /*    _EventsQueue.push_back(tEvent);
                if (_InProcess) return *this;

                _InProcess = true;

                while (!_EventsQueue.empty())
                {
                    ProcessEvent(_EventsQueue.front());
                    _EventsQueue.pop_front();
                }

                _InProcess = false;
                return *this;         */

                ProcessEvent(tEvent);
                return *this;
            }

//--- Модификация GAS ----------------------------------------------------------
            SFiniteStateMachine &  AcceptEvent(const EventType::TSubEvent & tSubEvent)
            {
                    ProcessEvent(EventType(tSubEvent));

                return *this;
            }
//------------------------------------------------------------------------------

            inline SFiniteStateMachine & operator << (const EventType & tEvent)
            {
                return AcceptEvent(tEvent);
            }


//--- Модификация GAS ----------------------------------------------------------
            inline SFiniteStateMachine & operator << (const EventType::TSubEvent & tSubEvent)
            {
                return AcceptEvent(tSubEvent);
            }
//------------------------------------------------------------------------------


            inline SFiniteStateMachine & operator << (SMachineManipulator tManipulator)
            {
                if (tManipulator == mm_ResetMachine) return Reset();
                return *this;
            }

        private:
            inline void ProcessEvent(const EventType & tEvent)
            {   
                int  EventIndex(GetEventIndex(tEvent));
                if (EventIndex == -1) return;

                 StateType      OldState(_CurrentState);


                _CurrentState = (_Transitions[EventIndex])[_CurrentStateIndex];
                _CurrentStateIndex = GetStateIndex(_CurrentState);

                _Functor(OldState, tEvent, _CurrentState);
            }

            inline int GetEventIndex(const EventType & tEvent) const
            {

                typename std::vector<EventType>::const_iterator   k(std::find(_Events.begin(), _Events.end(), tEvent));

                if (k == _Events.end())
                {
                        _UnknownEventStrategy(tEvent); return -1;
                }
                return std::distance(_Events.begin(), k);
            }

            inline int GetStateIndex(const StateType & tState) const
            {
                return std::distance(_States.begin(), std::find( _States.begin(), _States.end(), tState));
            }

        private:

                // Prevent the illegal usage

            SFiniteStateMachine();
            SFiniteStateMachine & operator= (const SFiniteStateMachine &);
            SFiniteStateMachine(const SFiniteStateMachine &);
    };
    
        // Allow writing the current machine state to an output stream

    template <class SState, class SEvent, class SFunctor, class SUnknownEventStrategy>
        std::ostream & operator << (std::ostream &  Stream, const SFiniteStateMachine<SState,SEvent,SFunctor,SUnknownEventStrategy> & Machine)
    {
        return Stream << Machine.GetCurrentState();
    }
    
}   // End of the FSM namespace

#endif

