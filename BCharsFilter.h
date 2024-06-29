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
#ifndef BCharsFilterH
#define BCharsFilterH
//---------------------------------------------------------------------------

#include "CNamedSetItem.h"
#include "CErrorSpecificators.h"
#include "UConstants.h"



typedef TNamedSetItem<TTextString, TCharsSet> TNamedCharsSetFilter;

enum  TCharsFilterSign {cf_Positive, cf_Negative};
enum  TCharsFilterDefinition {cf_Definitable, cf_NonDefinitable};

    class cfm_Definitable
    {
    cfm_Definitable(){};
       protected:
           TUInt _Index;
       public:
           TUInt Index() const    { return _Index; }

       cfm_Definitable (const TUInt & tIndex) : _Index (tIndex) {};
    };



     class TCharsFilter : public TErrorSpecificators
     {
         private:

             TNamedCharsSetFilter    _Filter;
             TCharsFilterSign        _Sign;
             TUInt                   _SubIndex;
             TCharsFilterDefinition  _Definition;

         public:


             TNamedCharsSetFilter Filter()   const { return _Filter; };
             TBool                Negative() const { return _Sign == cf_Negative; }
             TUInt    SubIndex() const { return _SubIndex; };

             TTextString  Name() const { return _Filter.Name(); };


             TBool Definitable() const { return _Definition == cf_Definitable; };
             TBool Defined()     const { return (_Filter.Set().Length()>0) ? true : false; };
             void  Define(const TUInt & tSubIndex, const TCharsSet & tCharsSet)
             {
               if (_SubIndex != tSubIndex) return;

                  if (Definitable()) _Filter.Set(GetPare(tCharsSet.Elements()));
                  else throw EFilterNotDefinitable();
             };



//Считается, что второй операнд не может быть негативным. В противном случае результат не определен.
         friend TBool operator == (const TCharsFilter & tFilter1, const TCharsFilter & tFilter2)
         {
              return   (tFilter1._Filter.IsSubset(tFilter2._Filter.Set())) ? (!tFilter1.Negative()) : (tFilter1.Negative());
         };


            TCharsFilter & operator << (const TCharsFilterSign & tSign)
            {
                _Sign = tSign;
                return *this;
            };

            TCharsFilter & operator << (const TCharsFilterDefinition & tDefinition)
            {
                _Definition = tDefinition;
                return *this;
            };

            TCharsFilter & operator << (const cfm_Definitable & tDefinitionManipulator)
            {
                _Definition = cf_Definitable;
                _SubIndex   = tDefinitionManipulator.Index();
                return *this;
            };


            TCharsFilter & operator << (const TUInt & tSubIndex)
            {
                _SubIndex = tSubIndex;
                return *this;
            };

            TCharsFilter & operator << (const TTextString & tName)
            {
                _Filter.Name(tName);
                return *this;
            };

            TCharsFilter & operator << (const TCharsSet & tCharsSet)
            {
                _Filter.Set(tCharsSet);
                return *this;
            };



         TCharsFilter(const TCharsSet & tCharsSet)
            : _Filter(TNamedCharsSetFilter("", tCharsSet)), _SubIndex(0), _Sign(cf_Positive), _Definition(cf_NonDefinitable){};

         TCharsFilter(const TTextString & tName, const TCharsSet & tCharsSet)
            : _Filter(TNamedCharsSetFilter(tName, tCharsSet)), _SubIndex(0), _Sign(cf_Positive), _Definition(cf_NonDefinitable){};

         TCharsFilter(const TTextString & tName, const TCharsSet & tCharsSet, const TCharsFilterSign & tSign)
            : _Filter(TNamedCharsSetFilter(tName, tCharsSet)), _SubIndex(0), _Sign(tSign), _Definition(cf_NonDefinitable){};



      /*   TCharsFilter(const TTextString & tName, const TCharsSet & tCharsSet, const TUInt & tSubIndex, const TCharsFilterSign & tSign)
            : _Filter(TNamedCharsSetFilter(tName, tCharsSet)), _SubIndex(tSubIndex), _Sign(tSign), _Definition(cf_NonDefinitable){};

         TCharsFilter(const TTextString & tName, const TCharsSet::TElementType & tElements, const TUInt & tSubIndex, const TCharsFilterSign & tSign)
            : _Filter(TNamedCharsSetFilter(tName, tElements)), _SubIndex(tSubIndex), _Sign(tSign), _Definition(cf_NonDefinitable){};

         TCharsFilter(const TTextString & tName, const TCharsSet & tCharsSet, const TUInt & tSubIndex, const TCharsFilterSign & tSign, const TCharsFilterDefinition & tDefinition)
            : _Filter(TNamedCharsSetFilter(tName, tCharsSet)), _SubIndex(tSubIndex), _Sign(tSign), _Definition(tDefinition){};

         TCharsFilter(const TTextString & tName, const TCharsSet::TElementType & tElements, const TUInt & tSubIndex, const TCharsFilterSign & tSign, const TCharsFilterDefinition & tDefinition)
            : _Filter(TNamedCharsSetFilter(tName, tElements)), _SubIndex(tSubIndex), _Sign(tSign), _Definition(tDefinition){};


           */

        ~TCharsFilter(){};

        private:
           TCharsFilter() : _Filter("", ""){};
     };







#endif
