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

#ifndef CK_BONES_H
#define CK_BONES_H

#include <vector>
#include <set>
#include "RenderManager.h"
#include "Math/Vec2.h"

using std::vector;
using std::set;

namespace ck {

struct BoneVertex {
    float x, y;
    int isUsed;
    int isSelected;
};

struct Bone {
    int v1, v2;
    float angle, length;
    int isUsed;
};

class Bones {
private:
    RenderManager* renderManager;

    glm::mat4 modelViewMatrix;

    /*BoneVertex* boneVertices;
    int boneVertexCount, boneVertexCapacity;

    Bone* bones;
    int boneCount, boneCapacity;*/

    vector<BoneVertex> boneVertices;
    vector<Bone> bones;

    set<int> selectedBoneVertices;

    int rootPoint;
    int tipPoint;

    int rootVertex;
    int tipVertex;
    int leftVertex;
    int rightVertex;
    int lineBottomLeft;
    int lineTopLeft;
    int lineBottomRight;
    int lineTopRight;

    int rootVertexT;
    int tipVertexT;
    int leftVertexT;
    int rightVertexT;
    int triangleBot;
    int triangleTop;
public:
    Bones(RenderManager* renderManager, glm::mat4 modelViewMatrix);
    ~Bones();

    void setModelViewMatrix(glm::mat4 modelViewMatrix);

    int addBoneVertex(float x, float y);
    void removeBoneVertex(int v);
    void restoreBoneVertex(int v);

    int addBone(int v1, int v2);
    void updateBoneAngleLength(int b);
    void removeBone(int b);
    void restoreBone(int b);

    void selectBoneVertex(int v);
    //set<int> getSelectedBoneVertices();

    void setBoneVertexPosition(int v, float x, float y);
    //void setVertexColor(int v, char r, char g, char b, char a);
    void moveBoneVertex(int v, float x, float y);
    float getBoneVertexPositionX(int v);
    float getBoneVertexPositionY(int v);
    //void getVertexColor(int v, char* color);
    bool boneContainsBoneVertex(int b, int v);
    vector<int> getAdjacentBoneVertices(int v);
    vector<int> getAdjacentBones(int v);
    // returns vertices that are only connected to the supplied bone
    vector<int> getIsolatedBoneVertices(int b);
    // returns -1 if no vertex within minimum distance
    int getClosestBoneVertex(float x, float y);

    void drawBone(float x, float y, float angle, float length, bool v1Selected, bool v2Selected);
    void draw();
};

}

#endif // CK_BONES_H
