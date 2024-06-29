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
#ifndef CTextsControllerH
#define CTextsControllerH
//---------------------------------------------------------------------------

#include "CRawDataContainer.h"
#include "CLogicalTextsContainer.h"
#include "CTextStringWrapper.h"
#include "CRawDataLoader.h"

#include "DTextsConfigurator.h"

#include "CTextStringList.h"

    class TTextsController
    {
        public:

            class EInvalidFormatString{};

        private:

            TRawDataContainer       _RawDataContainer;
            TLogicalTextsContainer  _LogicalTextContainer;
            TTextsConfigurator      _TextsConfigurator;

			TRawDataItem	   _RawDataItemDummy;
            TLogicalTextItem   _LogicalTextItemDummy;

            TLogicalTextItem * _PLogicalItem(const TTextString & tAlias);

        public:

            TRawDataContainer       * PRawDataContainer()     { return &_RawDataContainer; };
            TLogicalTextsContainer  * PLogicalTextContainer() { return &_LogicalTextContainer; };
            TTextsConfigurator      * PTextsConfigurator()    { return &_TextsConfigurator; };

            TBool  GetIndex(const TTextString & tAlias, TUInt * tIndex);

            TTextString         CurrentAlias() const;
            TSInt               CurrentIndex();
            TTextString			CurrentAuthor();
            TTextString			CurrentTitle();

            TTextString         KeyTextAlias() const;
            TSInt               KeyTextIndex();
            TTextString			KeyTextAuthor();
            TTextString			KeyTextTitle();
            TBool 			    KeyTextDefined() const;
            TTextDataProvider * KeyTextDataProvider();

            TTextString       * CurrentData();
            TTextString         CurrentText();
            TTextDataProvider * CurrentTextDataProvider();
            void SetCurrent(const TUInt & tIndex);
            void SetCurrent(const TTextString & tAlias);
            void SetActivated(const TUInt & tIndex, const TBool & tActivated);
        	void SetActivatedAll(const TBool & tActivated);

            TTextStringList   	AliasesList();

            TTextString       * Data(const TTextString & tAlias);
            TTextString         Text(const TTextString & tAlias);
            TTextDataProvider * TextDataProvider(const TTextString & tAlias);

            TBool   LoadText  (const TTextString & tFileName,      TRawDataLoader * tLoader, TTextString * tAlias);
            void    DeleteText(const TTextString & tAlias);
            void    DeleteCurrentText();
            void    DeleteKeyText();
			void    DeleteAllTexts();

            void    SetPrototypeTextAsKeyText(const TTextString & tAlias);
            void    SetKeyTextAsPrototypeText();

            TTextDataProvider * operator[](const TTextString & tAlias);

            void SetAuthorAndTitle(const TTextString & tAlias, const TTextString & tAuthor, const TTextString & tTitle);

            TUInt TextsCount()     const;
            TUInt ActivatedTextsCount();
            void  Clear();

            TTextsController();
           ~TTextsController();

    };

#endif
 