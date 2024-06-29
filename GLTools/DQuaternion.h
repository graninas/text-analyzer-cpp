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
#ifndef DQuaternionH
#define DQuaternionH
//---------------------------------------------------------------------------

#include "GLTypes.h"
#include "math.h"

typedef TGLDouble TDQuaternion[4];

inline void QProduct(TDQuaternion tQ1, TDQuaternion tQ2, TDQuaternion tQRes)
{
TGLDouble w, x, y, z;
        w = tQ1[0]*tQ2[0] - tQ1[1]*tQ2[1] - tQ1[2]*tQ2[2] - tQ1[3]*tQ2[3];
        x = tQ1[0]*tQ2[1] + tQ1[1]*tQ2[0] + tQ1[2]*tQ2[3] - tQ1[3]*tQ2[2];
        y = tQ1[0]*tQ2[2] - tQ1[1]*tQ2[3] + tQ1[2]*tQ2[0] + tQ1[3]*tQ2[1];
        z = tQ1[0]*tQ2[3] + tQ1[1]*tQ2[2] - tQ1[2]*tQ2[1] + tQ1[3]*tQ2[0];

     tQRes[0] = w;
     tQRes[1] = x;
     tQRes[2] = y;
     tQRes[3] = z;
};




















#endif
 