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
#ifndef DTextsConfiguratorH
#define DTextsConfiguratorH
//---------------------------------------------------------------------------

#include <map>

#include "DTextConfiguration.h"

    class TTextsConfigurator
    {
	    public:

        	typedef map<TTextString, TTextConfiguration, less<TTextString> > TTextConfigurations;

            class EOutOfRange{};

        private:

           TTextConfigurations _TextConfigurations;
           TTextString	       _KeyTextAlias;
           TTextString		   _CurrentAlias;

           TUInt _LastIndex;

           TTextConfigurations::iterator _Iterator;


           void  _ReNewIndexes(const TUInt & tBegin, const TBool & tEnumerateKeyText);

           void  _AddText(TLogicalTextItem * tItem, const TUInt & tIndex);

           TTextConfigurations::iterator _DeleteText(const TTextString & tAlias);

           TUInt _Count() const;
           void  _Clear();

           TTextConfiguration  & _GetConfiguration(const TTextString & tAlias);

           TUInt _GetIndex();

           void  _SetCurrent(const TTextString & tAlias);
           void  _SetKeyText(const TTextString & tAlias);

        public:

           TTextConfigurations * PConfigurations();

           TTextConfigurations	 Configurations() ;
           void 				 SetConfigurations(const TTextConfigurations & tTextConfigurations);
           

           TBool IsExist(const TTextString & tAlias);

           void AddKeyText(TLogicalTextItem * tItem);
           void AddPrototype(TLogicalTextItem * tItem, const TBool & tActivated);
           void DeleteText(const TTextString & tAlias);

           void UpdatePrototype(TLogicalTextItem * tItem);
           void UpdatePrototype(TLogicalTextItem * tItem, const TBool & tActivated);

           void SetPrototypeTextAsKeyText(const TTextString & tAlias);
           void SetKeyTextAsPrototypeText();

           TLogicalTextItem * CurrentPrototype();
           TTextString 		  CurrentAlias() const;
           TLogicalTextItem * KeyText();
           TTextString 		  KeyTextAlias() const;
           TBool	          KeyTextDefined() const;

           TBool	IsActivated(const TTextString & tAlias);
           void		SetActivated(const TTextString & tAlias, const TBool & tActivated);
           void		SetActivatedAll(const TBool & tActivated);

           void		Activate(const TTextString & tAlias);
           void 	ActivateAll();
           void		DeActivate(const TTextString & tAlias);
           void     DeActivateAll();
           TUInt 	ActivatedTextsCount();

           TBool    IsKeyText(const TTextString & tAlias) ;
           TBool    IsPrototypeText(const TTextString & tAlias) ;

           TBool	SetCurrent(const TTextString & tAlias);

           void  	RemoveNotActivated();

           TTextConfiguration  & operator[](const TTextString tAlias);
           TTextsConfigurator ActiveTextsConfigurator();
           TUInt Count() const;
           void  Clear();


           TTextConfigurations::iterator ToBegin();
           TTextConfigurations::iterator ToEnd();

           TTextConfigurations::iterator Begin();
           TTextConfigurations::iterator End();

           TTextConfigurations::iterator Next();

           TTextsConfigurator() : _KeyTextAlias(""), _CurrentAlias(""), _LastIndex(0), _Iterator(_TextConfigurations.end()){};
           
    };


#endif
 