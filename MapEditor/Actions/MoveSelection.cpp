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

#include "MoveSelection.h"

namespace ck {

MoveSelection::MoveSelection(Selection* selection, Triangles* triangles) {
    this->selection = selection;
    this->triangles = triangles;

    verticesToMove = selection->getSelectedVertices();
    for (unsigned int i = 0; i < verticesToMove.size(); i++)
        startPositions.push_back(Vec2(triangles->getVertexPositionX(verticesToMove[i]), triangles->getVertexPositionY(verticesToMove[i])));
}

void MoveSelection::setDeltaPosition(Vec2 deltaPosition) {
    this->deltaPosition = deltaPosition;
}

void MoveSelection::apply() {
    for (unsigned int i = 0; i < verticesToMove.size(); i++)
        triangles->setVertexPosition(verticesToMove[i], startPositions[i].x + deltaPosition.x, startPositions[i].y + deltaPosition.y);
    selection->updateSelection();
}

void MoveSelection::revert() {
    for (unsigned int i = 0; i < verticesToMove.size(); i++)
        triangles->setVertexPosition(verticesToMove[i], startPositions[i].x, startPositions[i].y);
    selection->updateSelection();
}

}
