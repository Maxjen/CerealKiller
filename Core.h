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

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

//#include <GL/glew.h>

#include <glm/glm.hpp>

#define PROGRAM_NAME "CerealKiller"

namespace ck {

/*

class Shader {
private:
    GLuint  vertexShaderId,
            fragmentShaderId,
            programId;
public:
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    ~Shader();
    char* fileTostring(const char *path);
    void printLog(GLuint obj);
    GLuint getProgramId();
};

inline GLuint Shader::getProgramId() {
    return programId;
}*/

class Core {
private:
    SDL_Window *mainwindow; // Our window handle
    SDL_GLContext maincontext; // Our opengl context handle

    int screenWidth, screenHeight;

    void sdldie(const char *msg);
    void checkSDLError(int line = -1);

    /*
    Shader* triangleShader;
    Shader* pointLineShader;

    Shader* radialBlurShader;

    //b2DynamicTree tree;

    //ResourceManager* resourceManager;
    //RenderManager* renderManager;
    Triangles* triangles;

    Selection* selection;

    ActionHandler* actionHandler;
	
    void frameRender();*/
public:
    Core(int screenWidth, int screenHeight);
	
    void mainLoop();
	
	void close();
};

}

#endif // CK_CORE_H
