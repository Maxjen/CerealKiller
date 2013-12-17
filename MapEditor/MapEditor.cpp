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

#include "MapEditor.h"

namespace ck {

MapEditor::MapEditor(ResourceManager* resourceManager, RenderManager* renderManager, int screenWidth, int screenHeight) {
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;

    actionHandler = nullptr;

    this->resourceManager = resourceManager;
    this->renderManager = renderManager;

    modelViewMatrix = glm::mat4();

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
}

MapEditor::~MapEditor() {
    delete selection;
    delete triangles;
}

void MapEditor::handleEvent(SDL_Event* event) {
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
                        actionHandler = new TriangleCreationHandler(selection, triangles, &actionManager, renderManager, selectionLayer, screenHeight);
                    }
                }
                else if (event->button.button == SDL_BUTTON_RIGHT) {
                    int v = triangles->getClosestVertex(event->button.x, screenHeight - event->button.y);
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
                    }
                }
                break;
            case SDL_KEYDOWN:
                switch (event->key.keysym.sym) {
                    case SDLK_LEFT:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(-30, 0, 0));
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_RIGHT:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(30, 0, 0));
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_UP:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, 30, 0));
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_DOWN:
                    {
                        modelViewMatrix = glm::translate(modelViewMatrix, glm::vec3(0, -30, 0));
                        renderManager->setModelViewMatrix(modelViewMatrix);
                        break;
                    }
                    case SDLK_a:
                    {
                        if (!selection->empty()) {
                            vector<int> selectedVertices = selection->getSelectedVertices();
                            SelectVertices* deselectAll = new SelectVertices(selection, selectedVertices);
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
                        if (!selection->empty()) {
                            RemoveSelection* removeSelection = new RemoveSelection(selection, triangles);
                            actionManager.pushAction(removeSelection);
                        }
                        break;
                    }
                    case SDLK_g:
                    {
                        if (!selection->empty()) {
                            actionHandler = new MoveHandler(selection, triangles, &actionManager);
                        }
                        break;
                    }
                    case SDLK_s:
                    {
                        vector<int> selectedVertices = selection->getSelectedVertices();
                        if (selectedVertices.size() > 1) {
                            actionHandler = new ScaleHandler(selection, triangles, &actionManager, screenHeight);
                        }
                        break;
                    }
                    case SDLK_r:
                    {
                        vector<int> selectedVertices = selection->getSelectedVertices();
                        if (selectedVertices.size() > 1) {
                            actionHandler = new RotationHandler(selection, triangles, &actionManager, screenHeight);
                        }
                        break;
                    }
                    case SDLK_f:
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
                    }
                    case SDLK_c:
                    {
                        selection->clear();
                        actionManager.clear();
                        triangles->clear();
                        break;
                    }
                    case SDLK_k:
                    {
                        saveMap("Maps/test.mxm");
                        break;
                    }
                    case SDLK_l:
                    {
                        selection->clear();
                        actionManager.clear();
                        triangles->clear();
                        loadMap("Maps/test.mxm");
                        break;
                    }
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}

void MapEditor::frameRender() {
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    triangles->draw();
    selection->draw();
    selectionLayer->draw();
}

int MapEditor::saveMap(const char* filename) {
    FILE* fp;
    unsigned short chunkId;
    unsigned int chunkLength;

    if ((fp = fopen(filename, "wb")) == NULL)
        return 0;

    chunkId = 0x6060;
    fwrite(&chunkId, 2, 1, fp);
    fseek(fp, 4, SEEK_CUR);

    triangles->saveTriangles(fp);

    chunkLength = ftell(fp);
    fseek(fp, 2, SEEK_SET);
    fwrite(&chunkLength, 4, 1, fp);

    fclose(fp);

    return 1;
}

int MapEditor::loadMap(const char* filename) {
    FILE* fp;
    long fileLength;
    unsigned short chunkId;
    unsigned int chunkLength;
    vector<string> textureNames;

    if ((fp = fopen(filename, "rb")) == NULL)
        return 0;

    fseek(fp, 0, SEEK_END);
    fileLength = ftell(fp);
    rewind(fp);

    while (ftell(fp) < fileLength) {
        fread(&chunkId, 2, 1, fp);
        fread(&chunkLength, 4, 1, fp);

        switch(chunkId) {
            case 0x6060:
                break;
            case 0xa0a0:
            {
                long chunkStart = ftell(fp);
                vector<int> stringSizes;
                char c;
                int currentStringSize = 0;
                for (unsigned int i = 0; i < chunkLength - 6; i++) {
                    fread(&c, 1, 1, fp);
                    currentStringSize++;
                    if (c == '\0') {
                        stringSizes.push_back(currentStringSize - 1);
                        currentStringSize = 0;
                    }
                }
                fseek(fp, chunkStart, SEEK_SET);
                for (unsigned int i = 0; i < stringSizes.size(); i++) {
                    string s;
                    s.resize(stringSizes[i]);
                    fread(&s[0], stringSizes[i], 1, fp);
                    fseek(fp, 1, SEEK_CUR);
                    textureNames.push_back(s);
                }
                break;
            }
            case 0xa1a1:
            {
                int vertexSize = 4 * sizeof(float) + 4 * sizeof(char);
                int numVertices = (chunkLength - 6) / vertexSize;
                for (int i = 0; i < numVertices; i++) {
                    float x, y, u, v;
                    char r, g, b, a;
                    fread(&x, sizeof(float), 1, fp);
                    fread(&y, sizeof(float), 1, fp);
                    fread(&u, sizeof(float), 1, fp);
                    fread(&v, sizeof(float), 1, fp);
                    fread(&r, sizeof(char), 1, fp);
                    fread(&g, sizeof(char), 1, fp);
                    fread(&b, sizeof(char), 1, fp);
                    fread(&a, sizeof(char), 1, fp);
                    triangles->addVertex(x, y, u, v, r, g, b, a);
                }
                break;
            }
            case 0xa2a2:
            {
                int triangleSize = 4 * sizeof(int);
                int numTriangles = (chunkLength - 6) / triangleSize;
                for (int i = 0; i < numTriangles; i++) {
                    int v1, v2, v3;
                    int textureId;
                    fread(&v1, sizeof(int), 1, fp);
                    fread(&v2, sizeof(int), 1, fp);
                    fread(&v3, sizeof(int), 1, fp);
                    fread(&textureId, sizeof(int), 1, fp);
                    triangles->addTriangle(v1, v2, v3, textureNames[textureId].c_str());
                }
                break;
            }
            default:
                fseek(fp, chunkLength - 6, SEEK_CUR);
                break;
        }
    }

    fclose(fp);
    return 1;
}

}
