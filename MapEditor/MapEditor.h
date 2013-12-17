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


#ifndef CK_MAPEDITOR_H
#define CK_MAPEDITOR_H

#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "../RenderManager.h"
#include "../Layer.h"
#include "../Triangles.h"
#include "../Selection.h"

#include "../Context.h"

#include "../ActionManager.h"
#include "Actions/SelectVertices.h"
#include "Actions/RemoveSelection.h"
/*#include "Actions/MoveSelection.h"
#include "Actions/ScaleSelection.h"
#include "Actions/RotateSelection.h"
#include "Actions/CreateTriangle.h"*/
#include "Actions/FillTriangle.h"

#include "../ActionHandler.h"
#include "ActionHandler/MoveHandler.h"
#include "ActionHandler/ScaleHandler.h"
#include "ActionHandler/RotationHandler.h"
#include "ActionHandler/TriangleCreationHandler.h"

namespace ck {

class MapEditor : public Context {
private:
    int screenWidth, screenHeight;

    //b2DynamicTree tree;

    ResourceManager* resourceManager;
    RenderManager* renderManager;
    ActionManager actionManager;

    glm::mat4 modelViewMatrix;

    Triangles* triangles;

    Selection* selection;
    Layer* selectionLayer;

    ActionHandler* actionHandler;
public:
    MapEditor(ResourceManager* resourceManager, RenderManager* renderManager, int screenWidth, int screenHeight);
    ~MapEditor();
    void handleEvent(SDL_Event* event);
    void frameRender();

    int saveMap(const char* filename);
    // returns 1 if successful, 0 otherwise
    int loadMap(const char* filename);
};

}

#endif // CK_MAPEDITOR_H
