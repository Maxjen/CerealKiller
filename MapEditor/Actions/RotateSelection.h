/*
    Copyright (c) 2012 Max Jensen <email>

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef CK_ROTATESELECTION_H
#define CK_ROTATESELECTION_H

#include "../../Action.h"
#include "../../Selection.h"
#include "../../Math/Vec2.h"

namespace ck {

class RotateSelection : public Action {
private:
    Selection* selection;
    Triangles* triangles;

    Vec2 rotationCenter;
    vector<int> verticesToRotate;
    vector<Vec2> startPositions;
    float angle;
public:
    RotateSelection(Selection* selection, Triangles* triangles);
    void setRotationAngle(float angle);
    Vec2 getRotationCenter();
    void apply();
    void revert();
};

}

#endif // CK_ROTATESELECTION_H
