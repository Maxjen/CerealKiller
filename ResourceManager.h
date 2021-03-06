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


#ifndef CK_RESOURCEMANAGER_H
#define CK_RESOURCEMANAGER_H

/*#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>*/
#include <GL/glew.h>

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

#include <map>
#include <string>

using std::map;
using std::string;

namespace ck {

class ResourceManager;

// only used in ResourceManager
struct TextureInternal {
    string name;
    unsigned int id;
    int width, height;
    int counter;
};

class Texture {
private:
    ResourceManager* resourceManager;
public:
    string* name;
	unsigned int id;
	int width, height;

    Texture(ResourceManager* resourceManager);
    ~Texture();
};

class ResourceManager {
private:
    map<string, TextureInternal> textures;
public:
    Texture* getTexture(const char* textureName);

    // reduces the counter of a texture and deletes the texture if it becomes 0
	void decreaseTextureCounter(const char* textureName);
};

}

#endif // CK_RESOURCEMANAGER_H
