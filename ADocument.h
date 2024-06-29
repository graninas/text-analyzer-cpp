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
#ifndef ADocumentH
#define ADocumentH
//---------------------------------------------------------------------------

#include "APagesList.h"
#include "CTextDataProvider.h"
#include "APagesCompositor.h"

namespace ns_Document
{

   class TDocument : public TErrorSpecificators
   {
       private:

          TPagesList   _PagesList;

          TUInt        _CurrentPage;

          TTextDataProvider * _TextDataProvider;

          void _CheckOnInitialized() const
          {
              if (IsInitialized()) return;
          throw  ENotInitialized();
          }

       public:

           TBool IsInitialized() const { return (_TextDataProvider != NULL) ? true : false; }

           TPagesList & PagesList() { return _PagesList; };

           TRangeItem Range() { return TRangeItem(_PagesList.First().Range().From(), _PagesList.First().Range().To()); };

           TDocument & operator << (const ns_Page::TPage & tPage)
           {
              _PagesList << tPage;
           return *this;
           };

           TTextString  PageText(const TUInt & tIndex)
           {
               _CheckOnInitialized();
           return _TextDataProvider->SubString(_PagesList[tIndex].Range().From(), _PagesList[tIndex].Range().Length());
           };

           TTextString  CurrentPageText()
           {
               _CheckOnInitialized();
           return _TextDataProvider->SubString(_PagesList[_CurrentPage].Range().From(), _PagesList[_CurrentPage].Range().Length()); \
           };

           ns_Page::TPage & CurrentPage()  { return _PagesList[_CurrentPage]; };

           ns_Page::TPage * PCurrentPage()  { return &_PagesList[_CurrentPage]; };

           TUInt CurrentPageIndex() const  { return _CurrentPage; };

           void  NextPage()
           {
           if (!_PagesList.Count()) return;

              if  (_CurrentPage+1>=_PagesList.Count()) return;
           _CurrentPage++;
           };

           void  PrevPage()
           {
           if (!_PagesList.Count()) return;
              if  (_CurrentPage == 0) return;
           _CurrentPage--;
           };

           void  FirstPage()
           {
           if (!_PagesList.Count()) return;

           _CurrentPage = 0;
           };

           void  LastPage()
           {
              if (!_PagesList.Count()) return;

               _CurrentPage = _PagesList.Count()-1;
           };

           TBool PagesRange(const TSInt & tIndex, const TUInt & tCount, TRangeItem * tRange)
           {
               TUInt index = tIndex;
               TUInt count = tCount;
                  if (tIndex == -1)
                  {
                        index = 0;
                        count = 2;
                  };

              TRangeItem dummy;

                 if (_PagesList.IsValidIndex(index)) dummy = _PagesList[index].Range();
                 else return false;

              for (TUInt i=index+1; (i<count) && (i<_PagesList.Count()); i++)
                   dummy = dummy + _PagesList[i].Range();

           *tRange = dummy;
           return true;
           };

           TBool  PagesList(const TSInt & tIndex, const TUInt & tCount, TPagesList * tPagesList)
           {
               TUInt index = tIndex;
               TUInt count = tCount;
                  if (tIndex == -1)
                  {
                        index = 0;
                        count = 2;
                  };

              TPagesList dummy;
              for (TUInt i=index; (i<count) && (i<_PagesList.Count()); i++)
                dummy << _PagesList[i];

           *tPagesList = dummy;
           return true;
           }

           TBool PagesText(const TSInt & tIndex, const TUInt & tCount, TTextString * tString)
           {
              TRangeItem range;
               if (!PagesRange(tIndex, tCount, &range)) return false;
               if (!_TextDataProvider) return false;

               *tString = _TextDataProvider->SubString(range.From(), range.Count());
           return true;
           };

           void  SetCurrentPage(const TUInt & tCurrentPageIndex)
           {
               _CurrentPage = tCurrentPageIndex;
           };

           TTextString  Text() const
           {
               _CheckOnInitialized();
           return _TextDataProvider->Text();
           };

           TTextString *Data() const
           {
               _CheckOnInitialized();
           return _TextDataProvider->Data();
           };

           TTextDataProvider * TextDataProvider() const
           {
              _CheckOnInitialized();
           return _TextDataProvider;
           }

           TTextString operator[] (const TUInt & tIndex)
           {
              TTextString text = Text().SubString(_PagesList[tIndex].Range().From(), _PagesList[tIndex].Range().Length());
              return text;
           };


           TUInt Count()     const { return _PagesList.Count(); }
           void  Clear()  { _PagesList.Clear(); };


           void  Copmose(TPagesCompositor * tPagesCompositor) { _PagesList = tPagesCompositor->Compose(_TextDataProvider->Length()); };


           void  Init(TTextDataProvider * tTextDataProvider)
           {
               Clear();
               _TextDataProvider = tTextDataProvider;
           };

          TDocument() : _TextDataProvider(NULL), _CurrentPage(0){};

          TDocument(TTextDataProvider * tTextDataProvider)
          : _TextDataProvider(tTextDataProvider), _CurrentPage(0){};
         ~TDocument(){ Clear(); }
   };


}; //End of namespace;
#endif
 