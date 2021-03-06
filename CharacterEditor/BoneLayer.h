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


#ifndef CK_BONELAYER_H
#define CK_BONELAYER_H

#include "../RenderManager.h"
#include "../Bones.h"
#include <set>

using std::set;

namespace ck {

struct BoneOverlay {
    float x, y;
    float angle, length;
};

class BoneLayer {
private:
    RenderManager* renderManager;
    Bones* bones;
    set<int> points;
    set<int> lines;
    set<int> triangles;
    vector<BoneOverlay> boneOverlays;
public:
    BoneLayer(RenderManager* renderManager, Bones* bones);
    void addPoint(int p);
    void removePoint(int p);
    void addLine(int l);
    void removeLine(int l);
    void addTriangle(int t);
    void removeTriangle(int t);
    int addBoneOverlay(float x, float y, float angle, float length);
    void setBoneOverlayPosition(int b, float x, float y);
    void setBoneOverlayAngleLength(int b, float angle, float length);
    void clearBoneOverlays();

    void clearLayer();

	void draw();
};

}

#endif // CK_BONELAYER_H
