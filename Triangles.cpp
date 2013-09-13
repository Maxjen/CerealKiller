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

#include "Triangles.h"

namespace ck {

Triangles::Triangles(RenderManager* renderManager) {
    this->renderManager = renderManager;

    vertexCount = 0;
    vertexCapacity = 16;
    vertices = (Vertex*)malloc(vertexCapacity * sizeof(Vertex));
    memset(vertices, 0, vertexCapacity * sizeof(Vertex));

    triangleCount = 0;
    triangleCapacity = 16;
    triangles = (Triangle*)malloc(triangleCapacity * sizeof(Triangles));
    memset(triangles, 0, triangleCapacity * sizeof(Triangle));
}

Triangles::~Triangles() {
    for (int i = 0; i < vertexCount; i++) {
        if (vertices[i].isUsed)
            renderManager->removeTriangleVertex(vertices[i].index);
    }
    free(vertices);

    for (int i = 0; i < triangleCount; i++) {
        if (triangles[i].textureName != 0)
            delete triangles[i].textureName;
        if (triangles[i].isUsed)
            renderManager->removeTriangle(triangles[i].index);
    }
    free(triangles);
}

int Triangles::addVertex(float x, float y, float u, float v, char r, char g, char b, char a) {
    if (vertexCount == vertexCapacity) {
        vertexCapacity *= 2;

        Vertex* oldVertices = vertices;
        vertices = (Vertex*)malloc(vertexCapacity * sizeof(Vertex));
        memcpy(vertices, oldVertices, vertexCount * sizeof(Vertex));
        memset(&vertices[vertexCount], 0, vertexCount * sizeof(Vertex));
        free(oldVertices);
    }
    vertices[vertexCount].x = x;
    vertices[vertexCount].y = y;
    vertices[vertexCount].u = u;
    vertices[vertexCount].v = v;
    vertices[vertexCount].r = r;
    vertices[vertexCount].g = g;
    vertices[vertexCount].b = b;
    vertices[vertexCount].a = a;
    vertices[vertexCount].isUsed = true;
    vertices[vertexCount].index = renderManager->addTriangleVertex(x, y, u, v, r, g, b, a);

    int result = vertexCount++;
    return result;
}

void Triangles::removeVertex(int v) {
    renderManager->removeTriangleVertex(vertices[v].index);
    vertices[v].isUsed = false;
}

void Triangles::restoreVertex(int v) {
    vertices[v].index = renderManager->addTriangleVertex(vertices[v].x, vertices[v].y, vertices[v].u, vertices[v].v, vertices[v].r, vertices[v].g, vertices[v].b, vertices[v].a);
    vertices[v].isUsed = true;
}

int Triangles::addTriangle(int v1, int v2, int v3, const char *textureName) {
    if (triangleCount == triangleCapacity) {
        triangleCapacity *= 2;

        Triangle* oldTriangles = triangles;
        triangles = (Triangle*)malloc(triangleCapacity * sizeof(Triangle));
        memcpy(triangles, oldTriangles, triangleCount * sizeof(Triangle));
        memset(&triangles[triangleCount], 0, triangleCount * sizeof(Triangle));
        free(oldTriangles);
    }
    triangles[triangleCount].v1 = v1;
    triangles[triangleCount].v2 = v2;
    triangles[triangleCount].v3 = v3;
    triangles[triangleCount].textureName = new string(textureName);
    triangles[triangleCount].isUsed = true;
    triangles[triangleCount].index = renderManager->addTriangle(vertices[v1].index, vertices[v2].index, vertices[v3].index, textureName);

    int result = triangleCount++;
    return result;
}

void Triangles::removeTriangle(int t) {
    renderManager->removeTriangle(triangles[t].index);
    triangles[t].isUsed = false;
}

void Triangles::restoreTriangle(int t) {
    triangles[t].index = renderManager->addTriangle(vertices[triangles[t].v1].index, vertices[triangles[t].v2].index, vertices[triangles[t].v3].index, triangles[t].textureName->c_str());
    triangles[t].isUsed = true;
}

void Triangles::setVertexPosition(int v, float x, float y) {
    vertices[v].x = x;
    vertices[v].y = y;
    renderManager->setTriangleVertexPosition(vertices[v].index, vertices[v].x, vertices[v].y);
}

void Triangles::setVertexColor(int v, char r, char g, char b, char a) {
    vertices[v].r = r;
    vertices[v].g = g;
    vertices[v].b = b;
    vertices[v].a = a;
    renderManager->setTriangleVertexColor(vertices[v].index, r, g, b, a);
}

void Triangles::moveVertex(int v, float x, float y) {
    vertices[v].x += x;
    vertices[v].y += y;
    renderManager->setTriangleVertexPosition(vertices[v].index, vertices[v].x, vertices[v].y);
}

float Triangles::getVertexPositionX(int v) {
    return vertices[v].x;
}

float Triangles::getVertexPositionY(int v) {
    return vertices[v].y;
}

void Triangles::getVertexColor(int v, char* color) {
    color[0] = vertices[v].r;
    color[1] = vertices[v].g;
    color[2] = vertices[v].b;
    color[3] = vertices[v].a;
}

bool Triangles::triangleContainsVertex(int t, int v) {
    if (triangles[t].v1 == v || triangles[t].v2 == v || triangles[t].v3 == v)
        return true;
    return false;
}

vector<int> Triangles::getAdjacentVertices(int v) {
    vector<int> result;
    for (int i = 0; i < triangleCount; ++i) {
        if (triangles[i].isUsed) {
            if (triangles[i].v1 == v) {
                result.push_back(triangles[i].v2);
                result.push_back(triangles[i].v3);
            }
            else if (triangles[i].v2 == v) {
                result.push_back(triangles[i].v1);
                result.push_back(triangles[i].v3);
            }
            else if (triangles[i].v3 == v) {
                result.push_back(triangles[i].v1);
                result.push_back(triangles[i].v2);
            }
        }
    }
    return result;
}

vector<int> Triangles::getIsolatedVertices(int t) {
    vector<int> result;

    int v[3];
    v[0] = triangles[t].v1;
    v[1] = triangles[t].v2;
    v[2] = triangles[t].v3;

    // check if the vertices of the removed triangle are used in other triangles and remove them if they are not
    // TODO: use a tree get all the triangles that overlap the removed triangles' aabb and only check for those
    bool vertexIsolated[3] = {true, true, true};
    for (int i = 0; i < triangleCount; i++) {
        if(triangles[i].isUsed) {
            for (int j = 0; j < 3; j++) {
                if (triangleContainsVertex(i, v[j]))
                    vertexIsolated[j] = false;
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (vertexIsolated[i])
            result.push_back(v[i]);
    }
    return result;
}

vector<int> Triangles::getAdjacentTriangles(int v) {
    vector<int> result;
    for (int i = 0; i < triangleCount; i++) {
        if (triangles[i].isUsed && triangleContainsVertex(i, v))
            result.push_back(i);
    }
    return result;
}

int Triangles::getClosestVertex(float x, float y) {
    int result = -1;
    float minDistanceSq = 1000.0f;

    for (int i = 0; i < triangleCount; i++) {
        if (triangles[i].isUsed) {
            float dx = vertices[triangles[i].v1].x - x;
            float dy = vertices[triangles[i].v1].y - y;
            float cDistanceSq = dx*dx + dy*dy;

            if(cDistanceSq < minDistanceSq) {
                result = triangles[i].v1;
                minDistanceSq = cDistanceSq;
            }

            dx = vertices[triangles[i].v2].x - x;
            dy = vertices[triangles[i].v2].y - y;
            cDistanceSq = dx*dx + dy*dy;

            if(cDistanceSq < minDistanceSq) {
                result = triangles[i].v2;
                minDistanceSq = cDistanceSq;
            }

            dx = vertices[triangles[i].v3].x - x;
            dy = vertices[triangles[i].v3].y - y;
            cDistanceSq = dx*dx + dy*dy;

            if(cDistanceSq < minDistanceSq) {
                result = triangles[i].v3;
                minDistanceSq = cDistanceSq;
            }
        }
    }

    return result;
}

void Triangles::draw() {
    for (int i = 0; i < triangleCount; i++) {
        if (triangles[i].isUsed)
            renderManager->drawTriangle(triangles[i].index);
    }
}

}
