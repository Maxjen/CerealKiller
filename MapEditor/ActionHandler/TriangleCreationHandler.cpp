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


#include "TriangleCreationHandler.h"

namespace ck {

TriangleCreationHandler::TriangleCreationHandler(Selection* selection, Triangles* triangles, ActionManager* actionManager, RenderManager* renderManager, Layer* selectionLayer, int screenHeight) {
    this->selection = selection;
    this->actionManager = actionManager;
    this->renderManager = renderManager;
    this->selectionLayer = selectionLayer;
    this->createTriangle = new CreateTriangle(selection, triangles);
    this->screenHeight = screenHeight;
    int x, y;
    SDL_GetMouseState(&x, &y);
    mousePosition.x = x;
    mousePosition.y = screenHeight - y;
    verticesCreated = 1;
    v1Position = Vec2(mousePosition.x, mousePosition.y);
    v1 = renderManager->addPoint(mousePosition.x, mousePosition.y, 255, 255, 255, 255);
    v2 = renderManager->addPoint(mousePosition.x, mousePosition.y, 255, 255, 255, 255);
    lv1 = renderManager->addLineVertex(mousePosition.x, mousePosition.y, 255, 255, 255, 255);
    lv2 = renderManager->addLineVertex(mousePosition.x, mousePosition.y, 255, 255, 255, 255);
    l1 = renderManager->addLine(lv1, lv2);

    selectionLayer->addPoint(v1);
    selectionLayer->addPoint(v2);
    selectionLayer->addLine(l1);
}

bool TriangleCreationHandler::handleEvent(SDL_Event* event) {
    switch (event->type) {
        case SDL_MOUSEMOTION:
            mousePosition.x = event->motion.x;
            mousePosition.y = screenHeight - event->motion.y;
            if (verticesCreated == 1) {
                renderManager->setPointPosition(v2, mousePosition.x, mousePosition.y);
                renderManager->setLineVertexPosition(lv2, mousePosition.x, mousePosition.y);
            }
            else if (verticesCreated == 2) {
                renderManager->setPointPosition(v3, mousePosition.x, mousePosition.y);
                renderManager->setLineVertexPosition(lv3, mousePosition.x, mousePosition.y);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_LEFT) {
                if (verticesCreated == 1) {
                    v2Position = Vec2(mousePosition.x, mousePosition.y);
                    v3 = renderManager->addPoint(mousePosition.x, mousePosition.y, 255, 255, 255, 255);
                    lv3 = renderManager->addLineVertex(mousePosition.x, mousePosition.y, 255, 255, 255, 255);
                    l2 = renderManager->addLine(lv2, lv3);
                    l3 = renderManager->addLine(lv3, lv1);
                    selectionLayer->addPoint(v3);
                    selectionLayer->addLine(l2);
                    selectionLayer->addLine(l3);
                    verticesCreated++;
                }
                else if (verticesCreated == 2) {
                    v3Position = Vec2(mousePosition.x, mousePosition.y);
                    createTriangle->setV1Position(v1Position.x, v1Position.y);
                    createTriangle->setV2Position(v2Position.x, v2Position.y);
                    createTriangle->setV3Position(v3Position.x, v3Position.y);
                    selectionLayer->clearLayer();
                    renderManager->removePoint(v1);
                    renderManager->removePoint(v2);
                    renderManager->removePoint(v3);
                    renderManager->removeLine(l1);
                    renderManager->removeLine(l2);
                    renderManager->removeLine(l3);
                    renderManager->removeLineVertex(lv1);
                    renderManager->removeLineVertex(lv2);
                    renderManager->removeLineVertex(lv3);
                    actionManager->pushAction(createTriangle);
                    return true;
                }
            }
            break;
        default:
            break;
    }

    return false;
}

}
