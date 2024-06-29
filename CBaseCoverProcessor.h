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
#ifndef CBaseCoverProcessorH
#define CBaseCoverProcessorH
//---------------------------------------------------------------------------


#include "BValuesCover.h"
#include "CErrorSpecificators.h"

#include "UReportFunctionsTypes.h"


     template <class SourceType> class  TBaseCoverProcessor : public TErrorSpecificators
     {
         private:

            SourceType    _Source;
            TValuesCover  _CharValuesMap;
            TValuesCover  _BaseCover;

            TBool         _CoverGenerated;

            TUInt         _Iterator;
            TUInt         _Begin;
            TUInt         _End;


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
//            	if ((_Iterator % _ReportStep) == 0)
  //              	_ProgressFunc(_Begin, _End, _Iterator);
            };

         public:

             TValuesCover   BaseCover() const
             {
                 if (!_CoverGenerated) throw ECoverNotGenerated();
                 return _BaseCover;
             };

             TValuesCover & CharValuesMap()   { return _CharValuesMap; }
             TValuesCover   CharValuesMap(const TValuesCover & tCharValuesMap)
             {
                 _CoverGenerated = false;
                 _CharValuesMap = tCharValuesMap;
             };


             TBaseCoverProcessor & Process()
             {
             if (_CharValuesMap.Count() != 256) throw EInvalidCharValuesMap();

             TUChar ch;
             _BaseCover.Clear();

				//<Небезопасный код>
					TChar * chString = _Source.c_str();
				//</Небезопасный код>

             _Begin = _Source.Begin();
             _End   = _Source.End();

                for (_Iterator=_Begin; _Iterator<=_End; _Iterator++)
                {
                     ch = TUChar(_Source[_Iterator]);
                    _BaseCover << _CharValuesMap[ch];
                };

             _CoverGenerated = true;

             return *this;
             };


TBaseCoverProcessor & Process(PProgressFunc tProgressFunc)
{
	if (_CharValuesMap.Count() != 256) throw EInvalidCharValuesMap();

	TUChar ch;
	_BaseCover.Clear();

//<Небезопасный код>
	TChar * chString = _Source.c_str();
//</Небезопасный код>

		_Begin = _Source.Begin();
		_End   = _Source.End();
		_Iterator = _Begin;

		_SetProgressFunc(tProgressFunc);
		_SetReportStep();
		_Report();

	for (_Iterator=_Begin; _Iterator<=_End; _Iterator++)
	{
    _Report();
		ch = TUChar(_Source[_Iterator]);
    	_BaseCover << _CharValuesMap[ch];
	};

    _Report();

_CoverGenerated = true;
return *this;
};


             TBaseCoverProcessor & operator << (const TValuesCover & tCharValuesMap)
             {
                _CharValuesMap = tCharValuesMap;
                _CoverGenerated = false;
                 return *this;
             };

             void Clear() { _BaseCover.Clear(); };


             void GetProcessInfo(TUInt * tBegin, TUInt * tEnd, TUInt * tCurrent)
             {
                 *tCurrent  = _Iterator;
                 *tBegin    = _Begin;
                 *tEnd      = _End;
             };


             TBaseCoverProcessor(const SourceType & tSource, const TValuesCover & tCharValuesMap)
              : _Source(tSource), _CharValuesMap(tCharValuesMap), _CoverGenerated(false), _Iterator(0), _Begin(0), _End(0) {};

     };



#endif
 