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


#include "MoveBoneHandler.h"

namespace ck {

MoveBoneHandler::MoveBoneHandler(CharSelection* charSelection, Bones* bones, ActionManager* actionManager) {
    this->charSelection = charSelection;
    this->bones = bones;
    this->actionManager = actionManager;
    this->moveBoneSelection = new MoveBoneSelection(charSelection, bones);
    deltaPosition = Vec2(0, 0);
    selectedVertices = charSelection->getSelectedBoneVertices();
}

bool MoveBoneHandler::handleEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
            deltaPosition.x += event->motion.xrel;
            deltaPosition.y -= event->motion.yrel;
            for (unsigned int i = 0; i < selectedVertices.size(); i++)
                bones->moveBoneVertex(selectedVertices[i], event->motion.xrel, -event->motion.yrel);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                moveBoneSelection->setDeltaPosition(deltaPosition);
                actionManager->pushAction(moveBoneSelection);
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

}
