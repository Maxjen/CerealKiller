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

#include "Selection.h"

namespace ck {

Selection::Selection(RenderManager* renderManager, Triangles* triangles) {
    this->renderManager = renderManager;
    this->triangles = triangles;
}

Selection::~Selection() {
    /*map<SelectionEdge, SelectionEdgeData>::iterator iL;
    for (iL = edges.begin(); iL != edges.end(); ++iL) {
        renderManager->removeLine(iL->second.indexLine);
        renderManager->removeLineVertex(iL->second.indexV1);
        renderManager->removeLineVertex(iL->second.indexV2);
    }

    map<int, int>::iterator iP;
    for (iP = selectedVertices.begin(); iP != selectedVertices.end(); ++iP)
        renderManager->removePoint(iP->second);

    edges.clear();
    selectedVertices.clear();*/
    clear();
}

void Selection::clear() {
    map<SelectionEdge, SelectionEdgeData>::iterator iL;
    for (iL = edges.begin(); iL != edges.end(); ++iL) {
        renderManager->removeLine(iL->second.indexLine);
        renderManager->removeLineVertex(iL->second.indexV1);
        renderManager->removeLineVertex(iL->second.indexV2);
    }

    map<int, int>::iterator iP;
    for (iP = selectedVertices.begin(); iP != selectedVertices.end(); ++iP)
        renderManager->removePoint(iP->second);

    edges.clear();
    selectedVertices.clear();
}

void Selection::selectVertex(int v) {
    map<int, int>::iterator it = selectedVertices.find(v);
    if(it == selectedVertices.end())
        addVertex(v);
    else
        removeVertex(v);
}

void Selection::addVertex(int v) {
    selectedVertices[v] = renderManager->addPoint(triangles->getVertexPositionX(v), triangles->getVertexPositionY(v), 255, 255, 255, 255);

    vector<int> adjacentVertices = triangles->getAdjacentVertices(v);
    for (unsigned int i = 0; i < adjacentVertices.size(); i++) {
        SelectionEdge key;
        int vTmp = adjacentVertices[i];
        key.v1 = v < vTmp ? v : vTmp;
        key.v2 = v > vTmp ? v : vTmp;

        // add edge unless it already exists
        map<SelectionEdge, SelectionEdgeData>::iterator it = edges.find(key);
        if (it == edges.end()) {
            if (v < vTmp) {
                edges[key].v1Selected = true;
                edges[key].v2Selected = false;
                edges[key].indexV1 = renderManager->addLineVertex(triangles->getVertexPositionX(v),triangles->getVertexPositionY(v), 255, 255, 255, 255);
                edges[key].indexV2 = renderManager->addLineVertex(triangles->getVertexPositionX(vTmp),triangles->getVertexPositionY(vTmp), 255, 255, 255, 0);
            }
            else {
                edges[key].v1Selected = false;
                edges[key].v2Selected = true;
                edges[key].indexV1 = renderManager->addLineVertex(triangles->getVertexPositionX(vTmp),triangles->getVertexPositionY(vTmp), 255, 255, 255, 0);
                edges[key].indexV2 = renderManager->addLineVertex(triangles->getVertexPositionX(v),triangles->getVertexPositionY(v), 255, 255, 255, 255);
            }
            edges[key].indexLine = renderManager->addLine(edges[key].indexV1, edges[key].indexV2);
        }
        else {
            if (v < vTmp) {
                edges[key].v1Selected = true;
                renderManager->setLineVertexColor(edges[key].indexV1, 255, 255, 255, 255);
            }
            else {
                edges[key].v2Selected = true;
                renderManager->setLineVertexColor(edges[key].indexV2, 255, 255, 255, 255);
            }
        }
    }
}

void Selection::removeVertex(int v) {
    renderManager->removePoint(selectedVertices[v]);
    selectedVertices.erase(v);

    map<SelectionEdge, SelectionEdgeData>::iterator iL = edges.begin();
    while (iL != edges.end()) {
        if (iL->first.v1 == v) {
            iL->second.v1Selected = false;
            if (iL->second.v2Selected == false) {
                renderManager->removeLine(iL->second.indexLine);
                renderManager->removeLineVertex(iL->second.indexV1);
                renderManager->removeLineVertex(iL->second.indexV2);
                edges.erase(iL++);
            }
            else {
                renderManager->setLineVertexColor(iL->second.indexV1, 255, 255, 255, 0);
                ++iL;
            }
        }
        else if (iL->first.v2 == v) {
            iL->second.v2Selected = false;
            if(iL->second.v1Selected == false) {
                renderManager->removeLine(iL->second.indexLine);
                renderManager->removeLineVertex(iL->second.indexV1);
                renderManager->removeLineVertex(iL->second.indexV2);
                edges.erase(iL++);
            }
            else {
                renderManager->setLineVertexColor(iL->second.indexV2, 255, 255, 255, 0);
                ++iL;
            }
        }
        else
            ++iL;
    }
}

vector<int> Selection::getSelectedVertices() {
    vector<int> result;
    map<int, int>::iterator it;
    for (it = selectedVertices.begin(); it != selectedVertices.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

void Selection::updateSelection() {
    map<int, int>::iterator iP;
    for (iP = selectedVertices.begin(); iP != selectedVertices.end(); ++iP)
        renderManager->setPointPosition(iP->second, triangles->getVertexPositionX(iP->first), triangles->getVertexPositionY(iP->first));

    map<SelectionEdge, SelectionEdgeData>::iterator iL;
    for (iL = edges.begin(); iL != edges.end(); ++iL) {
        renderManager->setLineVertexPosition(iL->second.indexV1, triangles->getVertexPositionX(iL->first.v1), triangles->getVertexPositionY(iL->first.v1));
        renderManager->setLineVertexPosition(iL->second.indexV2, triangles->getVertexPositionX(iL->first.v2), triangles->getVertexPositionY(iL->first.v2));
    }
}

bool Selection::empty() const {
    return selectedVertices.empty();
}

void Selection::draw() {
    map<int, int>::iterator iP;
    for (iP = selectedVertices.begin(); iP != selectedVertices.end(); ++iP)
        renderManager->drawPoint(iP->second);

    map<SelectionEdge, SelectionEdgeData>::iterator iL;
    for (iL = edges.begin(); iL != edges.end(); ++iL)
        renderManager->drawLine(iL->second.indexLine);
}

}
