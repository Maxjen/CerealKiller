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

#include "CharacterEditor.h"

namespace ck {

CharacterEditor::CharacterEditor(ResourceManager* resourceManager, RenderManager* renderManager, int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    actionHandler = nullptr;

    this->resourceManager = resourceManager;
    this->renderManager = renderManager;

    modelViewMatrix = glm::mat4();

    bones = new Bones(renderManager, modelViewMatrix);
    boneLayer = new BoneLayer(renderManager, bones);
    charSelection = new CharSelection(renderManager, bones);

    triangles = new Triangles(renderManager);
    selection = new Selection(renderManager, triangles);

    //glPointSize(3.0f);

    selectionLayer = new Layer(renderManager);

    /*glViewport(0, 0, screenWidth, screenHeight);

    // Set the color and depth clear values
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    //glDepthMask(GL_TRUE); // enabled by default
    glDepthFunc(GL_LEQUAL);*/

    int v1 = triangles->addVertex(500.0f, 200.0f, 0.0f, 1.0f, 255, 0, 255, 255);
    int v2 = triangles->addVertex(500.0f, 400.0f, 0.0f, 0.0f, 0, 255, 255, 255);
    int v3 = triangles->addVertex(700.0f, 400.0f, 1.0f, 0.0f, 0, 255, 255, 255);
    int v4 = triangles->addVertex(700.0f, 200.0f, 1.0f, 1.0f, 0, 0, 255, 255);
    triangles->addTriangle(v1, v2, v3, "Textures/Canyon.png");
    triangles->addTriangle(v1, v3, v4, "Textures/Fault Zone.png");

    int bv1 = bones->addBoneVertex(200.0f, 100.0f);
    int bv2 = bones->addBoneVertex(300.0f, 100.0f);
    int bv3 = bones->addBoneVertex(470.0f, 200.0f);
    int b1 = bones->addBone(bv1, bv2);
    int b2 = bones->addBone(bv2, bv3);
}

CharacterEditor::~CharacterEditor() {
    delete selection;
    delete triangles;
    delete charSelection;
    delete bones;
}

void CharacterEditor::handleEvent(SDL_Event* event) {
    if (actionHandler != nullptr) {
        if (actionHandler->handleEvent(event)) {
            delete actionHandler;
            actionHandler = nullptr;
        }
    }
    else {
        switch (event->type) {
            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_LEFT) {
                    const Uint8* keyState = SDL_GetKeyboardState(NULL);
                    if (keyState[SDL_SCANCODE_LCTRL]) {
                        actionHandler = new BoneCreationHandler(charSelection, bones, &actionManager, renderManager, boneLayer, screenHeight);
                    }
                }
                else if (event->button.button == SDL_BUTTON_RIGHT) {
                    /*int v = triangles->getClosestVertex(event->button.x, screenHeight - event->button.y);
                    if (v != -1) {
                        //std::cout<<"v = "<<v<<std::endl;
                        vector<int> newVertices;
                        newVertices.push_back(v);
                        SelectVertices* selectVertices;
                        const Uint8* keyState = SDL_GetKeyboardState(NULL);
                        if (keyState[SDL_SCANCODE_LSHIFT])
                            selectVertices = new SelectVertices(selection, newVertices);
                        else
                            selectVertices = new SelectVertices(selection, newVertices, true);
                        actionManager.pushAction(selectVertices);
                    }*/
                    int v = bones->getClosestBoneVertex(event->button.x, screenHeight - event->button.y);
                    if (v != -1) {
                        vector<int> newVertices;
                        newVertices.push_back(v);
                        SelectBoneVertices* selectBoneVertices;
                        const Uint8* keyState = SDL_GetKeyboardState(NULL);
                        if (keyState[SDL_SCANCODE_LSHIFT])
                            selectBoneVertices = new SelectBoneVertices(charSelection, newVertices);
                        else
                            selectBoneVertices = new SelectBoneVertices(charSelection, newVertices, true);
                        actionManager.pushAction(selectBoneVertices);
                        //charSelection->selectBoneVertex(v);
                        //bones->selectBoneVertex(v);
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_LEFT:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(-30, 0, 0));
                        bones->setModelViewMatrix(modelViewMatrix);
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(30, 0, 0));
                        bones->setModelViewMatrix(modelViewMatrix);
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_UP:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, 30, 0));
                        bones->setModelViewMatrix(modelViewMatrix);
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, -30, 0));
                        bones->setModelViewMatrix(modelViewMatrix);
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_a:
                    {
                        if (!charSelection->empty()) {
                            vector<int> selectedVertices = charSelection->getSelectedBoneVertices();
                            SelectBoneVertices* deselectAll = new SelectBoneVertices(charSelection, selectedVertices);
                            actionManager.pushAction(deselectAll);
                        }
                        break;
                    }
                    case SDLK_z:
                    {
                        const Uint8* keyState = SDL_GetKeyboardState(NULL);
                        if (keyState[SDL_SCANCODE_LCTRL]) {
                            if (keyState[SDL_SCANCODE_LSHIFT])
                                actionManager.redoAction();
                            else
                                actionManager.undoAction();
                        }
                        break;
                    }
                    case SDLK_x:
                    {
                        if (!charSelection->empty()) {
                            RemoveBoneSelection* removeBoneSelection = new RemoveBoneSelection(charSelection, bones);
                            actionManager.pushAction(removeBoneSelection);
                        }
                        break;
                    }
                    case SDLK_g:
                    {
                        if (!charSelection->empty()) {
                            actionHandler = new MoveBoneHandler(charSelection, bones, &actionManager);
                        }
                        break;
                    }
                    case SDLK_s:
                    {
                        vector<int> selectedVertices = charSelection->getSelectedBoneVertices();
                        if (selectedVertices.size() > 1) {
                            actionHandler = new ScaleBoneHandler(charSelection, bones, &actionManager, screenHeight);
                        }
                        break;
                    }
                    case SDLK_r:
                    {
                        vector<int> selectedVertices = charSelection->getSelectedBoneVertices();
                        if (selectedVertices.size() > 1) {
                            actionHandler = new RotationBoneHandler(charSelection, bones, &actionManager, screenHeight);
                        }
                        break;
                    }
                    case SDLK_e:
                    {
                        if (!charSelection->empty()) {

                        }
                        break;
                    }
                    /*case SDLK_f:
                    {
                        vector<int> selectedVertices = selection->getSelectedVertices();
                        if (selectedVertices.size() == 3) {
                            vector<int> adjacentTriangles = triangles->getAdjacentTriangles(selectedVertices[0]);
                            bool noTriangleYet = true;
                            for (unsigned int i = 0; i < adjacentTriangles.size(); i++) {
                                if (triangles->triangleContainsVertex(adjacentTriangles[i], selectedVertices[1]) && triangles->triangleContainsVertex(adjacentTriangles[i], selectedVertices[2]))
                                    noTriangleYet = false;
                            }
                            if (noTriangleYet) {
                                FillTriangle* fillTriangle = new FillTriangle(selection, triangles, selectedVertices[0], selectedVertices[1], selectedVertices[2]);
                                actionManager.pushAction(fillTriangle);
                            }
                        }
                        break;
                    }*/
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void CharacterEditor::frameRender() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    bones->draw();
    triangles->draw();
    boneLayer->draw();
    selection->draw();
    selectionLayer->draw();
}

}
