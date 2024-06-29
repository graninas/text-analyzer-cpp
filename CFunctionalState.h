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
#ifndef CFunctionalStateH
#define CFunctionalStateH
//---------------------------------------------------------------------------

#include "UTypes.h"

enum TStateActionType {sat_None=0, sat_UnitBegin=1, sat_UnitBody=2, sat_ExcludedUnitEnd=3, sat_IncludedUnitEnd=4};

   template <class EventType, class NameType> class TFunctionalState
   {
       public:

           typedef EventType EventType;
           typedef NameType  NameType;

       protected:

           NameType             _Name;
           TStateActionType     _ActionType;

       public:

            virtual NameType              Name()             const { return _Name; };
            virtual TStateActionType      ActionType()       const { return _ActionType; };


         friend TBool operator == (const TFunctionalState<EventType, NameType> & tState1, const TFunctionalState<EventType, NameType> & tState2)
         {
              return (tState1._Name == tState2._Name) ? true : false;
         };

            TFunctionalState(const NameType & tName, const TStateActionType & tActionType) : _Name(tName), _ActionType(tActionType){};
   };


#endif
 