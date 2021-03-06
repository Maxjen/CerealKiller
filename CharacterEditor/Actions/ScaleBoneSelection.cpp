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

#include "ScaleBoneSelection.h"

namespace ck {

ScaleBoneSelection::ScaleBoneSelection(CharSelection* charSelection, Bones* bones) {
    this->charSelection = charSelection;
    this->bones = bones;

    verticesToScale = charSelection->getSelectedBoneVertices();
    scaleCenter = Vec2(0, 0);
    for (unsigned int i = 0; i < verticesToScale.size(); i++) {
        startPositions.push_back(Vec2(bones->getBoneVertexPositionX(verticesToScale[i]), bones->getBoneVertexPositionY(verticesToScale[i])));
        scaleCenter += Vec2(bones->getBoneVertexPositionX(verticesToScale[i]), bones->getBoneVertexPositionY(verticesToScale[i]));
    }
    scaleCenter /= verticesToScale.size();
}

void ScaleBoneSelection::setScaleFactor(float scaleFactor) {
    this->scaleFactor = scaleFactor;
}

Vec2 ScaleBoneSelection::getScaleCenter() {
    return scaleCenter;
}

void ScaleBoneSelection::apply() {
    for (unsigned int i = 0; i < verticesToScale.size(); i++) {
        Vec2 positionFromCenter = Vec2(startPositions[i].x, startPositions[i].y) - scaleCenter;
        positionFromCenter *= scaleFactor;
        bones->setBoneVertexPosition(verticesToScale[i], scaleCenter.x + positionFromCenter.x, scaleCenter.y + positionFromCenter.y);
    }
}

void ScaleBoneSelection::revert() {
    for (unsigned int i = 0; i < verticesToScale.size(); i++)
        bones->setBoneVertexPosition(verticesToScale[i], startPositions[i].x, startPositions[i].y);
}

}
