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
#pragma hdrstop
#include "CHamNeuroSystem.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


void THamNeuroSystem::LoadEntryVector(TSampleVector aEntryVectorX)
{
	EntryVectorX = aEntryVectorX;
};

TUInt THamNeuroSystem::LoadSampleImage(TSampleVector aNewSampleImage)
{
   return SMatrix.AddSampleVector(aNewSampleImage);
};

void THamNeuroSystem::InitW()
{
TWeightVector V;

	for (TUInt i=0; i<SMatrix.SamplesMap.size(); i++)
	{
		V.clear();

		for (TUInt j=0; j<SMatrix.SamplesMap[i].size(); j++)
			V.push_back(SMatrix.SamplesMap[i][j]*0.5);

		W.push_back(V);
	};
};

void THamNeuroSystem::CalcKoefs()
{
	E  = 1 /(2.0 * SMatrix.SamplesMap.size());
    Tk = SMatrix.SamplesMap.size();
};

void THamNeuroSystem::IntYYPreCalculation()
{
	TWeightVector S;
	TSFloat Sum;
	TSFloat Res;

	IntY.clear();
	PrevIntY.clear();

        TUInt i,j;

	for (i=0; i<FloatY.size(); i++)
	{
		Sum = 0;
		for (j=0; j<FloatY.size(); j++)
			Sum += FloatY[j];

		Sum -= FloatY[i];	//В сумму входят все компоненты, кроме текущей i

		Res = Sum * E;
		Res = FloatY[i] - Res;
	
		S.push_back(Res);
	};

	for (i=0; i<S.size(); i++)
			IntY.push_back(F(S[i]));
};

bool THamNeuroSystem::MultipleSolution(TResultVector *Res)
{
	TSInt ResNumber;
	TUInt i;

	Res->clear();

	for (i=0; i<IntY.size(); i++)
	{
		if (IntY[i] != 0) 
		{
			ResNumber = IntY[i];
			break;
		}
	};

	for (i=0; i<IntY.size(); i++)
	{
		if (IntY[i] == ResNumber)
			Res->push_back(i);
		else
			if (IntY[i] != 0)
			{
				Res->clear();
				return false;
			}
	};

PrevIntY = IntY;
return true;
};

void THamNeuroSystem::CalcFloatYSums()
{
TSFloat Sum;
TSFloat Res;

FloatY.clear();
TUInt i,j;
	for (i=0; i<W.size(); i++)
	{
		Sum = 0;
		for (j=0; j<W[i].size(); j++)
			Sum += W[i][j] * EntryVectorX[j];

		Res = Sum + Tk;
		FloatY.push_back(Res);
	};
};

void THamNeuroSystem::CalcFloatYSumsEx()
{
TSFloat Sum;
TSFloat Res;
TSFloat CategoryKoeff;
	
FloatY.clear();
TUInt i,j;

	for (i=0; i<W.size(); i++)
	{
		CategoryKoeff = 0;
		Sum = 0;
		for (j=0; j<W[i].size(); j++)
		{
			Sum += W[i][j] * EntryVectorX[j] + (CategoryKoeff * EntryVectorX[j] * SMatrix.SamplesMap[i][j]);
			CategoryKoeff += 0.5;
		}

		Res = Sum + Tk;
		FloatY.push_back(Res);
	};
};

void THamNeuroSystem::Init()
{
	ClearAll();
};

void THamNeuroSystem::ClearW()
{
	for (TUInt i=0; i<W.size(); i++)
		W[i].clear();

	W.clear();
};

void THamNeuroSystem::ClearEntryVector()
{
	EntryVectorX.clear();
};

void THamNeuroSystem::ClearSMatrix()
{
	SMatrix.Clear();
};

void THamNeuroSystem::ClearFloatY()
{
	FloatY.clear();
};

void THamNeuroSystem::ClearAll()
{
	ClearW();
	ClearEntryVector();
	FloatY.clear();
	ClearSMatrix();
	Iteration = 0;
};

TSInt THamNeuroSystem::F(TSFloat X)
{
	if (X<=0) return 0;
return X;
};

void THamNeuroSystem::Step1_Initialize()
{
	ClearW();
	InitW();
	
	CalcKoefs();
	CalcFloatYSums();

	ClearW();

	IntYYPreCalculation();
};

void THamNeuroSystem::Step1_InitializeEx()
{
	ClearW();
	InitW();
	
	CalcKoefs();
	CalcFloatYSumsEx();

	ClearW();

	IntYYPreCalculation();
};

void THamNeuroSystem::Step2_SingleIteration()
{
	TWeightVector S;
	TSFloat Sum;
	TSFloat Res;

	PrevIntY = IntY;

	for (TUInt i=0; i<IntY.size(); i++)
	{
		Sum = 0;
		for (TUInt j=0; j<IntY.size(); j++)
			Sum += IntY[j];

		Sum -= IntY[i];	//В сумму входят все компоненты, кроме текущей i

		Res = Sum * E;
		Res = IntY[i] - Res;
	
		S.push_back(Res);
	};

	IntY.clear();

	for (TUInt i=0; i<S.size(); i++)
			IntY.push_back(F(S[i]));

Iteration++;
};

bool THamNeuroSystem::Step2_DoIterations(TSInt MaxIterations)
{
	while (Iteration<MaxIterations)
	{
		Step2_SingleIteration();

		if (Stabilized()) return true;
	};
return false;
};

bool THamNeuroSystem::Stabilized()
{
TResultVector Res;
	if (MultipleSolution(&Res)) return true;

	for (TUInt i=0; i<IntY.size(); i++)
		if (IntY[i] != PrevIntY[i]) return false;

return true;
};

bool THamNeuroSystem::DoAllSteps(TSInt MaxIterations)
{
        Step1_InitializeEx();
return  Step2_DoIterations(MaxIterations);
};

void THamNeuroSystem::Result(TResultVector *Res)
{
	MultipleSolution(Res);
};

TSInt THamNeuroSystem::ResultIndex()
{
TResultVector Res;
 if (MultipleSolution(&Res)) return Res[0];
return -1;
};


