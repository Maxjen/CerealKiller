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

#include "CreateTriangle.h"

namespace ck {

CreateTriangle::CreateTriangle(Selection* selection, Triangles* triangles) {
    this->selection = selection;
    this->triangles = triangles;

    firstApply = true;
}

void CreateTriangle::setV1Position(float x, float y) {
    v1Position = Vec2(x, y);
}

void CreateTriangle::setV2Position(float x, float y) {
    v2Position = Vec2(x, y);
}

void CreateTriangle::setV3Position(float x, float y) {
    v3Position = Vec2(x, y);
}

void CreateTriangle::apply() {
    if (firstApply) {
        v1 = triangles->addVertex(v1Position.x, v1Position.y, v1Position.x/256, -v1Position.y/256, 255, 255, 255, 255);
        v2 = triangles->addVertex(v2Position.x, v2Position.y, v2Position.x/256, -v2Position.y/256, 255, 255, 255, 255);
        v3 = triangles->addVertex(v3Position.x, v3Position.y, v3Position.x/256, -v3Position.y/256, 255, 255, 255, 255);
        t = triangles->addTriangle(v1, v2, v3, "Textures/Fault Zone.png");
        firstApply = false;
    }
    else {
        triangles->restoreVertex(v1);
        triangles->restoreVertex(v2);
        triangles->restoreVertex(v3);
        triangles->restoreTriangle(t);
    }
    selection->selectVertex(v1);
    selection->selectVertex(v2);
    selection->selectVertex(v3);
}

void CreateTriangle::revert() {
    selection->selectVertex(v1);
    selection->selectVertex(v2);
    selection->selectVertex(v3);

    triangles->removeTriangle(t);
    triangles->removeVertex(v1);
    triangles->removeVertex(v2);
    triangles->removeVertex(v3);
}

}
