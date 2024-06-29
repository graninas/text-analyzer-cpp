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
#ifndef BFilteringSchemeH
#define BFilteringSchemeH
//---------------------------------------------------------------------------

#include "BFilteringCascade.h"


     class TFilteringScheme : public TErrorSpecificators
     {
         public:

             typedef vector<TFilteringCascade> TFilteringCascades;

         private:

             TFilteringCascades _Cascades;
             TUInt              _StartCascade;
             TUInt              _CurrentCascade;

             void _AddEmptyCascade() { _Cascades.push_back(TFilteringCascade()); }

         public:

                TUInt  StartCascade()   const { return _StartCascade; }
                TUInt  CurrentCascade() const { return _CurrentCascade; }


                TFilteringResult  Accept(const TCharsSet & tFilteringItem)
                {
                    if (_CurrentCascade >= _Cascades.size()) throw EOutOfRange();

                    return _Cascades[_CurrentCascade].Accept(tFilteringItem);
                };

                void   Define(const TUInt & tSubIndex, const TCharsSet & tCharsSet)
                {
                   for (TUInt i=0; i<_Cascades.size(); i++)
                       _Cascades[i].Define(tSubIndex, tCharsSet);
                };

                void   Transit(const TUInt & tCascade)
                {
                    if (tCascade >= _Cascades.size()) throw EOutOfRange();
                    _CurrentCascade = tCascade;
                };

                void Reset() { _CurrentCascade = _StartCascade; };



                
                inline TFilteringCascade & operator [] (const TUInt & tIndex)
                {
                    if (tIndex == _Cascades.size()) _AddEmptyCascade();
                    else
                       if (tIndex > _Cascades.size()) throw EOutOfRange();

                return _Cascades[tIndex];
                };

                

             void Clear() { _Cascades.clear(); }

             TFilteringScheme(const TUInt & tStartCascade) : _StartCascade(tStartCascade), _CurrentCascade(tStartCascade){};
            ~TFilteringScheme(){ Clear(); };

         private:

             TFilteringScheme(){};
     };


#endif
 