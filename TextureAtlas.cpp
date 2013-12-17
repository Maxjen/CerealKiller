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

#include "TextureAtlas.h"

namespace ck {

TextureAtlas::TextureAtlas(size_t width, size_t height, size_t depth) {
    this->width = width;
    this->height = height;
    this->depth = depth;
    used = 0;
    id = 0;

    data = (unsigned char*)calloc(width * height * depth, sizeof(unsigned char));
}

TextureAtlas::~TextureAtlas() {
    //if (data)
    free(data);
    if (id)
        glDeleteTextures(1, &id);
}

void TextureAtlas::setRegion(int x, int y, int regionWidth, int regionHeight, const unsigned char* regionData, int stride) {
    assert(x > 0);
    assert(y > 0);
    assert(x < width - 1);
    assert(x + regionWidth <= width - 1);
    assert(y < height - 1);
    assert(y + regionHeight <= height - 1);

    for (size_t i = 0; i < regionHeight; i++) {
        memcpy(data + ((y + i) * width + x) * sizeof(unsigned char) * depth,
               regionData + (i * stride) * sizeof(unsigned char),
               regionWidth * sizeof(unsigned char) * depth);
    }
}

void TextureAtlas::update() {
    if (id == 0)
        glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Bones::setModelViewMatrix(glm::mat4 modelViewMatrix) {
    this->modelViewMatrix = modelViewMatrix;
}

}
