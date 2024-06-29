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
5 согласных  - Consonants

Правило плавной речи довольно-таки просто:
Если слово заканчивается кратким согласным (Д, Т, К, Г, Б, П), то следующее
за ним должно начинаться либо гласным (А, О, У, Ы, И, Э, Я, Ё, Ю, Е), либо
протяжным согласным (Р, Л, З, М, Н, С, Х, В, Ш, Щ, Ф, Ж, Ч). И наоборот, если
второе слово начинается с краткого гласного, то первое должно заканчиваться
гласным или согласным протяжным.
Столкновение в конце и начале слов кратких согласных затрудняет произношение.


Особое благозвучие достигается, когда слова соединяются гласными:

«У бабЫ-вдовЫ Умер ЕЁ ЕдинственныЙ двадцатилетниЙ сын, первыЙ нА селЕ работник.
БарынЯ, помещицА тогО самогО селА, Узнав О горЕ бабЫ, пошлА ЕЁ навесть в самыЙ день похорон.»
(И. Тургенев)


Полночною порою в болотной тиШи
Чуть слыШно, бесШумно ШурШат камыШи.

в промеЖутках соверШенной тиШины слыШен был Шорох
проШлогодних листьев, ШевеливШихся от таяния земли и от роста трав


МоРду Разбила кофейня,
ЗвеРьим кРиком боРима:
"отРазим кРовью игРы Рейна,
гРомами ядеР на мРамоР Рима".


В белом плаще с кровавым подбоем, шаркающей кавалерийской походкой,
ранним утром четырнадцатого числа месяца нисана в крытую колоннаду
между двумя крыльями дворца Ирода Великого вышел прокуратор Иудеи Понтий Пилат.


Все хорошо под сиянием лУнным.
ВсЮдУ родимУЮ Русь Узнаю.
Быстро лечУ я по рельсам чУгУнным,
Думаю дУмУ своЮ.

"Смерть бедного максима заставила меня призадУматься. Удивительно Умирает рУсский мУжик

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
   const TTextString cSameLettersContactDescription    = "(-3.0f) Одинаковые буквы на стыке слов";

   const cBriefContactValue          = -3.0f;
   const cBriefContactCriticalExcit  = 2;
   const cBriefContactInfluence      = 0;
   const TTextString cBriefContactDescription    = "(-3.0f) Краткие звуки (Д Т К Г Б П) на стыке слов.";

   const cAlternatingContactValue         = 5.0f;
   const cAlternatingContactCriticalExcit = 2;
   const cAlternatingContactInfluence     = 0;
   const TTextString cAlternatingContactDescription  = "(+5.0f) Чередование кратких (либо гласных) и длительных (либо гласных) звуков на стыке слов.";

   const cSameWordsBeginingValue          = -3.0f;
   const cSameWordsBeginingCriticalExcit  = 3;
   const cSameWordsBeginingInfluence      = 0;
   const TTextString cSameWordsBeginingDescription = "(-3.0f) Больше двух слов начинаются (оканчиваются) одинаковыми буквами.";

   const cDoublingDoublesValue          = -5.0f;
   const cDoublingDoublesCriticalExcit  = 2;
   const cDoublingDoublesInfluence      = 0;
   const TTextString cDoublingDoublesDescription = "(-5.0f) Повтор двухбуквенного сочетания.";

   const cDoublingTriplesValue          = -4.0f;
   const cDoublingTriplesCriticalExcit  = 2;
   const cDoublingTriplesInfluence      = 0;
   const TTextString cDoublingTriplesDescription = "(-4.0f) Повтор трехбуквенного сочетания.";

   const cConsonantsValue         = -10.0f;
   const cConsonantsCriticalExcit = 5;
   const cConsonantsInfluence     = 0;
   const TTextString cConsonantsDescription = "(-10.0f) Большое количество согласных подряд.";

   const cVowelsValue         = -6.0f;
   const cVowelsCriticalExcit = 4;
   const cVowelsInfluence     = 0;
   const TTextString cVowelsDescription = "(-6.0f) Большое количество гласных подряд.";

   const cHissValue         = -6.0f;
   const cHissCriticalExcit = 4;
   const cHissInfluence     = 40;
   const TTextString cHissDescription = "(-6.0f) Большое скопление свистящих звуков.";

   const cNoiseValue         = -6.0f;
   const cNoiseCriticalExcit = 5;
   const cNoiseInfluence     = 50;
   const TTextString cNoiseDescription = "(-6.0f) Большое скопление шипящих звуков.";


//(-) Одинаковые буквы на стыке слов.

    TRule   SameLettersContact()
    {
       TCharsFilter anyLetter("б", TCharsSet(cLetters));
       TCharsFilter notLetter("б", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("Б", TCharsSet(""));
       TCharsFilter defNotLetter("Б", TCharsSet(""),   cf_Negative);
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

//(-) Краткие звуки (Д Т К Г Б П) на стыке слов.

    TRule   BriefContact()
    {
       TCharsFilter anyLetter("б", TCharsSet(cLetters));
       TCharsFilter notLetter("б", TCharsSet(cLetters), cf_Negative);
       TCharsFilter brief("К", TCharsSet(cRusBrief));
       TCharsFilter notBrief("К", TCharsSet(cRusBrief),   cf_Negative);
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


//(+) Чередование кратких (либо гласных) и длительных (либо гласных) звуков на стыке слов.

    TRulesProxy   AlternatingContact()
    {
       TCharsFilter anyLetter("б", TCharsSet(cLetters));
       TCharsFilter notLetter("б", TCharsSet(cLetters), cf_Negative);
       TCharsFilter brief("К", TCharsSet(cRusBrief));
       TCharsFilter prolonged("Р", TCharsSet(cRusProlonged));
       TCharsFilter vowels("Г", TCharsSet(cRusVowels));
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
       TCharsFilter anyLetter("б", TCharsSet(cLetters));
       TCharsFilter notLetter("б", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("Б", TCharsSet(""));
       TCharsFilter defNotLetter("Б", TCharsSet(""),   cf_Negative);
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
       TCharsFilter anyLetter("б", TCharsSet(cLetters));
       TCharsFilter notLetter("б", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("Б", TCharsSet(""));
       TCharsFilter defNotLetter("Б", TCharsSet(""),   cf_Negative);
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
       TCharsFilter anyLetter("б", TCharsSet(cLetters));
       TCharsFilter notLetter("б", TCharsSet(cLetters), cf_Negative);
       TCharsFilter defLetter("Б", TCharsSet(""));
       TCharsFilter defNotLetter("Б", TCharsSet(""),   cf_Negative);
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
       TCharsFilter notletters("б", TCharsSet(cLetters),       cf_Negative);
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
       TCharsFilter vowels("Г", TCharsSet(cVowels));
       TCharsFilter notvowels("Г", TCharsSet(cVowels),         cf_Negative);
       TCharsFilter notletters("б", TCharsSet(cLetters),       cf_Negative);
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
       TCharsFilter hiss("Ц", TCharsSet(cRusHiss));
       TCharsFilter nothiss("Ц", TCharsSet(cRusHiss),          cf_Negative);
       TCharsFilter notletters("б", TCharsSet(cLetters),       cf_Negative);
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
       TCharsFilter noise("Ц", TCharsSet(cRusNoise));
       TCharsFilter notNoise("Ц", TCharsSet(cRusNoise),      cf_Negative);
       TCharsFilter notletters("б", TCharsSet(cLetters),       cf_Negative);
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
