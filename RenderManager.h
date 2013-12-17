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

#ifndef CK_RENDERMANAGER_H
#define CK_RENDERMANAGER_H

#include "ResourceManager.h"

/*#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>*/
//#include <GL/glew.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader/PointLineShader.h"
#include "Shader/TriangleShader.h"

namespace ck {

struct PointLineVertex {
    float x, y;
    char r, g, b, a;
};

struct TriangleVertex {
    float x, y;
    float u, v;
    char r, g, b, a;
};

class RenderManager {
private:
    ResourceManager* resourceManager;

    glm::mat4 projectionMatrix;
    glm::mat4 modelViewMatrix;

    PointLineShader pointLineShader;
    TriangleShader triangleShader;

    int pointCount;
    int pointCapacity;
    int freePoint; // first free element
    int* freePointList; // each array element is the index of the next free point
    GLuint pointVertexBuffer;

    int lineVertexCount;
    int lineVertexCapacity;
    int freeLineVertex; // first free element
    int* freeLineVertexList; // each array element is the index of the next free point
    int lineCount;
    int lineCapacity;
    int freeLine; // first free element
    int* freeLineList; // each array element is the index of the next free point
    GLuint lineVertexBuffer;
    GLuint lineIndexBuffer;

    int triangleVertexCount;
    int triangleVertexCapacity;
    int freeTriangleVertex; // first free element
    int* freeTriangleVertexList; // each array element is the index of the next free point
    int triangleCount;
    int triangleCapacity;
    int freeTriangle; // first free element
    int* freeTriangleList; // each array element is the index of the next free point
    Texture** triangleTextures;
    GLuint triangleVertexBuffer;
    GLuint triangleIndexBuffer;
public:
    RenderManager(ResourceManager* resourceManager);
    ~RenderManager();

    void setModelViewMatrix(glm::mat4 modelViewMatrix);

    int addPoint(float x, float y, char r, char g, char b, char a);
    void setPointPosition(int p, float x, float y);
    void drawPoint(int p);
    void removePoint(int p);

    int addLineVertex(float x, float y, char r, char g, char b, char a);
    int addLine(int v1, int v2);
    void setLineVertexPosition(int v, float x, float y);
    void setLineVertexColor(int v, char r, char g, char b, char a);
    void drawLine(int l);
    void removeLine(int l);
    void removeLineVertex(int v);

    int addTriangleVertex(float x, float y, float u, float v, char r, char g, char b, char a);
    int addTriangle(int v1, int v2, int v3, const char* textureName);
    void setTriangleVertexPosition(int v, float x, float y);
    void setTriangleVertexColor(int v, char r, char g, char b, char a);
    //void enableTextures();
    //void disableTextures();
    void drawTriangle(int t);
    void removeTriangle(int t);
    void removeTriangleVertex(int v);
};

}

#endif // CK_RENDERMANAGER_H
