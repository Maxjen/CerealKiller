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


#ifndef CK_CORE_H
#define CK_CORE_H

#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>

/*#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>*/
#include <GL/glew.h>

#include <glm/glm.hpp>

#include "RenderManager.h"
#include "Layer.h"
#include "Triangles.h"
#include "Selection.h"

#include "Actions/ActionManager.h"
#include "Actions/SelectVertices.h"
#include "Actions/RemoveSelection.h"
#include "Actions/MoveSelection.h"
#include "Actions/ScaleSelection.h"
#include "Actions/RotateSelection.h"
#include "Actions/CreateTriangle.h"
#include "Actions/FillTriangle.h"

#include "ActionHandler/ActionHandler.h"
#include "ActionHandler/MoveHandler.h"
#include "ActionHandler/ScaleHandler.h"
#include "ActionHandler/RotationHandler.h"
#include "ActionHandler/TriangleCreationHandler.h"

#define PROGRAM_NAME "CerealKiller"

namespace ck {

class Core {
private:
    SDL_Window *mainwindow; // Our window handle
    SDL_GLContext maincontext; // Our opengl context handle

    int screenWidth, screenHeight;

    void sdldie(const char *msg);
    void checkSDLError(int line = -1);

    //Shader* radialBlurShader;

    //b2DynamicTree tree;

    ResourceManager* resourceManager;
    RenderManager* renderManager;
    ActionManager actionManager;

    Triangles* triangles;

    Selection* selection;
    Layer* selectionLayer;

    ActionHandler* actionHandler;
	
    void frameRender();
    void setupWorld();
public:
    Core(int screenWidth, int screenHeight);
	
    void mainLoop();
	
	void close();
};

}

#endif // CK_CORE_H
