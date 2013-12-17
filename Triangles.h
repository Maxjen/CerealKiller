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

#ifndef CK_TRIANGLES_H
#define CK_TRIANGLES_H

#include <vector>
#include "RenderManager.h"

using std::vector;

namespace ck {

struct Vertex {
    float x, y;
    float u, v;
    char r, g, b, a;
    int isUsed;
    int index;
};

struct Triangle {
    int v1, v2, v3;
    //string* textureName;
    int textureId;
    int isUsed;
    int index;
};

class Triangles {
private:
    RenderManager* renderManager;

    vector<string> textureNames;

    Vertex* vertices;
    int vertexCount, vertexCapacity;

    Triangle* triangles;
    int triangleCount, triangleCapacity;
public:
    Triangles(RenderManager* renderManager);
    ~Triangles();

    void saveTriangles(FILE* fp);
    void clear();

    int addVertex(float x, float y, float u, float v, char r, char g, char b, char a);
    void removeVertex(int v);
    void restoreVertex(int v);

    int addTriangle(int v1, int v2, int v3, const char* textureName);
    void removeTriangle(int t);
    void restoreTriangle(int t);

    void setVertexPosition(int v, float x, float y);
    void setVertexColor(int v, char r, char g, char b, char a);
    void moveVertex(int v, float x, float y);
    float getVertexPositionX(int v);
    float getVertexPositionY(int v);
    void getVertexColor(int v, char* color);
    bool triangleContainsVertex(int t, int v);
    vector<int> getAdjacentVertices(int v);
    vector<int> getAdjacentTriangles(int v);
    // returns vertices that are only connected to the supplied triangle (needed for removing)
    vector<int> getIsolatedVertices(int t);
    // returns -1 if no vertex within minimum distance
    int getClosestVertex(float x, float y);

    void draw();
};

}

#endif // CK_TRIANGLES_H
