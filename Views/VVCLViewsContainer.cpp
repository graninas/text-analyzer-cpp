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
#include "VVCLViewsContainer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

        void TVCLViewsContainer::AddViewsGroup(const TTextString & tViewsGroupName)
        {
             TPVCLView pView = new TVCLView(tViewsGroupName);
	         typedef TPVCLViewsMap::value_type value_type;

            _ViewsMap.insert(value_type(tViewsGroupName, pView));
        };

        TVCLView * TVCLViewsContainer::PViewGroup(const TTextString & tViewsGroupName)
        {
             return _ViewsMap[tViewsGroupName];
        }

        void TVCLViewsContainer::AddView(const TTextString & tViewsGroupName, PControl pCotrol)
        {
             _ViewsMap[tViewsGroupName]->AddView(pCotrol);
        };

        void TVCLViewsContainer::UpdateGroup(const TTextString & tViewsGroupName)
        {
             _ViewsMap[tViewsGroupName]->Update();
        };

        void TVCLViewsContainer::EnableGroup(const TTextString & tViewsGroupName)
        {
             _ViewsMap[tViewsGroupName]->Enable();
        };

        void TVCLViewsContainer::DisableGroup(const TTextString & tViewsGroupName)
        {
             _ViewsMap[tViewsGroupName]->Disable();
        };

        void TVCLViewsContainer::ShowGroup(const TTextString & tViewsGroupName)
        {
             _ViewsMap[tViewsGroupName]->Show();
        };

        void TVCLViewsContainer::HideGroup(const TTextString & tViewsGroupName)
        {
             _ViewsMap[tViewsGroupName]->Hide();
        };

        void TVCLViewsContainer::Clear()
        {
             TPVCLViewsMap::iterator iter = _ViewsMap.begin();

             while ((iter++) != _ViewsMap.end())
                  delete (*iter).second;

        _ViewsMap.clear();
        }


         TVCLViewsContainer::TVCLViewsContainer() {};
        TVCLViewsContainer::~TVCLViewsContainer()
        {
        	Clear();
        };