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

#include "RemoveSelection.h"

namespace ck {

RemoveSelection::RemoveSelection(Selection* selection, Triangles* triangles) {
    this->selection = selection;
    this->triangles = triangles;
    selectedVertices = selection->getSelectedVertices();

    firstApply = true;

    for (unsigned int i = 0; i < selectedVertices.size(); i++) {
        vector<int> adjacentTriangles = triangles->getAdjacentTriangles(selectedVertices[i]);
        for (unsigned int j = 0; j < adjacentTriangles.size(); j++)
            trianglesToRemove.insert(adjacentTriangles[j]);
    }
}

void RemoveSelection::apply() {
    for (unsigned int i = 0; i < selectedVertices.size(); i++)
        selection->selectVertex(selectedVertices[i]);

    set<int>::iterator iT;
    set<int>::iterator iV;
    if (firstApply) {
        for (iT = trianglesToRemove.begin(); iT != trianglesToRemove.end(); ++iT) {
            vector<int> verticesTmp = triangles->getIsolatedVertices(*iT);
            for (unsigned int i = 0; i < verticesTmp.size(); i++)
                verticesToRemove.insert(verticesTmp[i]);
            triangles->removeTriangle(*iT);
        }
        for (iV = verticesToRemove.begin(); iV != verticesToRemove.end(); ++iV)
            triangles->removeVertex(*iV);

        firstApply = false;
    }
    else {
        for (iT = trianglesToRemove.begin(); iT != trianglesToRemove.end(); ++iT)
            triangles->removeTriangle(*iT);
        for (iV = verticesToRemove.begin(); iV != verticesToRemove.end(); ++iV)
            triangles->removeVertex(*iV);
    }
}

void RemoveSelection::revert() {
    set<int>::iterator iV;
    for (iV = verticesToRemove.begin(); iV != verticesToRemove.end(); ++iV)
        triangles->restoreVertex(*iV);
    set<int>::iterator iT;
    for (iT = trianglesToRemove.begin(); iT != trianglesToRemove.end(); ++iT)
        triangles->restoreTriangle(*iT);

    for (unsigned int i = 0; i < selectedVertices.size(); i++)
        selection->selectVertex(selectedVertices[i]);
}

}
