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


#ifndef CK_CHARACTEREDITOR_H
#define CK_CHARACTEREDITOR_H

#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "../RenderManager.h"
#include "../Layer.h"
#include "../Triangles.h"
#include "../Selection.h"
#include "BoneLayer.h"
#include "../Bones.h"
#include "CharSelection.h"

#include "../Context.h"

#include "../ActionManager.h"
#include "Actions/SelectBoneVertices.h"
#include "Actions/RemoveBoneSelection.h"
/*#include "Actions/MoveBoneSelection.h"
#include "Actions/ScaleBoneSelection.h"
#include "Actions/RotateBoneSelection.h"
#include "Actions/CreateBone.h"*/

#include "../ActionHandler.h"
#include "ActionHandler/MoveBoneHandler.h"
#include "ActionHandler/ScaleBoneHandler.h"
#include "ActionHandler/RotationBoneHandler.h"
#include "ActionHandler/BoneCreationHandler.h"

namespace ck {

class CharacterEditor : public Context {
private:
    int screenWidth, screenHeight;

    //b2DynamicTree tree;

    ResourceManager* resourceManager;
    RenderManager* renderManager;
    ActionManager actionManager;

    glm::mat4 modelViewMatrix;

    Bones* bones;
    BoneLayer* boneLayer;

    Triangles* triangles;

    CharSelection* charSelection;
    Selection* selection;
    Layer* selectionLayer;

    ActionHandler* actionHandler;
public:
    CharacterEditor(ResourceManager* resourceManager, RenderManager* renderManager, int screenWidth, int screenHeight);
    ~CharacterEditor();
    void handleEvent(SDL_Event* event);
    void frameRender();
};

}

#endif // CK_CHARACTEREDITOR_H
