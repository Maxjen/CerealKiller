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


#ifndef CK_ROTATIONBONEHANDLER_H
#define CK_ROTATIONBONEHANDLER_H

#include "../../ActionHandler.h"
#include "../../ActionManager.h"
#include "../Actions/RotateBoneSelection.h"

namespace ck {

class RotationBoneHandler : public ActionHandler {
private:
    CharSelection* charSelection;
    Bones* bones;
    ActionManager* actionManager;
    RotateBoneSelection* rotateBoneSelection;
    int screenHeight;
    Vec2 rotationCenter;
    Vec2 mousePosition;
    float angle;
    float startAngle;
    vector<int> selectedVertices;
    vector<Vec2> startPositions;
public:
    RotationBoneHandler(CharSelection* charSelection, Bones* bones, ActionManager* actionManager, int screenHeight);
    bool handleEvent(SDL_Event* event);
};

}

#endif // CK_ROTATIONBONEHANDLER_H
