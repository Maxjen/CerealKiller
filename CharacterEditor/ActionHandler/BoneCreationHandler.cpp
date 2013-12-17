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


#include "BoneCreationHandler.h"

namespace ck {

BoneCreationHandler::BoneCreationHandler(CharSelection* charSelection, Bones* bones, ActionManager* actionManager, RenderManager* renderManager, BoneLayer* boneLayer, int screenHeight) {
    this->charSelection = charSelection;
    this->actionManager = actionManager;
    this->renderManager = renderManager;
    this->boneLayer = boneLayer;
    this->createBone = new CreateBone(charSelection, bones);
    this->screenHeight = screenHeight;
    int x, y;
    SDL_GetMouseState(&x, &y);
    mousePosition.x = x;
    mousePosition.y = screenHeight - y;
    v1Position = Vec2(mousePosition.x, mousePosition.y);
    boneOverlayIndex = boneLayer->addBoneOverlay(mousePosition.x, mousePosition.y, 0, 0);
}

bool BoneCreationHandler::handleEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
        {
            mousePosition.x = event->motion.x;
            mousePosition.y = screenHeight - event->motion.y;
            float angle = atan2((mousePosition - v1Position).y, (mousePosition - v1Position).x);
            float length = distance(mousePosition, v1Position);
            boneLayer->setBoneOverlayAngleLength(boneOverlayIndex, angle, length);
            break;
        }
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                v2Position = Vec2(mousePosition.x, mousePosition.y);
                createBone->setV1Position(v1Position.x, v1Position.y);
                createBone->setV2Position(v2Position.x, v2Position.y);
                boneLayer->clearBoneOverlays();
                actionManager->pushAction(createBone);
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

}
