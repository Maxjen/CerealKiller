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


#include "BoneLayer.h"

namespace ck {

BoneLayer::BoneLayer(RenderManager* renderManager, Bones* bones) {
    this->renderManager = renderManager;
    this->bones = bones;
}

void BoneLayer::addPoint(int p) {
    points.insert(p);
}

void BoneLayer::removePoint(int p) {
    points.erase(p);
}

void BoneLayer::addLine(int l) {
    lines.insert(l);
}

void BoneLayer::removeLine(int l) {
    lines.erase(l);
}

void BoneLayer::addTriangle(int t) {
    triangles.insert(t);
}

void BoneLayer::removeTriangle(int t) {
    triangles.erase(t);
}

int BoneLayer::addBoneOverlay(float x, float y, float angle, float length) {
    BoneOverlay b;
    b.x = x;
    b.y = y;
    b.angle = angle;
    b.length = length;
    boneOverlays.push_back(b);
    return boneOverlays.size() - 1;
}

void BoneLayer::setBoneOverlayPosition(int b, float x, float y) {
    boneOverlays[b].x = x;
    boneOverlays[b].y = y;
}

void BoneLayer::setBoneOverlayAngleLength(int b, float angle, float length) {
    boneOverlays[b].angle = angle;
    boneOverlays[b].length = length;
}

void BoneLayer::clearBoneOverlays() {
    boneOverlays.clear();
}

void BoneLayer::clearLayer() {
    points.clear();
    lines.clear();
    triangles.clear();
    boneOverlays.clear();
}

void BoneLayer::draw() {
    set<int>::iterator i;

    for (i = points.begin(); i != points.end(); ++i)
        renderManager->drawPoint(*i);
    for (i = lines.begin(); i != lines.end(); ++i)
        renderManager->drawLine(*i);
    for (i = triangles.begin(); i != triangles.end(); ++i)
        renderManager->drawTriangle(*i);

    for (unsigned int i = 0; i < boneOverlays.size(); i++)
        bones->drawBone(boneOverlays[i].x, boneOverlays[i].y, boneOverlays[i].angle, boneOverlays[i].length, true, true);
}

}
