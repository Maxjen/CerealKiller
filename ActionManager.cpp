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

#include "ActionManager.h"

namespace ck {

ActionManager::ActionManager() {
}

ActionManager::~ActionManager() {
    /*while(!undoStack.empty()) {
        delete undoStack.top();
        undoStack.pop();
    }
    while(!redoStack.empty()) {
        delete redoStack.top();
        redoStack.pop();
    }*/
    clear();
}

void ActionManager::clear() {
    while(!undoStack.empty()) {
        delete undoStack.top();
        undoStack.pop();
    }
    while(!redoStack.empty()) {
        delete redoStack.top();
        redoStack.pop();
    }
}

void ActionManager::pushAction(Action* newAction) {
    newAction->apply();
    undoStack.push(newAction);
    while(!redoStack.empty()) {
        delete redoStack.top();
        redoStack.pop();
    }
}

void ActionManager::undoAction() {
    if (!undoStack.empty()) {
        undoStack.top()->revert();
        redoStack.push(undoStack.top());
        undoStack.pop();
    }
}

void ActionManager::redoAction() {
    if (!redoStack.empty()) {
        redoStack.top()->apply();
        undoStack.push(redoStack.top());
        redoStack.pop();
    }
}

}
