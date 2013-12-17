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

#include "CharSelection.h"

namespace ck {

CharSelection::CharSelection(RenderManager* renderManager, Bones* bones) {
    this->renderManager = renderManager;
    this->bones = bones;
}

CharSelection::~CharSelection() {
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

void CharSelection::clear() {
    set<int>::iterator it;
    for (it = selectedBoneVertices.begin(); it != selectedBoneVertices.end(); ++it) {
        bones->selectBoneVertex(*it);
    }

    selectedBoneVertices.clear();
}

void CharSelection::selectBoneVertex(int v) {
    set<int>::iterator it = selectedBoneVertices.find(v);
    if (it == selectedBoneVertices.end())
        selectedBoneVertices.insert(v);
    else
        selectedBoneVertices.erase(it);
    bones->selectBoneVertex(v);
}

/*void CharSelection::addBoneVertex(int v) {
}

void CharSelection::removeBoneVertex(int v) {
}*/

vector<int> CharSelection::getSelectedBoneVertices() {
    vector<int> result;
    set<int>::iterator it;
    for (it = selectedBoneVertices.begin(); it != selectedBoneVertices.end(); ++it) {
        result.push_back(*it);
    }
    return result;
}

/*void CharSelection::updateSelection() {
    map<int, int>::iterator iP;
    for (iP = selectedVertices.begin(); iP != selectedVertices.end(); ++iP)
        renderManager->setPointPosition(iP->second, triangles->getVertexPositionX(iP->first), triangles->getVertexPositionY(iP->first));

    map<SelectionEdge, SelectionEdgeData>::iterator iL;
    for (iL = edges.begin(); iL != edges.end(); ++iL) {
        renderManager->setLineVertexPosition(iL->second.indexV1, triangles->getVertexPositionX(iL->first.v1), triangles->getVertexPositionY(iL->first.v1));
        renderManager->setLineVertexPosition(iL->second.indexV2, triangles->getVertexPositionX(iL->first.v2), triangles->getVertexPositionY(iL->first.v2));
    }
}*/

bool CharSelection::empty() const {
    return selectedBoneVertices.empty();
}

/*void CharSelection::draw() {
    map<int, int>::iterator iP;
    for (iP = selectedVertices.begin(); iP != selectedVertices.end(); ++iP)
        renderManager->drawPoint(iP->second);

    map<SelectionEdge, SelectionEdgeData>::iterator iL;
    for (iL = edges.begin(); iL != edges.end(); ++iL)
        renderManager->drawLine(iL->second.indexLine);
}*/

}
