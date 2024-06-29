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
#include "CTextsController.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


#include <algorithm>
#include <SysUtils.hpp>

#include "UConstants.h"



TLogicalTextItem * TTextsController::_PLogicalItem(const TTextString & tAlias)
{
TUInt index;
	if (!_LogicalTextContainer.GetIndex(tAlias, &index)) return &_LogicalTextItemDummy;
return   _LogicalTextContainer.PItem(tAlias);
};


     TTextStringList   TTextsController::AliasesList()
     {
     	return _RawDataContainer.AliasesList();
     };

     TBool  TTextsController::GetIndex(const TTextString & tAlias, TUInt * tIndex)
     {
          return _RawDataContainer.GetIndex(tAlias, tIndex);
     };

     TTextString TTextsController::CurrentAlias() const
     {
         return _TextsConfigurator.CurrentAlias();
     };

TSInt TTextsController::CurrentIndex()
{
TUInt index;
	if (!GetIndex(_TextsConfigurator.CurrentAlias(), &index)) return -1;
return index;
};

TTextString	TTextsController::CurrentAuthor() 
{
TTextString alias = _TextsConfigurator.CurrentAlias();
   	return _PLogicalItem(alias)->Author();
};

TTextString	TTextsController::CurrentTitle()
{
TTextString alias = _TextsConfigurator.CurrentAlias();
   	return _PLogicalItem(alias)->Title();
}

TTextString TTextsController::KeyTextAlias() const
{
    return _TextsConfigurator.KeyTextAlias();
};

TSInt TTextsController::KeyTextIndex()
{
TUInt index;
	if (!GetIndex(_TextsConfigurator.KeyTextAlias(), &index)) return -1;
return index;
};

TTextString	TTextsController::KeyTextAuthor()
{
TTextString alias = _TextsConfigurator.KeyTextAlias();
   	return _PLogicalItem(alias)->Author();
};

TTextString	TTextsController::KeyTextTitle()
{
TTextString alias = _TextsConfigurator.KeyTextAlias();
   	return _PLogicalItem(alias)->Title();
}

TBool TTextsController::KeyTextDefined() const
{
	return _TextsConfigurator.KeyTextDefined();
};

TTextDataProvider * TTextsController::KeyTextDataProvider()
{
if (KeyTextDefined())
	return  &_RawDataContainer.Item(KeyTextAlias());
return NULL;
};

     TTextString * TTextsController::CurrentData()
     {
         return _RawDataContainer.Data(_TextsConfigurator.CurrentAlias());
     };

     TTextString TTextsController::CurrentText()
     {
         return _RawDataContainer.Text(_TextsConfigurator.CurrentAlias());
     };

     TTextDataProvider * TTextsController::CurrentTextDataProvider()
     {
         return &_RawDataContainer.Item(_TextsConfigurator.CurrentAlias());
     };

     void TTextsController::SetCurrent(const TUInt & tIndex)
     {
     TTextString alias;
     	_RawDataContainer.GetAlias(tIndex, &alias);
	    _TextsConfigurator.SetCurrent(alias);
     };

     void TTextsController::SetCurrent(const TTextString & tAlias)
     {
     	 _TextsConfigurator.SetCurrent(tAlias);
     };

	void TTextsController::SetActivated(const TUInt & tIndex, const TBool & tActivated)
    {
     TTextString alias;
     	_RawDataContainer.GetAlias(tIndex, &alias);
        _TextsConfigurator.SetActivated(alias, tActivated);
    };

void TTextsController::SetActivatedAll(const TBool & tActivated)
{
    _TextsConfigurator.SetActivatedAll(tActivated);
};

     TTextString * TTextsController::Data(const TTextString & tAlias)
     {
         return _RawDataContainer.Data(tAlias);
     };

     TTextString   TTextsController::Text(const TTextString & tAlias)
     {
         return _RawDataContainer.Text(tAlias);
     };

     TTextDataProvider * TTextsController::TextDataProvider(const TTextString & tAlias)
     {
         return &_RawDataContainer.Item(tAlias);
     };

     TBool  TTextsController::LoadText(const TTextString & tFileName, TRawDataLoader * tLoader, TTextString * tAlias)
     {
     TUInt index;
        try
        {
        	TRawDataItem rdi(tLoader, tFileName);
            index = _RawDataContainer.AddItem(rdi);
            if (!_RawDataContainer.Unvirtualize(index)) return false;
        }
        catch(...)
        { return false; }

     *tAlias = _RawDataContainer[index].Alias();
     _LogicalTextContainer.AddItem(*tAlias, *tAlias, *tAlias, _RawDataContainer.PItem(*tAlias)->CRC(), _RawDataContainer.PItem(*tAlias));
     _TextsConfigurator.AddPrototype(_LogicalTextContainer.PItem(*tAlias), cDefaultTextActivation);

     return true;
     };

void TTextsController::DeleteKeyText()
{
	if (KeyTextDefined())
	{
    TTextString alias = KeyTextAlias();
		_RawDataContainer.DeleteItem(alias);
	    _LogicalTextContainer.DeleteItem(alias);
    	_TextsConfigurator.DeleteText(alias);
    }
};

void TTextsController::DeleteCurrentText()
{
    if (TextsCount())
		DeleteText(CurrentAlias());
};

void TTextsController::DeleteAllTexts()
{
	Clear();
};


void  TTextsController::DeleteText(const TTextString & tAlias)
{
	_RawDataContainer.DeleteItem(tAlias);
    _LogicalTextContainer.DeleteItem(tAlias);
    _TextsConfigurator.DeleteText(tAlias);
};

void  TTextsController::SetPrototypeTextAsKeyText(const TTextString & tAlias)
{
    _TextsConfigurator.SetPrototypeTextAsKeyText(tAlias);
};

void    TTextsController::SetKeyTextAsPrototypeText()
{
    _TextsConfigurator.SetKeyTextAsPrototypeText();
};

     TTextDataProvider * TTextsController::operator[](const TTextString & tAlias)
     {
         return _RawDataContainer.PItem(tAlias);
     };


     void TTextsController::SetAuthorAndTitle(const TTextString & tAlias, const TTextString & tAuthor, const TTextString & tTitle)
     {
        try
        {
           if (!_RawDataContainer.Count()) return;
            _LogicalTextContainer[tAlias].Author(tAuthor);
            _LogicalTextContainer[tAlias].Title(tTitle);
            _TextsConfigurator.UpdatePrototype(&_LogicalTextContainer[tAlias]);
        }
     catch (...)  { };
     };

     TUInt TTextsController::TextsCount() const
     {
         return _LogicalTextContainer.Count();
     };


     TUInt TTextsController::ActivatedTextsCount() 
     {
         return _TextsConfigurator.ActivatedTextsCount();
     };

     void TTextsController::Clear()
     {
         _LogicalTextContainer.Clear();
         _RawDataContainer.Clear();
         _TextsConfigurator.Clear();
     };


     TTextsController::TTextsController() 
		:   _LogicalTextItemDummy(TLogicalTextItem("", "", "", 0, &_RawDataItemDummy))
     {
     };

     TTextsController::~TTextsController()
     {
        Clear();
     };
