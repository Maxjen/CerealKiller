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


#include "Layer.h"

namespace ck {

Layer::Layer(RenderManager* renderManager) {
    this->renderManager = renderManager;
}

void Layer::addPoint(int p) {
    points.insert(p);
}

void Layer::removePoint(int p) {
    points.erase(p);
}

void Layer::addLine(int l) {
    lines.insert(l);
}

void Layer::removeLine(int l) {
    lines.erase(l);
}

void Layer::addTriangle(int t) {
    triangles.insert(t);
}

void Layer::removeTriangle(int t) {
    triangles.erase(t);
}

void Layer::clearLayer() {
    points.clear();
    lines.clear();
    triangles.clear();
}

void Layer::draw() {
    set<int>::iterator i;

    for (i = points.begin(); i != points.end(); ++i)
        renderManager->drawPoint(*i);
    for (i = lines.begin(); i != lines.end(); ++i)
        renderManager->drawLine(*i);
    for (i = triangles.begin(); i != triangles.end(); ++i)
        renderManager->drawTriangle(*i);
}

}
