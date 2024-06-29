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
#ifndef CHamNeuroSystemH
#define CHamNeuroSystemH
//---------------------------------------------------------------------------

#include "CSamplesMatrix.h"

class THamNeuroSystem
{
private:

	void InitW();
	void CalcFloatYSums();
	void CalcFloatYSumsEx();
	void CalcKoefs();
	void IntYYPreCalculation();
	bool MultipleSolution(TResultVector *Res);

public:

	TSamplesMatrix SMatrix;
	TSFloat     E;              //Эпсилон для обратной связи.
	TSFloat     Tk;             //Коэффициент для расчета начальных весов.

	TSampleVector EntryVectorX;
	TWeightMatrix W;

	TYVector    FloatY;
	TYIntVector	IntY, PrevIntY;	//Целое выходное значение нейронов 2 слоя.

	TSInt Iteration;

	void  LoadEntryVector(TSampleVector aEntryVectorX);
	TUInt LoadSampleImage(TSampleVector aNewSampleImage);

	void Init();

	void ClearW();
	void ClearEntryVector();
	void ClearSMatrix();
	void ClearFloatY();
	void ClearAll();

	TSInt F(TSFloat X);		//Активационная функция.

	void Step1_Initialize();	//Обычная функция НС Хэмминга
	void Step1_InitializeEx();	//Улучшенная функция НС Хэмминга - учитывает не только совпадение битов, но и разрядность
	void Step2_SingleIteration();
	bool Step2_DoIterations(TSInt MaxIterations);
	bool Stabilized();

	bool DoAllSteps(TSInt MaxIterations);

	void  Result(TResultVector *Res);		//Все возможные решения
	TSInt ResultIndex();					//Первое решение


	THamNeuroSystem(){Init();};
	~THamNeuroSystem(){};
};





#endif
