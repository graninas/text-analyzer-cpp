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
#ifndef VVCLViewH
#define VVCLViewH
//---------------------------------------------------------------------------


#include <vcl.h>
#include "CContainer.h"


typedef TControl * PControl;

     class TVCLView
     {
     private:

		typedef TContainer<PControl> TPControlsContainer;

        TPControlsContainer _Container;

     protected:

        TTextString  _Name;

     public:

        virtual TTextString Name() const { return _Name; };

        virtual void AddView(PControl tControl)
        {
            _Container.AddItem(tControl);
        };

        virtual void Update()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
           	_Container[i]->Update();

        };

        virtual void Enable()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
            	_Container[i]->Enabled = true;
                _Container[i]->Update();
            }
        };

        virtual void Disable()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
            	_Container[i]->Enabled = false;
                _Container[i]->Update();
            };
        };

        virtual void Show()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
            	_Container[i]->Show();
                _Container[i]->Update();
            }
        };

        virtual void Hide()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
            	_Container[i]->Hide();
                _Container[i]->Update();
            }
        };

        TVCLView(const TTextString & tName) : _Name(tName)
        {};

        ~TVCLView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

struct TVLCViewEqualKey
{
  bool operator()(TVCLView * tV1, TVCLView * tV2) const
  {
    return tV1->Name() == tV2->Name();
  }
};

struct TVCLViewLess
{
  bool operator()(TVCLView * tV1, TVCLView * tV2) const
  {
    return tV1->Name() < tV2->Name();
  }
};


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef TLabel * PLabel;

     class TVCLLabelsView : public TVCLView
     {
     private:

		typedef TContainer<PLabel> TPLabelsContainer;

        TPLabelsContainer _Container;

     public:

        virtual void SetCaption(const TTextString & tCaption)
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
               _Container[i]->Caption = tCaption;
               _Container[i]->Update();
            }
        };

        TVCLLabelsView(const TTextString & tLabelsViewName) : TVCLView(tLabelsViewName)
        {};

        ~TVCLLabelsView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////

typedef TPanel * PPanel;

     class TVCLPanelsView : public TVCLLabelsView
     {
     private:

		typedef TContainer<PPanel> TPPanelsContainer;

        TPPanelsContainer _Container;

     public:

        TVCLPanelsView(const TTextString & tPanelsViewName) : TVCLLabelsView(tPanelsViewName)
        {};

        ~TVCLPanelsView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////

typedef TCheckBox * PCheckBox;

     class TVCLCheckBoxesView : public TVCLLabelsView
     {
     private:

		typedef TContainer<PCheckBox> TPCheckBoxesContainer;

        TPCheckBoxesContainer _Container;

     public:

        virtual void CheckOn()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
               _Container[i]->Checked = true;
               _Container[i]->Update();
            }
        };

        virtual void CheckOff()
        {
            for (TUInt i=0; i<_Container.Count(); i++)
            {
               _Container[i]->Checked = false;
               _Container[i]->Update();
            }
        };

        TVCLCheckBoxesView(const TTextString & tCheckBoxesViewName) : TVCLLabelsView(tCheckBoxesViewName)
        {};

        ~TVCLCheckBoxesView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////

typedef TButton * PButton;

     class TVCLButtonsView : public TVCLLabelsView
     {
     private:

		typedef TContainer<PButton> TPButtonsContainer;

        TPButtonsContainer _Container;

     public:

        TVCLButtonsView(const TTextString & tButtonsViewName) : TVCLLabelsView(tButtonsViewName)
        {};

        ~TVCLButtonsView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////

typedef TListBox * PListBox;

     class TVCLListBoxesView : public TVCLView
     {
     private:

		typedef TContainer<PListBox> TPListBoxesContainer;

        TPListBoxesContainer _Container;

     public:

        virtual void SetList(TStrings * tStrings, const TUInt & tItemIndex)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
             	_Container[i]->Items = tStrings;
                _Container[i]->ItemIndex = tItemIndex;
                _Container[i]->Update();
            }
        };

        virtual void SetItemIndex(const TUInt & tItemIndex)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->ItemIndex = tItemIndex;
                _Container[i]->Update();
            }
        };

        virtual void ClearList()
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Items->Clear();
                _Container[i]->Update();
            }
        };

        virtual void AddItemToList(const AnsiString & tItem)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Items->Add(tItem);
                _Container[i]->Update();
            }
        };

        virtual void RemoveItemFromList(const AnsiString & tItem)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Items->Delete(_Container[i]->Items->IndexOf(tItem));
                _Container[i]->Update();
            }
        };

        virtual void RemoveItemFromList(const TUInt & tItemIndex)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Items->Delete(tItemIndex);
                _Container[i]->Update();
            }
        };

        TVCLListBoxesView(const TTextString & tListBoxesViewName) : TVCLView(tListBoxesViewName)
        {};

        ~TVCLListBoxesView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////

#include <CheckLst.hpp>
typedef TCheckListBox * PCheckListBox;

     class TVCLCheckListBoxesView : public TVCLListBoxesView
     {
     private:

		typedef TContainer<PCheckListBox> TPCheckListBoxesContainer;

        TPCheckListBoxesContainer _Container;

     public:

        virtual void CheckAllOn()
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                for (TSInt j=0; j<_Container[i]->Count; j++)
	                _Container[i]->Checked[j] = true;
            _Container[i]->Update();
            }
        };

        virtual void CheckAllOff()
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                for (TSInt j=0; j<_Container[i]->Count; j++)
	                _Container[i]->Checked[j] = false;
            _Container[i]->Update();
            }
        };

        virtual void CheckOn(const TUInt & tItemIndex)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Checked[tItemIndex] = true;
                _Container[i]->Update();
            }
        };

        virtual void CheckAllOff(const TUInt & tItemIndex)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Checked[tItemIndex] = false;
                _Container[i]->Update();
            }
        };

        TVCLCheckListBoxesView(const TTextString & tCheckListBoxesViewName) : TVCLListBoxesView(tCheckListBoxesViewName)
        {};

        ~TVCLCheckListBoxesView()
        {};
     };

////////////////////////////////////////////////////////////////////////////////

typedef TMemo * PMemo;

     class TVCLMemosView : public TVCLView
     {
     private:

		typedef TContainer<PMemo> TPMemosContainer;

        TPMemosContainer _Container;

     public:

        virtual void SetText(const AnsiString & tText)
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Text = tText;
                _Container[i]->Update();
            }
        };

        virtual void ClearText()
        {
        	for (TUInt i=0; i<_Container.Count(); i++)
            {
                _Container[i]->Text = "";
                _Container[i]->Update();
            }
        };

        TVCLMemosView(const TTextString & tMemosViewName) : TVCLView(tMemosViewName)
        {};

        ~TVCLMemosView()
        {};
     };

#endif
