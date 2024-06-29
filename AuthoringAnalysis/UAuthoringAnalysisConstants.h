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
#ifndef UAuthoringAnalysisConstantsH
#define UAuthoringAnalysisConstantsH
//---------------------------------------------------------------------------


#include "UTypes.h"

const TTextString cPreparingTextsStage		= "<--- Подготовка текстов --->";
const TTextString cPreparingTextsMessage 	= "Подготовка текстов к анализу...";

const TTextString cTreeMakingStage        	= "<--- Создание структуры --->";
const TTextString cTreeMakingMessage 		= "Построение структурного дерева текста...";

const TTextString cPrepareSamplesStage      = "<--- Подготовка образцов --->";
const TTextString cPrepareSamplesMessage 	= "Выборка образцов...";

const TTextString cCalculateFrequenciesStage    = "<--- Подсчет частот --->";
const TTextString cCalculateFrequenciesMessage 	= "Подсчет частотных характеристик символов...";

const TTextString cHamNSPreparingStage   	= "<--- Подготовка нейросистемы --->";
const TTextString cHamNSPreparingMessage 	= "Подготовка нейросистемы...";

const TTextString cHamNSComparingStage   	= "<--- Обработка данных --->";
const TTextString cHamNSComparingMessage 	= "Обработка данных нейросистемой Хэмминга...";

const TTextString cHamNSProcessingStage   	= "<--- Активация нейросистемы --->";
const TTextString cHamNSProcessingMessage 	= "Активация нейросистемы Хэмминга...";

const TTextString cDoneMessage = "Завершено.";

const TTextString cResultsMessageBorder = "<--------------------------------------------------->";
const TTextString cResultsMessageTitle  = "По результатам, полученным из нейросистемы, по трем уровням (предложения, абзацы, слова), походят нижеперечисленные тексты.";
const TTextString cResultsMessageLevelBody   = "Уровень:";
const TTextString cAnalysisFailure           = "...   К сожалению, нет ни одного результата.";


const TUInt cParagraphsLevel = 0;
const TUInt cSentencesLevel = 1;
const TUInt cWordsLevel 	= 2;

TTextString CLeveledMessage(const TUInt & tLevel)
{
	switch(tLevel)
    {
		case cParagraphsLevel: return """Абзацы""";
        case cSentencesLevel:  return """Предложения""";
        case cWordsLevel:	   return """Слова""";
    };
return "";
}

////////////////////////////////////////////////////////////////////////////////

const TUInt cNeuroSystemMaxIterations = 1000000;

const int bitZero   = 0x00;
const int bitOne    = 0x01;
const int bitTwo    = 0x02;
const int bitThree  = 0x04;
const int bitFour   = 0x08;
const int bitFive   = 0x10;
const int bitSix    = 0x20;
const int bitSeven  = 0x40;
const int bitEight  = 0x80;

#endif
 