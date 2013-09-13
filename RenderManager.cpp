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

#include "RenderManager.h"

namespace ck {

RenderManager::RenderManager(ResourceManager* resourceManager) {
    this->resourceManager = resourceManager;

    projectionMatrix = glm::ortho<GLfloat>(0, 800, 0, 600, -128, 128);
    modelViewMatrix = glm::mat4();

    pointLineShader.bind();
    pointLineShader.setProjectionMatrix(projectionMatrix);
    pointLineShader.setModelViewMatrix(modelViewMatrix);

    triangleShader.bind();
    triangleShader.setProjectionMatrix(projectionMatrix);
    triangleShader.setModelViewMatrix(modelViewMatrix);

    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++)
            printf("%f ", glm::value_ptr(modelViewMatrix)[i*4+j]);
        printf("\n");
    }*/

    /*glUniformMatrix4fv(projectionMatrixLocationPointLine, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(modelViewMatrixLocationPointLine, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(projectionMatrixLocationTriangle, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(modelViewMatrixLocationTriangle, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));*/

    /*glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 0, 600, -128, 128);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();*/

    pointCount = 0;
    pointCapacity = 16;
    freePoint = 0;
    freePointList = (int*)malloc(pointCapacity * sizeof(int));
    for (int i = 0; i < pointCapacity; i++)
        freePointList[i] = i + 1;

    glGenBuffers(1, &pointVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, pointVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, pointCapacity * sizeof(PointLineVertex), NULL, GL_DYNAMIC_DRAW);


    lineVertexCount = lineCount = 0;
    lineVertexCapacity = lineCapacity = 16;
    freeLineVertex = 0;
    freeLineVertexList = (int*)malloc(lineVertexCapacity * sizeof(int));
    for (int i = 0; i < lineVertexCapacity; i++)
        freeLineVertexList[i] = i + 1;
    freeLine = 0;
    freeLineList = (int*)malloc(lineCapacity * sizeof(int));
    for (int i = 0; i < lineCapacity; i++)
        freeLineList[i] = i + 1;

    glGenBuffers(1, &lineVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, lineVertexCapacity * sizeof(PointLineVertex), NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &lineIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineCapacity * 2 * sizeof(int), NULL, GL_DYNAMIC_DRAW);


    triangleVertexCount = triangleCount = 0;
    triangleVertexCapacity = triangleCapacity = 16;
    freeTriangleVertex = 0;
    freeTriangleVertexList = (int*)malloc(triangleVertexCapacity * sizeof(int));
    for (int i = 0; i < triangleVertexCapacity; i++)
        freeTriangleVertexList[i] = i + 1;
    freeTriangle = 0;
    freeTriangleList = (int*)malloc(triangleCapacity * sizeof(int));
    for (int i = 0; i < triangleCapacity; i++)
        freeTriangleList[i] = i + 1;
    triangleTextures = (Texture**)malloc(triangleCapacity * sizeof(Texture*));
    memset(triangleTextures, 0, triangleCapacity * sizeof(Texture*));

    glGenBuffers(1, &triangleVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, triangleVertexCapacity * sizeof(TriangleVertex), NULL, GL_DYNAMIC_DRAW);

    glGenBuffers(1, &triangleIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleCapacity * 3 * sizeof(int), NULL, GL_DYNAMIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

RenderManager::~RenderManager() {
    free(freePointList);
    free(freeLineVertexList);
    free(freeLineList);
    free(freeTriangleVertexList);
    free(freeTriangleList);

    for (int i = 0; i < triangleCapacity; i++) {
        if (triangleTextures[i] == 0)
            delete(triangleTextures[i]);
    }
    free(triangleTextures);

    glDeleteBuffers(1, &pointVertexBuffer);

    glDeleteBuffers(1, &lineVertexBuffer);
    glDeleteBuffers(1, &lineIndexBuffer);

    glDeleteBuffers(1, &triangleVertexBuffer);
    glDeleteBuffers(1, &triangleIndexBuffer);
}

int RenderManager::addPoint(float x, float y, char r, char g, char b, char a) {
    if (pointCount == pointCapacity) {
        pointCapacity *= 2;

        int* oldFreePointList = freePointList;
        freePointList = (int*)malloc(pointCapacity * sizeof(int));
        memcpy(freePointList, oldFreePointList, pointCount * sizeof(int));
        for (int i = pointCount; i < pointCapacity; i++)
            freePointList[i] = i + 1;

        glBindBuffer(GL_ARRAY_BUFFER, pointVertexBuffer);
        PointLineVertex* vertices = (PointLineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, pointCount * sizeof(PointLineVertex), GL_MAP_READ_BIT);
        PointLineVertex* verticesTmp = (PointLineVertex*)malloc(pointCount * sizeof(PointLineVertex));
        memcpy(verticesTmp, vertices, pointCount * sizeof(PointLineVertex));
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, pointCapacity * sizeof(PointLineVertex), verticesTmp, GL_DYNAMIC_DRAW);
        free(verticesTmp);
    }
    PointLineVertex newPoint;
    newPoint.x = x;
    newPoint.y = y;
    newPoint.r = r;
    newPoint.g = g;
    newPoint.b = b;
    newPoint.a = a;
    glBindBuffer(GL_ARRAY_BUFFER, pointVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, freePoint * sizeof(PointLineVertex), sizeof(PointLineVertex), &newPoint);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int result = freePoint;
    freePoint = freePointList[freePoint];
    pointCount++;

    return result;
}

void RenderManager::setPointPosition(int p, float x, float y) {
    float position[2] = {x, y};
    glBindBuffer(GL_ARRAY_BUFFER, pointVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, p * sizeof(PointLineVertex), 2 * sizeof(float), &position);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::drawPoint(int p) {
    pointLineShader.bind();

    glBindBuffer(GL_ARRAY_BUFFER, pointVertexBuffer);

    pointLineShader.setPositionPointer(sizeof(PointLineVertex), 0);
    pointLineShader.setColorPointer(sizeof(PointLineVertex), (GLvoid*)(2 * sizeof(float)));
    pointLineShader.enablePositionPointer();
    pointLineShader.enableColorPointer();

    glDrawArrays(GL_POINTS, p, 1);

    pointLineShader.disableColorPointer();
    pointLineShader.disablePositionPointer();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    pointLineShader.unbind();
}

void RenderManager::removePoint(int p) {
    freePointList[p] = freePoint;
    freePoint = p;
}

int RenderManager::addLineVertex(float x, float y, char r, char g, char b, char a) {
    if (lineVertexCount == lineVertexCapacity) {
        lineVertexCapacity *= 2;

        int* oldFreeLineVertexList = freeLineVertexList;
        freeLineVertexList = (int*)malloc(lineVertexCapacity * sizeof(int));
        memcpy(freeLineVertexList, oldFreeLineVertexList, lineVertexCount * sizeof(int));
        for (int i = lineVertexCount; i < lineVertexCapacity; i++)
            freeLineVertexList[i] = i + 1;

        glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
        PointLineVertex* vertices = (PointLineVertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, lineVertexCount * sizeof(PointLineVertex), GL_MAP_READ_BIT);
        PointLineVertex* verticesTmp = (PointLineVertex*)malloc(lineVertexCount * sizeof(PointLineVertex));
        memcpy(verticesTmp, vertices, lineVertexCount * sizeof(PointLineVertex));
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, lineVertexCapacity * sizeof(PointLineVertex), verticesTmp, GL_DYNAMIC_DRAW);
        free(verticesTmp);
    }
    PointLineVertex newLineVertex;
    newLineVertex.x = x;
    newLineVertex.y = y;
    newLineVertex.r = r;
    newLineVertex.g = g;
    newLineVertex.b = b;
    newLineVertex.a = a;
    glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, freeLineVertex * sizeof(PointLineVertex), sizeof(PointLineVertex), &newLineVertex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int result = freeLineVertex;
    freeLineVertex = freeLineVertexList[freeLineVertex];
    lineVertexCount++;

    return result;
}

int RenderManager::addLine(int v1, int v2) {
    if (lineCount == lineCapacity) {
        lineCapacity *= 2;

        int* oldFreeLineList = freeLineList;
        freeLineList = (int*)malloc(lineCapacity * sizeof(int));
        memcpy(freeLineList, oldFreeLineList, lineCount * sizeof(int));
        for (int i = lineCount; i < lineCapacity; i++)
            freeLineList[i] = i + 1;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBuffer);
        int* indices = (int*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, lineCount * 2 * sizeof(int), GL_MAP_READ_BIT);
        int* indicesTmp = (int*)malloc(lineCount * 2 * sizeof(int));
        memcpy(indicesTmp, indices, lineCount * 2 * sizeof(int));
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, lineCapacity * 2 * sizeof(int), indicesTmp, GL_DYNAMIC_DRAW);
        free(indicesTmp);
    }
    int newLine[2] = {v1, v2};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBuffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, freeLine * 2 * sizeof(int), 2 * sizeof(int), &newLine);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    int result = freeLine;
    freeLine = freeLineList[freeLine];
    lineCount++;

    return result;
}

void RenderManager::setLineVertexPosition(int v, float x, float y) {
    float position[2] = {x, y};
    glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, v * sizeof(PointLineVertex), 2 * sizeof(float), &position);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::setLineVertexColor(int v, char r, char g, char b, char a) {
    char color[4] = {r, g, b, a};
    glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, v * sizeof(PointLineVertex) + 2 * sizeof(float), 4 * sizeof(char), &color);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::drawLine(int l) {
    pointLineShader.bind();

    glBindBuffer(GL_ARRAY_BUFFER, lineVertexBuffer);

    pointLineShader.setPositionPointer(sizeof(PointLineVertex), 0);
    pointLineShader.setColorPointer(sizeof(PointLineVertex), (GLvoid*)(2 * sizeof(float)));
    pointLineShader.enablePositionPointer();
    pointLineShader.enableColorPointer();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lineIndexBuffer);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glDrawElements(GL_LINES, 2, GL_UNSIGNED_INT, (GLvoid*)(2 * sizeof(int) * l));
    glDisable(GL_BLEND);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    pointLineShader.disableColorPointer();
    pointLineShader.disablePositionPointer();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    pointLineShader.unbind();
}

void RenderManager::removeLine(int l) {
    freeLineList[l] = freeLine;
    freeLine = l;
}

void RenderManager::removeLineVertex(int v) {
    freeLineVertexList[v] = freeLineVertex;
    freeLineVertex = v;
}

int RenderManager::addTriangleVertex(float x, float y, float u, float v, char r, char g, char b, char a) {
    if (triangleVertexCount == triangleVertexCapacity) {
        triangleVertexCapacity *= 2;

        int* oldFreeTriangleVertexList = freeTriangleVertexList;
        freeTriangleVertexList = (int*)malloc(triangleVertexCapacity * sizeof(int));
        memcpy(freeTriangleVertexList, oldFreeTriangleVertexList, triangleVertexCount * sizeof(int));
        for (int i = triangleVertexCount; i < triangleVertexCapacity; i++)
            freeTriangleVertexList[i] = i + 1;

        glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);
        TriangleVertex* vertices = (TriangleVertex*)glMapBufferRange(GL_ARRAY_BUFFER, 0, triangleVertexCount * sizeof(TriangleVertex), GL_MAP_READ_BIT);
        TriangleVertex* verticesTmp = (TriangleVertex*)malloc(triangleVertexCount * sizeof(TriangleVertex));
        memcpy(verticesTmp, vertices, triangleVertexCount * sizeof(TriangleVertex));
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBufferData(GL_ARRAY_BUFFER, triangleVertexCapacity * sizeof(TriangleVertex), verticesTmp, GL_DYNAMIC_DRAW);
        free(verticesTmp);
    }
    TriangleVertex newTriangleVertex;
    newTriangleVertex.x = x;
    newTriangleVertex.y = y;
    newTriangleVertex.u = u;
    newTriangleVertex.v = v;
    newTriangleVertex.r = r;
    newTriangleVertex.g = g;
    newTriangleVertex.b = b;
    newTriangleVertex.a = a;
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, freeTriangleVertex * sizeof(TriangleVertex), sizeof(TriangleVertex), &newTriangleVertex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int result = freeTriangleVertex;
    freeTriangleVertex = freeTriangleVertexList[freeTriangleVertex];
    triangleVertexCount++;

    return result;
}

int RenderManager::addTriangle(int v1, int v2, int v3, const char *textureName) {
    // TODO: texture
    if (triangleCount == triangleCapacity) {
        triangleCapacity *= 2;

        int* oldFreeTriangleList = freeTriangleList;
        freeTriangleList = (int*)malloc(triangleCapacity * sizeof(int));
        memcpy(freeTriangleList, oldFreeTriangleList, triangleCount * sizeof(int));
        for (int i = triangleCount; i < triangleCapacity; i++)
            freeTriangleList[i] = i +1;

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBuffer);
        int* indices = (int*)glMapBufferRange(GL_ELEMENT_ARRAY_BUFFER, 0, triangleCount * 3 * sizeof(int), GL_MAP_READ_BIT);
        int* indicesTmp = (int*)malloc(triangleCount * 3 * sizeof(int));
        memcpy(indicesTmp, indices, triangleCount * 3 * sizeof(int));
        glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangleCapacity * 3 * sizeof(int), indicesTmp, GL_DYNAMIC_DRAW);
        free(indicesTmp);

        Texture** oldTriangleTextures = triangleTextures;
        triangleTextures = (Texture**)malloc(triangleCapacity * sizeof(Texture*));
        memcpy(triangleTextures, oldTriangleTextures, triangleCount * sizeof(Texture*));
        memset(&triangleTextures[triangleCount], 0, triangleCount * sizeof(Texture*));
    }
    int newTriangle[3] = {v1, v2, v3};
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBuffer);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, freeTriangle * 3 * sizeof(int), 3 * sizeof(int), &newTriangle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    triangleTextures[freeTriangle] = resourceManager->getTexture(textureName);

    int result = freeTriangle;
    freeTriangle = freeTriangleList[freeTriangle];
    triangleCount++;

    return result;
}

void RenderManager::setTriangleVertexPosition(int v, float x, float y) {
    float position[2] = {x, y};
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, v * sizeof(TriangleVertex), 2 * sizeof(float), &position);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::setTriangleVertexColor(int v, char r, char g, char b, char a) {
    char color[4] = {r, g, b, a};
    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);
    glBufferSubData(GL_ARRAY_BUFFER, v * sizeof(TriangleVertex) + 4 * sizeof(float), 4 * sizeof(char), &color);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderManager::drawTriangle(int t) {
    triangleShader.bind();

    glBindBuffer(GL_ARRAY_BUFFER, triangleVertexBuffer);

    triangleShader.setPositionPointer(sizeof(TriangleVertex), 0);
    triangleShader.setTexCoordPointer(sizeof(TriangleVertex), (GLvoid*)(2 * sizeof(float)));
    triangleShader.setColorPointer(sizeof(TriangleVertex), (GLvoid*)(4 * sizeof(float)));
    triangleShader.enablePositionPointer();
    triangleShader.enableTexCoordPointer();
    triangleShader.enableColorPointer();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, triangleIndexBuffer);

    //glActiveTexture(GL_TEXTURE0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, triangleTextures[t]->id);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (GLvoid*)(3 * sizeof(int) * t));
    glDisable(GL_BLEND);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    triangleShader.disableColorPointer();
    triangleShader.disableTexCoordPointer();
    triangleShader.disablePositionPointer();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    triangleShader.unbind();
}

void RenderManager::removeTriangle(int t) {
    delete(triangleTextures[t]);
    freeTriangleList[t] = freeTriangle;
    freeTriangle = t;
}

void RenderManager::removeTriangleVertex(int v) {
    freeTriangleVertexList[v] = freeTriangleVertex;
    freeTriangleVertex = v;
}

}
