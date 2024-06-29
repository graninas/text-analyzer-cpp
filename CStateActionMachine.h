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
#ifndef CStateActionMachineH
#define CStateActionMachineH
//---------------------------------------------------------------------------

#include "UTypes.h"
#include "FiniteStateMachine.h"

     template <class StateType> class TStateActionMachine
     {
         public:

            virtual FSM::SMachineManipulator OnStart(const StateType & tState, const TUInt & tFirst)
            {
                return FSM::mm_Nothing;
            }

            virtual FSM::SMachineManipulator OnState(const StateType & tState, const TUInt & tIterator)
            {
                return FSM::mm_Nothing;
            };

            virtual FSM::SMachineManipulator OnEnd(const StateType & tState, const TUInt & tLast)
            {
                return FSM::mm_Nothing;
            };

        TStateActionMachine(){};

     };



#endif
 