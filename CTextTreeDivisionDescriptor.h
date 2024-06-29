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
#ifndef CTextTreeDivisionDescriptorH
#define CTextTreeDivisionDescriptorH
//---------------------------------------------------------------------------

#include "CCFDivisionTreeItem.h"
#include "CLogicalTextItem.h"
#include "CTextDivisionDescriptor.h"



    template <class LevelDataType, class CompositeUnitType> class TTextTreeDivisionDescriptor : public TTextDataProvider, public TTextDivisionDescriptor
    {
        public:

            class EInvalidSourceTextPointer {};

        private:
            TCFDivisionTreeItem<LevelDataType, CompositeUnitType> _Tree;

            TTextString         _SourceTextAlias;
            TLogicalTextItem  * _SourceText;

            TTextString         _DivisionName;


            TBool _IsValidSourceTextPointer()
            {
                if (_SourceText == NULL) return false;

                try
                {
                   TTextString SourceTextAlias = _SourceText->Alias();
                   if (SourceTextAlias != _SourceTextAlias) return false;
                }
                catch(...)
                {
                    return false;
                };
            return true;
            };

            TTextTreeDivisionDescriptor(){};

        public:


            TCFDivisionTreeItem<LevelDataType, CompositeUnitType> & Tree() { return _Tree; };

            TTextString         Alias() const { return _SourceTextAlias; };
            TLogicalTextItem  * LogicalTextItem(){ return _SourceText; };
            TTextString         Text() { return _SourceText->Text(); };
            TUInt               Length() { return _SourceText->Length(); };
            TTextString       * Data()   { return _SourceText->Data(); };

            TTextString  SubString(const TUInt & tIndex, const TUInt & tCount)  const { return _SourceText->SubString(tIndex, tCount); };

            TTextString  DivisionName() const { return _DivisionName; };
            void         DivisionName(const TTextString & tDivisionName) { _DivisionName = tDivisionName; };


            TTextTreeDivisionDescriptor(const TTextString & tDivisionName, const TTextString & tSourceTextAlias, TLogicalTextItem * tSourceText, TCFDivisionTreeItem<LevelDataType, CompositeUnitType> & tFirstTreeNode)
              : _DivisionName(tDivisionName), _SourceTextAlias(tSourceTextAlias), _SourceText(tSourceText), _Tree(tFirstTreeNode)
            {
                if (!_IsValidSourceTextPointer()) throw EInvalidSourceTextPointer();
            };

           ~TTextTreeDivisionDescriptor()
            {
                _Tree.~TTextDivisionItem<LevelDataType>();
            };
    };


/*

Пример возбуждения исключения EInvalidSourceTextPointer():

TRawDataItem p;
TLogicalTextItem v("", "", "", 124234, &p);
TTextDivisionItem<int> DivTree(1,188,0);

   TTextTreeDivisionDescriptor<int> Tree("", "dfsdf", &v, DivTree);

*/




#endif
 