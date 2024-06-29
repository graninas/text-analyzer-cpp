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
#ifndef BFilteringResultH
#define BFilteringResultH
//---------------------------------------------------------------------------

#include "BCharsFilter.h"

enum TFilteringResultMans {frm_Skip, frm_Excit, frm_LinkDot, frm_EndProc, frm_Reset, frm_TimeBackReset};

    class frm_Manipulator
    {
       protected:
           TUInt _Index;

           frm_Manipulator(){};
       public:
           TUInt Index() const    { return _Index; }

       frm_Manipulator (const TUInt & tIndex) : _Index (tIndex) {};
    };


    class frm_Transit : public frm_Manipulator
    {
    frm_Transit(){};
       public:
          frm_Transit (const TUInt & tIndex) : frm_Manipulator (tIndex) {};
    };

    class frm_Define  : public frm_Manipulator
    {
    frm_Define(){};
       public:
          frm_Define (const TUInt & tIndex) : frm_Manipulator (tIndex) {};
    };


    class TFilteringResult : public TErrorSpecificators
    {
        private:

            TBool     _Skip;
            TBool     _Excit;
            TBool     _LinkDot;

            TBool     _Define;
            TUInt     _FilterSubIndex;

            TBool     _Transit;
            TUInt     _TransitIndex;

            TBool     _EndProc;
            TBool     _Reset;
            TBool     _TimeBackReset;

        public:

            TBool     Skip()           const { return _Skip; }
            TBool     Excit()          const { return _Excit; }
            TBool     LinkDot()        const { return _LinkDot; }
            TBool     Define()         const { return _Define; }
            TBool     Transit()        const { return _Transit; }
            TUInt     FilterSubIndex() const { return _FilterSubIndex; }
            TUInt     TransitIndex()   const { return _TransitIndex; }
            TBool     EndProc()        const { return _EndProc; }
            TBool     Reset()          const { return _Reset; }
            TBool     TimeBackReset()  const { return _TimeBackReset; }


            TFilteringResult & operator << (const TFilteringResultMans & tMan)
            {
                switch(tMan)
                {
                    case frm_Skip:     _Skip    = true; break;
                    case frm_Excit:    _Excit   = true; break;
                    case frm_LinkDot:  _LinkDot = true; break;
                    case frm_EndProc:  _EndProc = true; break;
                    case frm_Reset:    _Reset   = true; break;
                    case frm_TimeBackReset:    _TimeBackReset   = true; break;
                };
                return *this;
            };

            TFilteringResult & operator << (const frm_Transit & tFrm_Transit)
            {
                 _TransitIndex = tFrm_Transit.Index();
                 _Transit = true;

            return *this;
            };

            TFilteringResult & operator << (const frm_Define & tFrm_Define)
            {
                 _FilterSubIndex = tFrm_Define.Index();
                 _Define = true;

            return *this;
            };


           TFilteringResult()  : _Skip(false), _Excit(false), _LinkDot(false), _Define(false),
              _FilterSubIndex(0), _Transit(false), _TransitIndex(0), _EndProc(false), _Reset(false), _TimeBackReset(false){};
    };




#endif
 