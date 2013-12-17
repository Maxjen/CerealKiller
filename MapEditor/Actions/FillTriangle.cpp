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

#include "FillTriangle.h"

namespace ck {

FillTriangle::FillTriangle(Selection* selection, Triangles* triangles, int v1, int v2, int v3) {
    this->triangles = triangles;
    this->selection = selection;
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    firstApply = true;
}

void FillTriangle::apply() {
    selection->selectVertex(v1);
    selection->selectVertex(v2);
    selection->selectVertex(v3);
    if (firstApply) {
        t = triangles->addTriangle(v1, v2, v3, "Textures/Fault Zone.png");
        firstApply = false;
    }
    else {
        triangles->restoreTriangle(t);
    }
    selection->selectVertex(v1);
    selection->selectVertex(v2);
    selection->selectVertex(v3);
}

void FillTriangle::revert() {
    selection->selectVertex(v1);
    selection->selectVertex(v2);
    selection->selectVertex(v3);
    triangles->removeTriangle(t);
    selection->selectVertex(v1);
    selection->selectVertex(v2);
    selection->selectVertex(v3);
}

}
