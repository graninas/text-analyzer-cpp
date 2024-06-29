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

const TTextString cPreparingTextsStage		= "<--- ���������� ������� --->";
const TTextString cPreparingTextsMessage 	= "���������� ������� � �������...";

const TTextString cTreeMakingStage        	= "<--- �������� ��������� --->";
const TTextString cTreeMakingMessage 		= "���������� ������������ ������ ������...";

const TTextString cPrepareSamplesStage      = "<--- ���������� �������� --->";
const TTextString cPrepareSamplesMessage 	= "������� ��������...";

const TTextString cCalculateFrequenciesStage    = "<--- ������� ������ --->";
const TTextString cCalculateFrequenciesMessage 	= "������� ��������� ������������� ��������...";

const TTextString cHamNSPreparingStage   	= "<--- ���������� ������������ --->";
const TTextString cHamNSPreparingMessage 	= "���������� ������������...";

const TTextString cHamNSComparingStage   	= "<--- ��������� ������ --->";
const TTextString cHamNSComparingMessage 	= "��������� ������ ������������� ��������...";

const TTextString cHamNSProcessingStage   	= "<--- ��������� ������������ --->";
const TTextString cHamNSProcessingMessage 	= "��������� ������������ ��������...";

const TTextString cDoneMessage = "���������.";

const TTextString cResultsMessageBorder = "<--------------------------------------------------->";
const TTextString cResultsMessageTitle  = "�� �����������, ���������� �� ������������, �� ���� ������� (�����������, ������, �����), ������� ����������������� ������.";
const TTextString cResultsMessageLevelBody   = "�������:";
const TTextString cAnalysisFailure           = "...   � ���������, ��� �� ������ ����������.";


const TUInt cParagraphsLevel = 0;
const TUInt cSentencesLevel = 1;
const TUInt cWordsLevel 	= 2;

TTextString CLeveledMessage(const TUInt & tLevel)
{
	switch(tLevel)
    {
		case cParagraphsLevel: return """������""";
        case cSentencesLevel:  return """�����������""";
        case cWordsLevel:	   return """�����""";
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
 