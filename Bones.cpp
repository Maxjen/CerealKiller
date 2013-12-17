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

#include "Bones.h"

namespace ck {

Bones::Bones(RenderManager* renderManager, glm::mat4 modelViewMatrix) {
    this->renderManager = renderManager;
    this->modelViewMatrix = modelViewMatrix;

    /*boneVertexCount = 0;
    boneVertexCapacity = 16;
    boneVertices = (BoneVertex*)malloc(boneVertexCapacity * sizeof(BoneVertex));
    memset(boneVertices, 0, boneVertexCapacity * sizeof(BoneVertex));

    boneCount = 0;
    boneCapacity = 16;
    bones = (Bone*)malloc(boneCapacity * sizeof(Bone));
    memset(bones, 0, boneCapacity * sizeof(Bone));*/

    rootPoint = renderManager->addPoint(0, 0, 255, 255, 255, 155);
    tipPoint = renderManager->addPoint(20.0f, 0, 255, 255, 255, 155);

    rootVertex = renderManager->addLineVertex(0, 0, 255, 255, 255, 100);
    tipVertex = renderManager->addLineVertex(20.0f, 0, 255, 255, 255, 100);
    leftVertex = renderManager->addLineVertex(10.0f, 5.0f, 255, 255, 255, 100);
    rightVertex = renderManager->addLineVertex(10.0f, -5.0f, 255, 255, 255, 100);
    lineBottomLeft = renderManager->addLine(rootVertex, leftVertex);
    lineTopLeft = renderManager->addLine(leftVertex, tipVertex);
    lineBottomRight = renderManager->addLine(rootVertex, rightVertex);
    lineTopRight = renderManager->addLine(rightVertex, tipVertex);

    rootVertexT = renderManager->addTriangleVertex(0, 0, 0, 0, 255, 255, 255, 100);
    tipVertexT = renderManager->addTriangleVertex(20.0f, 0, 0, 0, 255, 255, 255, 100);
    leftVertexT = renderManager->addTriangleVertex(10.0f, 5.0f, 0, 0, 255, 255, 255, 100);
    rightVertexT = renderManager->addTriangleVertex(10.0f, -5.0f, 0, 0, 255, 255, 255, 100);
    triangleBot = renderManager->addTriangle(rootVertexT, rightVertexT, leftVertexT, "Textures/white.png");
    triangleTop = renderManager->addTriangle(rightVertexT, tipVertexT, leftVertexT, "Textures/white.png");
}

Bones::~Bones() {
    /*for (int i = 0; i < boneVertexCount; i++) {
        if (boneVertices[i].isUsed)
            renderManager->removeLineVertex(boneVertices[i].index);
    }
    free(boneVertices);

    for (int i = 0; i < boneCount; i++) {
        if (bones[i].isUsed)
            renderManager->removeLine(bones[i].index);
    }
    free(bones);*/

    renderManager->removeLine(lineBottomLeft);
    renderManager->removeLine(lineTopLeft);
    renderManager->removeLine(lineBottomRight);
    renderManager->removeLine(lineTopRight);
    renderManager->removeLineVertex(rootVertex);
    renderManager->removeLineVertex(tipVertex);
    renderManager->removeLineVertex(leftVertex);
    renderManager->removeLineVertex(rightVertex);

    renderManager->removeTriangle(triangleBot);
    renderManager->removeTriangle(triangleTop);
    renderManager->removeTriangleVertex(rootVertexT);
    renderManager->removeTriangleVertex(tipVertexT);
    renderManager->removeTriangleVertex(leftVertexT);
    renderManager->removeTriangleVertex(rightVertexT);
}

void Bones::setModelViewMatrix(glm::mat4 modelViewMatrix) {
    this->modelViewMatrix = modelViewMatrix;
}

int Bones::addBoneVertex(float x, float y) {
    /*if (boneVertexCount == boneVertexCapacity) {
        boneVertexCapacity *= 2;

        BoneVertex* oldBoneVertices = boneVertices;
        boneVertices = (BoneVertex*)malloc(boneVertexCapacity * sizeof(BoneVertex));
        memcpy(boneVertices, oldBoneVertices, boneVertexCount * sizeof(BoneVertex));
        memset(&boneVertices[boneVertexCount], 0, boneVertexCount * sizeof(BoneVertex));
        free(oldBoneVertices);
    }
    boneVertices[boneVertexCount].x = x;
    boneVertices[boneVertexCount].y = y;
    boneVertices[boneVertexCount].isUsed = true;
    boneVertices[boneVertexCount].index = renderManager->addLineVertex(x, y, 255, 255, 255, 255);

    int result = boneVertexCount++;
    return result;*/

    BoneVertex v;
    v.x = x;
    v.y = y;
    v.isUsed = true;
    v.isSelected = false;
    boneVertices.push_back(v);
    return boneVertices.size() - 1;
}

void Bones::removeBoneVertex(int v) {
    boneVertices[v].isUsed = false;
}

void Bones::restoreBoneVertex(int v) {
    boneVertices[v].isUsed = true;
}

int Bones::addBone(int v1, int v2) {
    /*if (boneCount == boneCapacity) {
        boneCapacity *= 2;

        Bone* oldBones = bones;
        bones = (Bone*)malloc(boneCapacity * sizeof(Bone));
        memcpy(bones, oldBones, boneCount * sizeof(Bone));
        memset(&bones[boneCount], 0, boneCount * sizeof(Bone));
        free(oldBones);
    }
    bones[boneCount].v1 = v1;
    bones[boneCount].v2 = v2;
    bones[boneCount].isUsed = true;
    bones[boneCount].index = renderManager->addLine(boneVertices[v1].index, boneVertices[v2].index);

    int result = boneCount++;
    return result;*/

    Vec2 v1Tmp(boneVertices[v1].x, boneVertices[v1].y);
    Vec2 v2Tmp(boneVertices[v2].x, boneVertices[v2].y);
    Bone b;
    b.v1 = v1;
    b.v2 = v2;
    b.angle = atan2((v2Tmp - v1Tmp).y, (v2Tmp - v1Tmp).x);
    b.length = distance(v1Tmp, v2Tmp);
    b.isUsed = true;
    bones.push_back(b);
    return bones.size() - 1;
}

void Bones::updateBoneAngleLength(int b) {
    Vec2 v1Tmp(boneVertices[bones[b].v1].x, boneVertices[bones[b].v1].y);
    Vec2 v2Tmp(boneVertices[bones[b].v2].x, boneVertices[bones[b].v2].y);
    bones[b].angle = atan2((v2Tmp - v1Tmp).y, (v2Tmp - v1Tmp).x);
    bones[b].length = distance(v1Tmp, v2Tmp);
}

void Bones::removeBone(int b) {
    bones[b].isUsed = false;
}

void Bones::restoreBone(int b) {
    bones[b].isUsed = true;
}

void Bones::selectBoneVertex(int v) {
    if (selectedBoneVertices.find(v) == selectedBoneVertices.end()) {
        selectedBoneVertices.insert(v);
        boneVertices[v].isSelected = true;
    }
    else {
        selectedBoneVertices.erase(v);
        boneVertices[v].isSelected = false;
    }
}

void Bones::setBoneVertexPosition(int v, float x, float y) {
    boneVertices[v].x = x;
    boneVertices[v].y = y;
    vector<int> adjacentBones = getAdjacentBones(v);
    for (unsigned int i = 0; i < adjacentBones.size(); i++)
        updateBoneAngleLength(adjacentBones[i]);
}

/*set<int> Bones::getSelectedBoneVertices() {
    return selectedBoneVertices;
}*/

/*void Bones::setVertexColor(int v, char r, char g, char b, char a) {
    vertices[v].r = r;
    vertices[v].g = g;
    vertices[v].b = b;
    vertices[v].a = a;
    renderManager->setTriangleVertexColor(vertices[v].index, r, g, b, a);
}*/

void Bones::moveBoneVertex(int v, float x, float y) {
    boneVertices[v].x += x;
    boneVertices[v].y += y;
    vector<int> adjacentBones = getAdjacentBones(v);
    for (unsigned int i = 0; i < adjacentBones.size(); i++)
        updateBoneAngleLength(adjacentBones[i]);
}

float Bones::getBoneVertexPositionX(int v) {
    return boneVertices[v].x;
}

float Bones::getBoneVertexPositionY(int v) {
    return boneVertices[v].y;
}

/*void Bones::getVertexColor(int v, char* color) {
    color[0] = vertices[v].r;
    color[1] = vertices[v].g;
    color[2] = vertices[v].b;
    color[3] = vertices[v].a;
}*/

bool Bones::boneContainsBoneVertex(int b, int v) {
    if (bones[b].v1 == v || bones[b].v2 == v)
        return true;
    return false;
}

vector<int> Bones::getAdjacentBoneVertices(int v) {
    /*vector<int> result;
    for (int i = 0; i < boneCount; ++i) {
        if (bones[i].isUsed) {
            if (bones[i].v1 == v) {
                result.push_back(bones[i].v2);
            }
            else if (bones[i].v2 == v) {
                result.push_back(bones[i].v1);
            }
        }
    }
    return result;*/

    vector<int> result;
    for (unsigned int i = 0; i < bones.size(); i++) {
        if (bones[i].isUsed) {
            if (bones[i].v1 == v) {
                result.push_back(bones[i].v2);
            }
            else if (bones[i].v2 == v) {
                result.push_back(bones[i].v1);
            }
        }
    }
    return result;
}

vector<int> Bones::getIsolatedBoneVertices(int b) {
    vector<int> result;

    int v[2];
    v[0] = bones[b].v1;
    v[1] = bones[b].v2;

    // TODO: use a tree get all the triangles that overlap the removed triangles' aabb and only check for those
    bool vertexIsolated[2] = {true, true};
    //for (int i = 0; i < boneCount; i++) {
    for (unsigned int i = 0; i < bones.size(); i++) {
        if(bones[i].isUsed) {
            for (int j = 0; j < 2; j++) {
                if (boneContainsBoneVertex(i, v[j]))
                    vertexIsolated[j] = false;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        if (vertexIsolated[i])
            result.push_back(v[i]);
    }
    return result;
}

vector<int> Bones::getAdjacentBones(int v) {
    vector<int> result;
    //for (int i = 0; i < boneCount; i++) {
    for (unsigned int i = 0; i < bones.size(); i++) {
        if (bones[i].isUsed && boneContainsBoneVertex(i, v))
            result.push_back(i);
    }
    return result;
}

int Bones::getClosestBoneVertex(float x, float y) {
    int result = -1;
    float minDistanceSq = 1000.0f;

    //for (int i = 0; i < boneCount; i++) {
    for (unsigned int i = 0; i < bones.size(); i++) {
        if (bones[i].isUsed) {
            float dx = boneVertices[bones[i].v1].x - x;
            float dy = boneVertices[bones[i].v1].y - y;
            float cDistanceSq = dx*dx + dy*dy;

            if(cDistanceSq < minDistanceSq) {
                result = bones[i].v1;
                minDistanceSq = cDistanceSq;
            }

            dx = boneVertices[bones[i].v2].x - x;
            dy = boneVertices[bones[i].v2].y - y;
            cDistanceSq = dx*dx + dy*dy;

            if(cDistanceSq < minDistanceSq) {
                result = bones[i].v2;
                minDistanceSq = cDistanceSq;
            }
        }
    }

    return result;
}

void Bones::drawBone(float x, float y, float angle, float length, bool v1Selected, bool v2Selected) {
    glm::mat4 modelViewMatrixTmp = glm::translate(modelViewMatrix, glm::vec3(x, y, 0));
    modelViewMatrixTmp = glm::rotate(modelViewMatrixTmp, angle, glm::vec3(0, 0, 1));
    renderManager->setModelViewMatrix(modelViewMatrixTmp);

    renderManager->setLineVertexPosition(tipVertex, length, 0);
    renderManager->setTriangleVertexPosition(tipVertexT, length, 0);
    if (length < 20.0f) {
        renderManager->setLineVertexPosition(leftVertex, length/2, 5.0f);
        renderManager->setLineVertexPosition(rightVertex, length/2, -5.0f);
        renderManager->setTriangleVertexPosition(leftVertexT, length/2, 5.0f);
        renderManager->setTriangleVertexPosition(rightVertexT, length/2, -5.0f);
    }
    else {
        renderManager->setLineVertexPosition(leftVertex, 10.0f, 5.0f);
        renderManager->setLineVertexPosition(rightVertex, 10.0f, -5.0f);
        renderManager->setTriangleVertexPosition(leftVertexT, 10.0f, 5.0f);
        renderManager->setTriangleVertexPosition(rightVertexT, 10.0f, -5.0f);
    }

    if (v1Selected) {
        renderManager->setLineVertexColor(rootVertex, 255, 255, 255, 255);
        renderManager->setLineVertexColor(leftVertex, 255, 255, 255, 255);
        renderManager->setLineVertexColor(rightVertex, 255, 255, 255, 255);
        renderManager->setTriangleVertexColor(rootVertexT, 255, 255, 255, 200);
        renderManager->setTriangleVertexColor(leftVertexT, 255, 255, 255, 200);
        renderManager->setTriangleVertexColor(rightVertexT, 255, 255, 255, 200);
        renderManager->drawPoint(rootPoint);
    }
    else {
        renderManager->setLineVertexColor(rootVertex, 255, 255, 255, 100);
        renderManager->setLineVertexColor(leftVertex, 255, 255, 255, 100);
        renderManager->setLineVertexColor(rightVertex, 255, 255, 255, 100);
        renderManager->setTriangleVertexColor(rootVertexT, 255, 255, 255, 100);
        renderManager->setTriangleVertexColor(leftVertexT, 255, 255, 255, 100);
        renderManager->setTriangleVertexColor(rightVertexT, 255, 255, 255, 100);
    }
    if (v2Selected) {
        renderManager->setLineVertexColor(tipVertex, 255, 255, 255, 255);
        renderManager->setTriangleVertexColor(tipVertexT, 255, 255, 255, 200);
        renderManager->setPointPosition(tipPoint, length, 0);
        renderManager->drawPoint(tipPoint);
    }
    else {
        renderManager->setLineVertexColor(tipVertex, 255, 255, 255, 100);
        renderManager->setTriangleVertexColor(tipVertexT, 255, 255, 255, 100);
    }

    renderManager->drawLine(lineBottomLeft);
    renderManager->drawLine(lineTopLeft);
    renderManager->drawLine(lineBottomRight);
    renderManager->drawLine(lineTopRight);

    renderManager->drawTriangle(triangleBot);
    renderManager->drawTriangle(triangleTop);
}

void Bones::draw() {
    //for (int i = 0; i < boneCount; i++) {
    for (unsigned int i = 0; i < bones.size(); i++) {
        if (bones[i].isUsed) {
            float xTmp = boneVertices[bones[i].v1].x;
            float yTmp = boneVertices[bones[i].v1].y;
            /*glm::mat4 modelViewMatrixTmp = glm::translate(modelViewMatrix, glm::vec3(xTmp, yTmp, 0));
            modelViewMatrixTmp = glm::rotate(modelViewMatrixTmp, bones[i].angle, glm::vec3(0, 0, 1));
            renderManager->setModelViewMatrix(modelViewMatrixTmp);*/
            drawBone(xTmp, yTmp, bones[i].angle, bones[i].length, boneVertices[bones[i].v1].isSelected, boneVertices[bones[i].v2].isSelected);
            //renderManager->drawLine(bones[i].index);
        }
    }
    /*renderManager->drawLine(lineBottomLeft);
    renderManager->drawLine(lineTopLeft);
    renderManager->drawLine(lineBottomRight);
    renderManager->drawLine(lineTopRight);*/
}

}
