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
#ifndef CHamNSConnectorH
#define CHamNSConnectorH
//---------------------------------------------------------------------------

#include "CHamNeuroSystem.h"
#include "UConstants.h"

template <class T> class THamNSConnector
{
private:

	void          ByteToBinaryVector(T DataItem, TSInt SizeOfData, TSampleVector *DestinationVector);
	TSampleVector VectorToBinaryVector(vector <T> SourceVector);

public:

	typedef vector<T> TVector;

	THamNeuroSystem HamNS;

	void  NSLoadEntryVector(TVector  EntryVector);
	TUInt NSLoadSampleImage(TVector NewSampleImage);

	void  NSStep1_Initialize();
	void  NSStep2_SingleIteration();
	bool  NSStep2_DoIterations(TSInt MaxIterations);
	bool  NSStabilized();

	bool  NSDoAllSteps(TSInt MaxIterations);
	TSInt NSResultIndex();
	void  NSResult(TResultVector *Res);

	THamNSConnector(){};
	~THamNSConnector(){};
};

template <class T> void THamNSConnector<T>::ByteToBinaryVector(T DataItem, TSInt SizeOfData, TSampleVector *DestinationVector)
{
vector <bool>  BoolBits;
T NewDataItem = DataItem;

	for (TSInt i=1; i<SizeOfData; i++)
	{
		BoolBits.clear();

		BoolBits.push_back(	NewDataItem & bitOne	);
		BoolBits.push_back( NewDataItem & bitTwo	);
		BoolBits.push_back( NewDataItem & bitThree	);
		BoolBits.push_back( NewDataItem & bitFour	);
		BoolBits.push_back( NewDataItem & bitFive	);
		BoolBits.push_back( NewDataItem & bitSix	);
		BoolBits.push_back( NewDataItem & bitSeven	);
		BoolBits.push_back( NewDataItem & bitEight	);

		for (TUInt j=0; j<BoolBits.size(); j++)
                {
			if (BoolBits[j]) DestinationVector->push_back(1);
			else		 DestinationVector->push_back(0);
                }

	NewDataItem = NewDataItem >> 8;
	};
};

template <class T> TSampleVector THamNSConnector<T>::VectorToBinaryVector(TVector SourceVector)
{
	TSInt SizeOfData;
	T     DataItem;
	TUInt i;
	TSampleVector ResVector;

	SizeOfData = sizeof(T);
	
	for (i=0; i<SourceVector.size(); i++)
	{
		DataItem = SourceVector[i];
		ByteToBinaryVector(DataItem, SizeOfData, &ResVector);
	};

	return ResVector;
};

template <class T> void THamNSConnector<T>::NSLoadEntryVector(TVector EntryVector)
{
	HamNS.LoadEntryVector(VectorToBinaryVector(EntryVector));
};

template <class T> TUInt THamNSConnector<T>::NSLoadSampleImage(TVector NewSampleImage)
{
	return HamNS.LoadSampleImage(VectorToBinaryVector(NewSampleImage));
};

template <class T> void THamNSConnector<T>::NSStep1_Initialize()
{
        if (ExtendedNS)	HamNS.Step1_InitializeEx();
        else            HamNS.Step1_Initialize();
};

template <class T> void THamNSConnector<T>::NSStep2_SingleIteration()
{
	HamNS.Step2_SingleIteration();
};

template <class T> bool THamNSConnector<T>::NSStep2_DoIterations(TSInt MaxIterations)
{
	return HamNS.Step2_DoIterations(MaxIterations);
};

template <class T> bool THamNSConnector<T>::NSStabilized()
{
	return HamNS.Stabilized();
};

template <class T> bool THamNSConnector<T>::NSDoAllSteps(TSInt MaxIterations)
{
	return HamNS.DoAllSteps(MaxIterations);
};

template <class T> TSInt THamNSConnector<T>::NSResultIndex()
{
	return HamNS.ResultIndex();
};

template <class T> void THamNSConnector<T>::NSResult(TResultVector *Res)
{
	HamNS.Result(Res);
};


#endif
 