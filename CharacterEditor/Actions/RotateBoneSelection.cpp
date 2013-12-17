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

#include "RotateBoneSelection.h"

namespace ck {

RotateBoneSelection::RotateBoneSelection(CharSelection* charSelection, Bones* bones) {
    this->charSelection = charSelection;
    this->bones = bones;

    verticesToRotate = charSelection->getSelectedBoneVertices();
    rotationCenter = Vec2(0, 0);
    for (unsigned int i = 0; i < verticesToRotate.size(); i++) {
        startPositions.push_back(Vec2(bones->getBoneVertexPositionX(verticesToRotate[i]), bones->getBoneVertexPositionY(verticesToRotate[i])));
        rotationCenter += Vec2(bones->getBoneVertexPositionX(verticesToRotate[i]), bones->getBoneVertexPositionY(verticesToRotate[i]));
    }
    rotationCenter /= verticesToRotate.size();
}

void RotateBoneSelection::setRotationAngle(float angle) {
    this->angle = angle;
}

Vec2 RotateBoneSelection::getRotationCenter() {
    return rotationCenter;
}

void RotateBoneSelection::apply() {
    for (unsigned int i = 0; i < verticesToRotate.size(); i++) {
        Vec2 newPosition = vectorRot2D(Vec2(startPositions[i].x, startPositions[i].y), rotationCenter, angle);
        bones->setBoneVertexPosition(verticesToRotate[i], newPosition.x, newPosition.y);
    }
}

void RotateBoneSelection::revert() {
    for (unsigned int i = 0; i < verticesToRotate.size(); i++)
        bones->setBoneVertexPosition(verticesToRotate[i], startPositions[i].x, startPositions[i].y);
}

}
