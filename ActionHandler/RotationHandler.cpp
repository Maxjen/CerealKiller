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


#include "RotationHandler.h"

namespace ck {

RotationHandler::RotationHandler(Selection* selection, Triangles* triangles, ActionManager* actionManager, int screenHeight) {
    this->selection = selection;
    this->triangles = triangles;
    this->actionManager = actionManager;
    this->rotateSelection = new RotateSelection(selection, triangles);
    this->screenHeight = screenHeight;
    rotationCenter = rotateSelection->getRotationCenter();
    int x, y;
    SDL_GetMouseState(&x, &y);
    mousePosition.x = x;
    mousePosition.y = screenHeight - y;
    startAngle = atan2((mousePosition - rotationCenter).y, (mousePosition - rotationCenter).x);
    selectedVertices = selection->getSelectedVertices();
    for (unsigned int i = 0; i < selectedVertices.size(); i++) {
        startPositions.push_back(Vec2(triangles->getVertexPositionX(selectedVertices[i]), triangles->getVertexPositionY(selectedVertices[i])));
    }
}

bool RotationHandler::handleEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
            mousePosition.x = event->motion.x;
            mousePosition.y = screenHeight - event->motion.y;
            angle = atan2((mousePosition - rotationCenter).y, (mousePosition - rotationCenter).x) - startAngle;
            for (unsigned int i = 0; i < selectedVertices.size(); i++) {
                Vec2 newPosition = vectorRot2D(Vec2(startPositions[i].x, startPositions[i].y), rotationCenter, angle);
                triangles->setVertexPosition(selectedVertices[i], newPosition.x, newPosition.y);
            }
            selection->updateSelection();
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                rotateSelection->setRotationAngle(angle);
                actionManager->pushAction(rotateSelection);
                return true;
            }
            break;
        default:
            break;
    }

    return false;
}

}
