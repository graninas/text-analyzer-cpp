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
#ifndef URulesH
#define URulesH
//---------------------------------------------------------------------------


#include "BRulesProxy.H"
#include "UConstants.h"


/*
5 ���������  - Consonants

������� ������� ���� ��������-���� ������:
���� ����� ������������� ������� ��������� (�, �, �, �, �, �), �� ���������
�� ��� ������ ���������� ���� ������� (�, �, �, �, �, �, �, �, �, �), ����
��������� ��������� (�, �, �, �, �, �, �, �, �, �, �, �, �). � ��������, ����
������ ����� ���������� � �������� ��������, �� ������ ������ �������������
������� ��� ��������� ���������.
������������ � ����� � ������ ���� ������� ��������� ���������� ������������.


������ ����������� �����������, ����� ����� ����������� ��������:

�� ����-����� ���� Ũ ������������ �������������� ���, ������ �� ���� ��������.
������, �������� ���� ������ ����, ����� � ���� ����, ����� Ũ ������� � ����� ���� �������.�
(�. ��������)


��������� ����� � �������� ����
���� ������, �������� ������ ������.

� ����������� ����������� ������ ������ ��� �����
������������ �������, ������������ �� ������ ����� � �� ����� ����


����� ������� �������,
������� ������ ������:
"������� ������ ���� �����,
������� ���� �� ������ ����".


� ����� ����� � �������� �������, ��������� ������������� ��������,
������ ����� �������������� ����� ������ ������ � ������ ���������
����� ����� �������� ������ ����� �������� ����� ���������� ����� ������ �����.


��� ������ ��� ������� ������.
����� ������� ���� �����.
������ ���� � �� ������� ��������,
����� ���� ����.

"������ ������� ������� ��������� ���� �������������. ����������� ������� ������� �����

*/

namespace ns_Rules
{
enum  TRulesEnumerator {re_SameLettersContact, re_BriefContact, re_AlternatingContact, re_SameWordsBegining, re_DoublingDoubles, re_DoublingTriples,
                        re_Consonants, re_Vowels, re_Hiss, re_Noise};

	const TTextString cForwardDescriptionPrefix		= "(F)";
	const TTextString cBackwardDescriptionPrefix	= "(B)";
    const TTextString cBothDirDescriptionPrefix		= "(FB)";


    TTextString CDirectionPrefix(const TRuleDirection & tDirection)
    {
    	switch(tDirection)
        {
        	case rd_Forward:	return cForwardDescriptionPrefix;
            case rd_Backward:   return cBackwardDescriptionPrefix;
        };
    return cBothDirDescriptionPrefix;
    };

   const cSameLettersContactValue          = -3.0f;
   const cSameLettersContactCriticalExcit  = 2;
   const cSameLettersContactInfluence      = 0;
   const TTextString cSameLettersContactDescription    = "(-3.0f) ���������� ����� �� ����� ����";

   const cBriefContactValue          = -3.0f;
   const cBriefContactCriticalExcit  = 2;
   const cBriefContactInfluence      = 0;
   const TTextString cBriefContactDescription    = "(-3.0f) ������� ����� (� � � � � �) �� ����� ����.";

   const cAlternatingContactValue         = 5.0f;
   const cAlternatingContactCriticalExcit = 2;
   const cAlternatingContactInfluence     = 0;
   const TTextString cAlternatingContactDescription  = "(+5.0f) ����������� ������� (���� �������) � ���������� (���� �������) ������ �� ����� ����.";

   const cSameWordsBeginingValue          = -3.0f;
   const cSameWordsBeginingCriticalExcit  = 3;
   const cSameWordsBeginingInfluence      = 0;
   const TTextString cSameWordsBeginingDescription = "(-3.0f) ������ ���� ���� ���������� (������������) ����������� �������.";

   const cDoublingDoublesValue          = -5.0f;
   const cDoublingDoublesCriticalExcit  = 2;
   const cDoublingDoublesInfluence      = 0;
   const TTextString cDoublingDoublesDescription = "(-5.0f) ������ �������������� ���������.";

   const cDoublingTriplesValue          = -4.0f;
   const cDoublingTriplesCriticalExcit  = 2;
   const cDoublingTriplesInfluence      = 0;
   const TTextString cDoublingTriplesDescription = "(-4.0f) ������ �������������� ���������.";

   const cConsonantsValue         = -10.0f;
   const cConsonantsCriticalExcit = 5;
   const cConsonantsInfluence     = 0;
   const TTextString cConsonantsDescription = "(-10.0f) ������� ���������� ��������� ������.";

   const cVowelsValue         = -6.0f;
   const cVowelsCriticalExcit = 4;
   const cVowelsInfluence     = 0;
   const TTextString cVowelsDescription = "(-6.0f) ������� ���������� ������� ������.";

   const cHissValue         = -6.0f;
   const cHissCriticalExcit = 4;
   const cHissInfluence     = 40;
   const TTextString cHissDescription = "(-6.0f) ������� ��������� ��������� ������.";

   const cNoiseValue         = -6.0f;
   const cNoiseCriticalExcit = 5;
   const cNoiseInfluence     = 50;
   const TTextString cNoiseDescription = "(-6.0f) ������� ��������� ������� ������.";


//(-) ���������� ����� �� ����� ����.

    TRule   SameLettersContact()
    {
       TCharsFilter anyLetter("�", TCharsSet(cLetters));
       TCharsFilter notLetter("�", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("�", TCharsSet(""));
       TCharsFilter defNotLetter("�", TCharsSet(""),   cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

          TFilteringScheme scheme(0);

          scheme[0] << anyLetter    << frm_Excit << frm_LinkDot << frm_Transit(1) << frm_Define(1);
          scheme[1] << notLetter    << frm_Transit(2)
                    << anyLetter    << frm_TimeBackReset
                    << EOT          << frm_EndProc;
          scheme[2] << notLetter    << frm_Skip
                    << defLetter    << cfm_Definitable(1) << frm_Excit << frm_LinkDot << frm_EndProc
                    << defNotLetter << cfm_Definitable(1) << frm_EndProc
                    << EOT          << frm_EndProc;

    return TRule("SameLettersContact", cSameLettersContactValue, re_SameLettersContact, rda_NotDifferential, rd_Forward, scheme,
                 cSameLettersContactCriticalExcit, cSameLettersContactInfluence, CDirectionPrefix(rd_Forward) + cSameLettersContactDescription);
    };

//(-) ������� ����� (� � � � � �) �� ����� ����.

    TRule   BriefContact()
    {
       TCharsFilter anyLetter("�", TCharsSet(cLetters));
       TCharsFilter notLetter("�", TCharsSet(cLetters), cf_Negative);
       TCharsFilter brief("�", TCharsSet(cRusBrief));
       TCharsFilter notBrief("�", TCharsSet(cRusBrief),   cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

          TFilteringScheme scheme(0);

          scheme[0] << brief     << frm_Excit << frm_LinkDot << frm_Transit(1);
          scheme[1] << notLetter << frm_Transit(2)
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;
          scheme[2] << notLetter << frm_Skip
                    << brief     << frm_Excit << frm_LinkDot << frm_EndProc
                    << notBrief  << frm_EndProc
                    << EOT       << frm_EndProc;

    return TRule("BriefContact", cBriefContactValue, re_BriefContact, rda_NotDifferential, rd_Forward, scheme,
                 cBriefContactCriticalExcit, cBriefContactInfluence, CDirectionPrefix(rd_Forward) + cBriefContactDescription);
    };


//(+) ����������� ������� (���� �������) � ���������� (���� �������) ������ �� ����� ����.

    TRulesProxy   AlternatingContact()
    {
       TCharsFilter anyLetter("�", TCharsSet(cLetters));
       TCharsFilter notLetter("�", TCharsSet(cLetters), cf_Negative);
       TCharsFilter brief("�", TCharsSet(cRusBrief));
       TCharsFilter prolonged("�", TCharsSet(cRusProlonged));
       TCharsFilter vowels("�", TCharsSet(cRusVowels));
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

          TFilteringScheme scheme(0);
          TRulesProxy      proxy;

          scheme[0] << brief     << frm_Excit << frm_LinkDot << frm_Transit(1);
          scheme[1] << notLetter << frm_Transit(2)
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;
          scheme[2] << notLetter << frm_Skip
                    << prolonged << frm_Excit << frm_LinkDot << frm_EndProc
                    << vowels    << frm_Excit << frm_LinkDot << frm_EndProc
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;

          proxy << TRule("AlternatingContactBrief", cAlternatingContactValue, re_AlternatingContact, rda_NotDifferential, rd_Forward, scheme,
                 cAlternatingContactCriticalExcit, cAlternatingContactInfluence, CDirectionPrefix(rd_Forward) + cAlternatingContactDescription);

          scheme.Clear();

          scheme[0] << prolonged << frm_Excit << frm_LinkDot << frm_Transit(1);
          scheme[1] << notLetter << frm_Transit(2)
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;
          scheme[2] << notLetter << frm_Skip
                    << brief     << frm_Excit << frm_LinkDot << frm_EndProc
                    << vowels    << frm_Excit << frm_LinkDot << frm_EndProc
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;

          proxy << TRule("AlternatingContactProlonged", cAlternatingContactValue, re_AlternatingContact, rda_NotDifferential, rd_Forward, scheme,
                 cAlternatingContactCriticalExcit, cAlternatingContactInfluence, CDirectionPrefix(rd_Forward) + cAlternatingContactDescription);

          scheme.Clear();

          scheme[0] << vowels    << frm_Excit << frm_LinkDot << frm_Transit(1);
          scheme[1] << notLetter << frm_Transit(2)
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;
          scheme[2] << notLetter << frm_Skip
                    << brief     << frm_Excit << frm_LinkDot << frm_EndProc
                    << prolonged << frm_Excit << frm_LinkDot << frm_EndProc
                    << anyLetter << frm_TimeBackReset
                    << EOT       << frm_EndProc;

          proxy << TRule("AlternatingContactVowels", cAlternatingContactValue, re_AlternatingContact, rda_NotDifferential, rd_Forward, scheme,
                 cAlternatingContactCriticalExcit, cAlternatingContactInfluence, CDirectionPrefix(rd_Forward) + cAlternatingContactDescription);

    return proxy;
    };

    TRule   SameWordsBegining(const TRuleDirection & tDirection)
    {
       TCharsFilter anyLetter("�", TCharsSet(cLetters));
       TCharsFilter notLetter("�", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("�", TCharsSet(""));
       TCharsFilter defNotLetter("�", TCharsSet(""),   cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

          TFilteringScheme scheme(0);

          scheme[0] << anyLetter << frm_Excit << frm_LinkDot << frm_Transit(1) << frm_Define(1);
          scheme[1] << anyLetter << frm_Skip
                    << notLetter << frm_Transit(2)
                    << EOT       << frm_EndProc;
          scheme[2] << defLetter << cfm_Definitable(1) << frm_Excit << frm_LinkDot << frm_Transit(1)
                    << notLetter << frm_Skip
                    << defNotLetter << frm_EndProc << frm_TimeBackReset
                    << EOT       << frm_EndProc;

    return TRule("SameWordsBegining", cSameWordsBeginingValue, re_SameWordsBegining,
                 rda_NotDifferential, tDirection, scheme, cSameWordsBeginingCriticalExcit,
                 cSameWordsBeginingInfluence, CDirectionPrefix(tDirection) + cSameWordsBeginingDescription);
    };


    TRule   DoublingDoubles(const TRuleDirection & tDirection)
    {
       TCharsFilter anyLetter("�", TCharsSet(cLetters));
       TCharsFilter notLetter("�", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("�", TCharsSet(""));
       TCharsFilter defNotLetter("�", TCharsSet(""),   cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

          TFilteringScheme scheme(0);

          scheme[0] << anyLetter << frm_Excit << frm_LinkDot << frm_Transit(1) << frm_Define(1);
          scheme[1] << anyLetter << frm_Define(2) << frm_LinkDot << frm_Transit(2)
                    << notLetter << frm_Skip
                    << EOT       << frm_EndProc;

          scheme[2] << notLetter << frm_Skip
                    << defLetter << cfm_Definitable(1) << frm_LinkDot << frm_Transit(3)
                    << defNotLetter << cfm_Definitable(1) << frm_EndProc
                    << EOT       << frm_EndProc;

          scheme[3] << notLetter << frm_Skip
                    << defLetter << cfm_Definitable(2) << frm_Excit << frm_LinkDot << frm_Transit(2)
                    << defNotLetter << cfm_Definitable(2) << frm_EndProc
                    << EOT       << frm_EndProc;

    return TRule("DoublingDoubles", cDoublingDoublesValue, re_DoublingDoubles, rda_NotDifferential, tDirection,
                 scheme, cDoublingDoublesCriticalExcit, cDoublingDoublesInfluence, CDirectionPrefix(tDirection) + cDoublingDoublesDescription);
    };

    TRule   DoublingTriples(const TRuleDirection & tDirection)
    {
       TCharsFilter anyLetter("�", TCharsSet(cLetters));
       TCharsFilter notLetter("�", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("�", TCharsSet(""));
       TCharsFilter defNotLetter("�", TCharsSet(""),   cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

          TFilteringScheme scheme(0);

          scheme[0] << anyLetter << frm_Excit << frm_LinkDot << frm_Transit(1) << frm_Define(1);
          scheme[1] << anyLetter << frm_Define(2) << frm_LinkDot << frm_Transit(2)
                    << notLetter << frm_Skip
                    << EOT       << frm_EndProc;

          scheme[2] << anyLetter << frm_Define(3) << frm_LinkDot << frm_Transit(3)
                    << notLetter << frm_Skip
                    << EOT       << frm_EndProc;

          scheme[3] << notLetter << frm_Skip
                    << defLetter << cfm_Definitable(1) << frm_LinkDot << frm_Transit(4)
                    << defNotLetter << cfm_Definitable(1) << frm_EndProc
                    << EOT       << frm_EndProc;

          scheme[4] << notLetter << frm_Skip
                    << defLetter << cfm_Definitable(2) << frm_LinkDot << frm_Transit(5)
                    << defNotLetter << cfm_Definitable(2) << frm_EndProc
                    << EOT       << frm_EndProc;

          scheme[5] << notLetter << frm_Skip
                    << defLetter << cfm_Definitable(3) << frm_Excit << frm_LinkDot << frm_Transit(3)
                    << defNotLetter << cfm_Definitable(3) << frm_EndProc
                    << EOT       << frm_EndProc;

    return TRule("DoublingTriples", cDoublingTriplesValue, re_DoublingTriples, rda_NotDifferential, tDirection,
                 scheme, cDoublingTriplesCriticalExcit, cDoublingTriplesInfluence, CDirectionPrefix(tDirection) + cDoublingTriplesDescription);
    };


    TRule   Consonants()
    {
       TCharsFilter consonants("C", TCharsSet(cConsonants));
       TCharsFilter notconsonants("C", TCharsSet(cConsonants), cf_Negative);
       TCharsFilter notletters("�", TCharsSet(cLetters),       cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

       TFilteringScheme scheme(0);


          scheme[0] << consonants    << (TFilteringResult() << frm_Excit << frm_LinkDot << frm_Transit(1));
          scheme[1] << notletters    << (TFilteringResult() << frm_Skip)
                    << consonants    << (TFilteringResult() << frm_Excit << frm_LinkDot)
                    << notconsonants << (TFilteringResult() << frm_Reset << frm_EndProc)
                    << EOT           << (TFilteringResult() << frm_EndProc);

        return TRule("Consonants", cConsonantsValue, re_Consonants, rda_NotDifferential, rd_Forward, scheme,
                      cConsonantsCriticalExcit, cConsonantsInfluence, CDirectionPrefix(rd_Forward) + cConsonantsDescription);
    };

    TRule   Vowels()
    {
       TCharsFilter vowels("�", TCharsSet(cVowels));
       TCharsFilter notvowels("�", TCharsSet(cVowels),         cf_Negative);
       TCharsFilter notletters("�", TCharsSet(cLetters),       cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

       TFilteringScheme scheme(0);


          scheme[0] << vowels     << (TFilteringResult() << frm_Excit << frm_LinkDot << frm_Transit(1));
          scheme[1] << notletters << (TFilteringResult() << frm_Skip)
                    << vowels     << (TFilteringResult() << frm_Excit << frm_LinkDot)
                    << notvowels  << (TFilteringResult() << frm_Reset << frm_EndProc)
                    << EOT        << (TFilteringResult() << frm_EndProc);

        return TRule("Vowels", cVowelsValue, re_Vowels, rda_NotDifferential, rd_Forward, scheme, cVowelsCriticalExcit,
                      cVowelsInfluence, CDirectionPrefix(rd_Forward) + cVowelsDescription);
    };


    TRule   Hiss()
    {
       TCharsFilter hiss("�", TCharsSet(cRusHiss));
       TCharsFilter nothiss("�", TCharsSet(cRusHiss),          cf_Negative);
       TCharsFilter notletters("�", TCharsSet(cLetters),       cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

       TFilteringScheme scheme(0);

          scheme[0] << hiss       << (TFilteringResult() << frm_Excit << frm_LinkDot << frm_Transit(1));
          scheme[1] << notletters << (TFilteringResult() << frm_Skip)
                    << hiss       << (TFilteringResult() << frm_Excit << frm_LinkDot)
                    << nothiss    << (TFilteringResult() << frm_Skip)
                    << EOT        << (TFilteringResult() << frm_EndProc);

       return TRule("Hiss", cHissValue, re_Hiss, rda_Differential, rd_Forward, scheme, cHissCriticalExcit,
                     cHissInfluence, CDirectionPrefix(rd_Forward) + cHissDescription);
    };

    TRule   Noise()
    {
       TCharsFilter noise("�", TCharsSet(cRusNoise));
       TCharsFilter notNoise("�", TCharsSet(cRusNoise),      cf_Negative);
       TCharsFilter notletters("�", TCharsSet(cLetters),       cf_Negative);
       TCharsFilter EOT("EOT", TCharsSet(CTextStringEndSign),  cf_Positive);

       TFilteringScheme scheme(0);

          scheme[0] << noise       << (TFilteringResult() << frm_Excit << frm_LinkDot << frm_Transit(1));
          scheme[1] << notletters  << (TFilteringResult() << frm_Skip)
                    << noise       << (TFilteringResult() << frm_Excit << frm_LinkDot)
                    << notNoise    << (TFilteringResult() << frm_Skip)
                    << EOT         << (TFilteringResult() << frm_EndProc);

       return TRule("Noise", cNoiseValue, re_Noise, rda_Differential, rd_Forward, scheme, cNoiseCriticalExcit,
                     cNoiseInfluence, CDirectionPrefix(rd_Forward) + cNoiseDescription);
    };

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------


	TRulesProxy Rules()
    {
    TRulesProxy proxy;
		proxy	<< SameLettersContact()
                << BriefContact()
                << AlternatingContact()
                << SameWordsBegining(rd_Forward) << SameWordsBegining(rd_Backward)
                << DoublingDoubles(rd_Forward) << DoublingTriples(rd_Backward)
                << DoublingTriples(rd_Forward) << DoublingTriples(rd_Backward)
                << Consonants()
                << Vowels()
                << Hiss()
                << Noise();

    return proxy;
    };




};
#endif
