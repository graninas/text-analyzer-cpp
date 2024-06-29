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
#include "GLFont.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#include "GLConstants.h"




           TGLBool TGLFont::IsInitialized() const { return _Initialized; };

           TGLUInt TGLFont::Base() const { return _Base; }

           void TGLFont::BuildFont(const TGLInt & tFontSize, const DWORD & tCharSetType, const char* tFontName,
             const DWORD & tBold, const DWORD & tItalic, const DWORD & tUnder, const DWORD & tStriked )
           {
           if (_Initialized) DeleteFont();
                _Base = glGenLists(256);

              _Font = CreateFont( tFontSize,
                    0,        // Ширина фонта
                    0,        // Угол отношения
                    0,        // Угол наклона
                    tBold,      // Ширина шрифта
                    tItalic,        // Курсив
                    tUnder,        // Подчеркивание
                    tStriked,        // Перечеркивание
                    tCharSetType,        // Идентификатор набора символов
                    OUT_TT_PRECIS,      // Точность вывода
                    CLIP_DEFAULT_PRECIS,    // Точность отсечения
                    ANTIALIASED_QUALITY,    // Качество вывода
                    FF_DONTCARE|DEFAULT_PITCH,  // Семейство и шаг
                    tFontName);      // Имя шрифта

           _Initialized = true;
           };

           void TGLFont::BuildFont(const TGLInt & tFontSize, const char* tFontName)
           {
           if (_Initialized) DeleteFont();
                _Base = glGenLists(256);

              _Font = CreateFont( tFontSize,
                    0,        // Ширина фонта
                    0,        // Угол отношения
                    0,        // Угол наклона
                    cDefaultFontBold,      // Ширина шрифта
                    cDefaultItalic,        // Курсив
                    cDefaultUnderline,        // Подчеркивание
                    cDefaultStriked,        // Перечеркивание
                    cDefaultCharSet,        // Идентификатор набора символов
                    OUT_TT_PRECIS,      // Точность вывода
                    CLIP_DEFAULT_PRECIS,    // Точность отсечения
                    ANTIALIASED_QUALITY,    // Качество вывода
                    FF_DONTCARE|DEFAULT_PITCH,  // Семейство и шаг
                    tFontName);      // Имя шрифта

           _Initialized = true;
           };

           TGLBool  TGLFont::SelectFont(const HDC & thDC)
           {
           if (!_Initialized) return false;
               if (!SelectObject(thDC, _Font)) return false;
           return wglUseFontBitmaps(thDC, 0, 256, _Base);
           };

           void  TGLFont::DeleteFont()
           {
           if (!_Initialized) return;

                glDeleteLists(_Base, 256);
                DeleteObject(_Font);
           _Initialized = false;
           };





