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
#include "DTextsConfigurator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include <algorithm>

void  TTextsConfigurator::_AddText(TLogicalTextItem * tItem, const TUInt & tIndex)
{
typedef  TTextConfigurations::value_type value_type;

    _TextConfigurations.insert(value_type(tItem->Alias(), TTextConfiguration(tItem, true, tIndex)));

    _Iterator = _TextConfigurations.begin();
};

TTextsConfigurator::TTextConfigurations::iterator TTextsConfigurator::_DeleteText(const TTextString & tAlias)
{
	TTextConfigurations::iterator iter = _TextConfigurations.find(tAlias);
    _TextConfigurations.erase(iter);
return iter;
};

TUInt TTextsConfigurator::_Count() const
{
     return _TextConfigurations.size();
}

void TTextsConfigurator::_Clear()
{
    _TextConfigurations.clear();
};

TTextConfiguration & TTextsConfigurator::_GetConfiguration(const TTextString & tAlias)
{
if (!IsExist(tAlias)) throw EOutOfRange();
    return _TextConfigurations[tAlias];
};

TUInt TTextsConfigurator::_GetIndex()
{
     _LastIndex++;
return _LastIndex;
};

void TTextsConfigurator::_ReNewIndexes(const TUInt & tBegin, const TBool & tEnumerateKeyText)
{
TTextConfigurations::iterator iter = _TextConfigurations.begin();

TUInt index = tBegin;

if (tEnumerateKeyText)
     while (iter != _TextConfigurations.end())
     {
         (*iter).second.Index(index++);
     iter++;
     }
else
	while (iter != _TextConfigurations.end())
    {
    	if ((*iter).second.PLogicalTextItem()->Alias() != _KeyTextAlias)
        (*iter).second.Index(index++);
    iter++;
    };
};

void TTextsConfigurator::_SetCurrent(const TTextString & tAlias)
{
	_CurrentAlias = tAlias;
};

void TTextsConfigurator::_SetKeyText(const TTextString & tAlias)
{
    _KeyTextAlias = tAlias;
};

TBool TTextsConfigurator::IsExist(const TTextString & tAlias)
{
TTextConfigurations::iterator iter = _TextConfigurations.find(tAlias);
   	if (iter == _TextConfigurations.end()) return false;
return true;
};

void TTextsConfigurator::AddKeyText(TLogicalTextItem * tItem)
{
	_AddText(tItem, _GetIndex());
    _SetKeyText(tItem->Alias());
    _SetCurrent(tItem->Alias());
};

void TTextsConfigurator::AddPrototype(TLogicalTextItem * tItem, const TBool & tActivated)
{
	_AddText(tItem, _GetIndex());
    _SetCurrent(tItem->Alias());
};

void TTextsConfigurator::UpdatePrototype(TLogicalTextItem * tItem)
{
    _TextConfigurations[tItem->Alias()].PLogicalTextItem(tItem);
};

void TTextsConfigurator::UpdatePrototype(TLogicalTextItem * tItem, const TBool & tActivated)
{
    _TextConfigurations[tItem->Alias()].PLogicalTextItem(tItem);
    _TextConfigurations[tItem->Alias()].SetActivated(tActivated);
};

void TTextsConfigurator::DeleteText(const TTextString & tAlias)
{
TTextConfigurations::iterator iter = _DeleteText(tAlias);
    if (iter == _TextConfigurations.end()) 	_SetCurrent("");
	else
        	_SetCurrent(ToBegin()->first);

	if (tAlias == _KeyTextAlias) _KeyTextAlias = "";
};

void TTextsConfigurator::SetPrototypeTextAsKeyText(const TTextString & tAlias)
{
TTextConfigurations::iterator iter = _TextConfigurations.find(tAlias);
   	if (iter == _TextConfigurations.end()) return;
    if (!(*iter).second.IsActivated())     return;

	_SetKeyText(tAlias);
};

void TTextsConfigurator::SetKeyTextAsPrototypeText()
{
    _SetKeyText("");
};

TLogicalTextItem * TTextsConfigurator::CurrentPrototype()
{
    if (!IsExist(_CurrentAlias)) return NULL;
return _TextConfigurations[_CurrentAlias].PLogicalTextItem();
};

TTextString TTextsConfigurator::CurrentAlias() const
{
    return _CurrentAlias;
};

TLogicalTextItem * TTextsConfigurator::KeyText()
{
    if (!IsExist(_KeyTextAlias)) return NULL;
return _TextConfigurations[_KeyTextAlias].PLogicalTextItem();
};

TTextString TTextsConfigurator::KeyTextAlias() const
{
	return _KeyTextAlias;
};

TBool  TTextsConfigurator::KeyTextDefined() const
{
    return (_KeyTextAlias != "");
};

TBool TTextsConfigurator::IsActivated(const TTextString & tAlias)
{
    if (!IsExist(tAlias)) return false;
return   _TextConfigurations[tAlias].IsActivated();
};

void TTextsConfigurator::SetActivated(const TTextString & tAlias, const TBool & tActivated)
{
    if (!IsExist(tAlias)) return;
    if ((!tActivated) && (tAlias == _KeyTextAlias))
    {
    	_SetKeyText("");
        _TextConfigurations[tAlias].DeActivate();
    return;
    };

_TextConfigurations[tAlias].SetActivated(tActivated);
};

void TTextsConfigurator::SetActivatedAll(const TBool & tActivated)
{
TTextConfigurations::iterator iter = _TextConfigurations.begin();
    while (iter != _TextConfigurations.end())
    {
        SetActivated((*iter).first, tActivated);
    iter++;
    };
};

void  TTextsConfigurator::Activate(const TTextString & tAlias)
{
    if (!IsExist(tAlias)) return;
_TextConfigurations[tAlias].Activate();
};

void TTextsConfigurator::ActivateAll()
{
	TTextConfigurations::iterator iter = _TextConfigurations.begin();
    while (iter != _TextConfigurations.end())
    {
		(*iter).second.Activate();
    iter++;
    };
};

void  TTextsConfigurator::DeActivate(const TTextString & tAlias)
{
    if (!IsExist(tAlias)) return;
    if (tAlias == _KeyTextAlias) _SetKeyText(tAlias);

_TextConfigurations[tAlias].DeActivate();
};

void TTextsConfigurator::DeActivateAll()
{
	TTextConfigurations::iterator iter = _TextConfigurations.begin();
    while (iter != _TextConfigurations.end())
    {
		(*iter).second.DeActivate();
    iter++;
    };
};

TUInt  TTextsConfigurator::ActivatedTextsCount()
{
TTextConfigurations::iterator iter = _TextConfigurations.begin();

	TUInt activeCount = 0;

    	while (iter != _TextConfigurations.end())
        {
        	if ((*iter).second.IsActivated())
            	activeCount++;
        iter++;
        }
return activeCount;
};

TBool TTextsConfigurator::IsKeyText(const TTextString & tAlias)
{
    return (tAlias == _KeyTextAlias);
};

TBool TTextsConfigurator::IsPrototypeText(const TTextString & tAlias)
{
    return (IsExist(tAlias) && (tAlias != _KeyTextAlias));
};

TTextsConfigurator::TTextConfigurations * TTextsConfigurator::PConfigurations()
{
    return &_TextConfigurations;
};       

TTextsConfigurator::TTextConfigurations	 TTextsConfigurator::Configurations()
{
	return _TextConfigurations;
};

void TTextsConfigurator::SetConfigurations(const TTextConfigurations & tTextConfigurations)
{
	_TextConfigurations = tTextConfigurations;
};

TBool TTextsConfigurator::SetCurrent(const TTextString & tAlias)
{
    if (!IsExist(tAlias)) return false;
    _SetCurrent(tAlias);
return true;
};

void TTextsConfigurator::RemoveNotActivated()
{
TTextConfigurations::iterator iter = _TextConfigurations.begin();

	while (iter != _TextConfigurations.end())
    {
        if (!(*iter).second.IsActivated())
        {
        	_TextConfigurations.erase(iter);
            iter = _TextConfigurations.begin();		//“ака€ конструкци€ потому, что € не уверен, что итератор можно использовать повторно после удалени€ элемента.
        }
        else iter++;
    };
};

TTextConfiguration & TTextsConfigurator::operator[](const TTextString tAlias)
{
    return _GetConfiguration(tAlias);
};

TUInt TTextsConfigurator::Count() const
{
     return _Count();
}

void TTextsConfigurator::Clear()
{
    _Clear();
    _KeyTextAlias = "";
    _CurrentAlias = "";
    _LastIndex = 0;
};

TTextsConfigurator::TTextConfigurations::iterator TTextsConfigurator::ToBegin()
{
	_Iterator = _TextConfigurations.begin();
return _Iterator;
};

TTextsConfigurator::TTextConfigurations::iterator TTextsConfigurator::ToEnd()
{
	_Iterator = _TextConfigurations.end();
return _Iterator;
};

TTextsConfigurator::TTextConfigurations::iterator TTextsConfigurator::Begin()
{
    return _TextConfigurations.begin();
};

TTextsConfigurator::TTextConfigurations::iterator TTextsConfigurator::End()
{
	return _TextConfigurations.end();
};

TTextsConfigurator::TTextConfigurations::iterator TTextsConfigurator::Next()
{
    if (_Iterator != _TextConfigurations.end()) _Iterator++;
return _Iterator;
};


