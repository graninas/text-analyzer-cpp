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
#ifndef DAdaptedRangeMapH
#define DAdaptedRangeMapH
//---------------------------------------------------------------------------

#include "UStructs.h"
#include "DRangeAdapter.h"

template<class RangeAdapterType = TRangeAdapter> class TAdaptedRangeMap
	{
	public:
    	typedef TTextString SpecificatorType;
        SpecificatorType    Specificator() { return _Alias; };

        typedef vector<RangeAdapterType> TRangeAdapters;

        class EOutOfRange{};

private:

		TRangeAdapters _Items;
        TTextString    _Alias;

      TUInt _Count() const
      {
          return _Items.size();
      };

      void _Clear()
      {
          _Items.clear();
          _Alias = "";
      };

public:
		TTextString Alias() const
        {
			return _Alias;
        }

        void Alias(const TTextString & tAlias)
        {
			_Alias = tAlias;
        }

      TBool IsValidIndex(const TUInt & tIndex) const
      {
          if (tIndex >= _Items.size()) return false;
      return true;
      };

      TRangeAdapters Items()
      {
          return _Items;
      };

      TRangeAdapters Items(const TUInt & tIndex, const TUInt & tCount)
      {
      TRangeAdapters rangeAdapters;

          for (TUInt i=0; ((i < tCount) && (i < _Items.size())); i++)
          rangeAdapters.push_back(_Items[i+tIndex]);

      return rangeAdapters;
      };

      TUInt Count() const
      {
          return _Count();
      };

      RangeAdapterType & operator[](const TUInt & tIndex)
      {
          if (!IsValidIndex(tIndex)) throw EOutOfRange();
      return _Items[tIndex];
      };

      void AddItems(const TRangeAdapters & tAdapters)
      {
          for (TUInt i=0; i<tAdapters.size(); i++)
          _Items.push_back(tAdapters[i]);
      };

      void Clear()
      {
          _Clear();
      };

      void Sort()
      {
          sort(_Items.begin(), _Items.end());
      };


	TAdaptedRangeMap()
    	:	_Alias("")
        {};

	TAdaptedRangeMap<RangeAdapterType>(const TTextString & tAlias)
    	:	_Alias(tAlias)
        {};

	TAdaptedRangeMap<RangeAdapterType>(const TTextString & tAlias, const TRangeAdapters & tAdapters)
    	:  _Alias(tAlias), _Items(tAdapters)
        {};

      ~TAdaptedRangeMap<RangeAdapterType>()
      {
          Clear();
      };


};	   //End of class




#endif
