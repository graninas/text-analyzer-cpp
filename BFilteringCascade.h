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
#ifndef BFilteringCascadeH
#define BFilteringCascadeH
//---------------------------------------------------------------------------

#include "UStructs.h"
#include "BFilteringResult.h"


    class TFilteringCascade : public TErrorSpecificators
    {
         public:

             class TActiveFilterItem
             {
             public:

                  TCharsFilter      Filter;
                  TFilteringResult  Result;

                  TActiveFilterItem(const TCharsFilter & tFilter, const TFilteringResult & tResult) : Filter(tFilter), Result(tResult) {};
             };

             typedef vector<TActiveFilterItem> TActiveFilters;

         private:

             TActiveFilters  _Filters;

         public:


            TFilteringResult  Accept(const TCharsSet & tCharsSet)
            {
                 TCharsFilter filter(tCharsSet);

                 for (TUInt i=0; i<_Filters.size(); i++)
                     if (_Filters[i].Filter == filter) return _Filters[i].Result;

            return TFilteringResult()<<frm_Skip;
//            throw EResultNotDefined();
            };

            void    Define(const TUInt & tSubIndex, const TCharsSet & tCharsSet)
            {
                for (TUInt i=0; i<_Filters.size(); i++)
                   _Filters[i].Filter.Define(tSubIndex, tCharsSet);
            };


            TFilteringCascade & operator << (const TCharsFilter & tFilter)
            {
               _Filters.push_back(TActiveFilterItem(tFilter, TFilteringResult()));
                return *this;
            };

            TFilteringCascade & operator << (const TFilteringResult & tFilteringResult)
            {
               if (!_Filters.size()) throw ENoFiltersLoaded();

               _Filters[_Filters.size()-1].Result = tFilteringResult;
                return *this;
            };

            TFilteringCascade & operator << (const TFilteringResultMans & tFilteringResultManipulator)
            {
               if (!_Filters.size()) throw ENoFiltersLoaded();

               _Filters[_Filters.size()-1].Result << tFilteringResultManipulator;
                return *this;
            };

            TFilteringCascade & operator << (const frm_Transit & tFrm_Transit)
            {
               if (!_Filters.size()) throw ENoFiltersLoaded();

               _Filters[_Filters.size()-1].Result << tFrm_Transit;
                return *this;
            };

            TFilteringCascade & operator << (const frm_Define & tFrm_Define)
            {
               if (!_Filters.size()) throw ENoFiltersLoaded();

               _Filters[_Filters.size()-1].Result << tFrm_Define;
                return *this;
            };

            TFilteringCascade & operator << (const cfm_Definitable & tCfm_Definitable)
            {
               if (!_Filters.size()) throw ENoFiltersLoaded();

               _Filters[_Filters.size()-1].Filter << tCfm_Definitable;
                return *this;
            };


            void Clear(){ _Filters.clear(); }

             TFilteringCascade(){};
            ~TFilteringCascade(){ Clear(); };
    };


/*


          inline TSignFilter * operator[] (const TUInt & tIndex)
          {
              if (tIndex>=_Filters.size()) throw EOutOfRange();

                 return &_Filters[tIndex];
          };

          inline TSignFilter * operator[] (const TFilterKey & tFilterKey)
          {
              if (tIndex>=_Filters.size()) throw EOutOfRange();

                 return &_Filters[tIndex];
          };
*/
#endif
