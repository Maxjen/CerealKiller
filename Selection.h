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

#ifndef CK_SELECTION_H
#define CK_SELECTION_H

#include "RenderManager.h"
#include "Triangles.h"

namespace ck {

struct SelectionEdge {
    int v1, v2;

    bool operator<(const SelectionEdge& e) const {
        return (v1 < e.v1) || (v1 == e.v1 && v2 < e.v2);
    }
};

struct SelectionEdgeData {
    bool v1Selected, v2Selected;
    int indexV1, indexV2, indexLine;
    //int triangleCount;
};

class Selection {
private:
    RenderManager* renderManager;
    Triangles* triangles;

    //set<int> selectedVertices;

    // maps index of vertex to index of point in renderManager
    map<int, int> selectedVertices;

    map<SelectionEdge, SelectionEdgeData> edges;

    // maybe make public
    void addVertex(int v);
    void removeVertex(int v);
public:
    Selection(RenderManager* renderManager, Triangles* triangles);
    ~Selection();

    void selectVertex(int v);
    vector<int> getSelectedVertices();

    void updateSelection();
    bool empty() const;

    void draw();
};

}

#endif // CK_SELECTION_H
