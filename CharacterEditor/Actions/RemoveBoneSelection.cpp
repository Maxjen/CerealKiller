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

#include "RemoveBoneSelection.h"

namespace ck {

RemoveBoneSelection::RemoveBoneSelection(CharSelection* charSelection, Bones* bones) {
    this->charSelection = charSelection;
    this->bones = bones;
    selectedVertices = charSelection->getSelectedBoneVertices();

    firstApply = true;

    for (unsigned int i = 0; i < selectedVertices.size(); i++) {
        vector<int> adjacentBones = bones->getAdjacentBones(selectedVertices[i]);
        for (unsigned int j = 0; j < adjacentBones.size(); j++)
            bonesToRemove.insert(adjacentBones[j]);
    }
}

void RemoveBoneSelection::apply() {
    for (unsigned int i = 0; i < selectedVertices.size(); i++)
        charSelection->selectBoneVertex(selectedVertices[i]);

    set<int>::iterator iB;
    set<int>::iterator iV;
    if (firstApply) {
        for (iB = bonesToRemove.begin(); iB != bonesToRemove.end(); ++iB) {
            vector<int> verticesTmp = bones->getIsolatedBoneVertices(*iB);
            for (unsigned int i = 0; i < verticesTmp.size(); i++)
                boneVerticesToRemove.insert(verticesTmp[i]);
            bones->removeBone(*iB);
        }
        for (iV = boneVerticesToRemove.begin(); iV != boneVerticesToRemove.end(); ++iV)
            bones->removeBoneVertex(*iV);

        firstApply = false;
    }
    else {
        for (iB = bonesToRemove.begin(); iB != bonesToRemove.end(); ++iB)
            bones->removeBone(*iB);
        for (iV = boneVerticesToRemove.begin(); iV != boneVerticesToRemove.end(); ++iV)
            bones->removeBoneVertex(*iV);
    }
}

void RemoveBoneSelection::revert() {
    set<int>::iterator iV;
    for (iV = boneVerticesToRemove.begin(); iV != boneVerticesToRemove.end(); ++iV)
        bones->restoreBoneVertex(*iV);
    set<int>::iterator iB;
    for (iB = bonesToRemove.begin(); iB != bonesToRemove.end(); ++iB)
        bones->restoreBone(*iB);

    for (unsigned int i = 0; i < selectedVertices.size(); i++)
        charSelection->selectBoneVertex(selectedVertices[i]);
}

}
