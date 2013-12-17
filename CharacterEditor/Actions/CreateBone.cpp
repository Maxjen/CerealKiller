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

#include "CreateBone.h"

namespace ck {

CreateBone::CreateBone(CharSelection* charSelection, Bones* bones) {
    this->charSelection = charSelection;
    this->bones = bones;

    firstApply = true;
}

void CreateBone::setV1Position(float x, float y) {
    v1Position = Vec2(x, y);
}

void CreateBone::setV2Position(float x, float y) {
    v2Position = Vec2(x, y);
}

void CreateBone::apply() {
    if (firstApply) {
        v1 = bones->addBoneVertex(v1Position.x, v1Position.y);
        v2 = bones->addBoneVertex(v2Position.x, v2Position.y);
        b = bones->addBone(v1, v2);
        firstApply = false;
    }
    else {
        bones->restoreBoneVertex(v1);
        bones->restoreBoneVertex(v2);
        bones->restoreBone(b);
    }
    charSelection->selectBoneVertex(v1);
    charSelection->selectBoneVertex(v2);
}

void CreateBone::revert() {
    charSelection->selectBoneVertex(v1);
    charSelection->selectBoneVertex(v2);

    bones->removeBone(b);
    bones->removeBoneVertex(v1);
    bones->removeBoneVertex(v2);
}

}
