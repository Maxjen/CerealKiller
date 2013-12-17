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


#include "ResourceManager.h"

namespace ck {

Texture::Texture(ResourceManager *resourceManager) {
    this->resourceManager = resourceManager;
}

Texture::~Texture() {
    resourceManager->decreaseTextureCounter(name->c_str());
}

Texture* ResourceManager::getTexture(const char* textureName) {
    map<string, TextureInternal>::iterator it = textures.find(textureName);
    if (it != textures.end())
        textures[textureName].counter++;
	
    //if(textures[textureName].counter == 1) {
    else {
        textures[textureName].counter = 1;
        textures[textureName].name = textureName;

        SDL_Surface* textureImage;
        if (!(textureImage = IMG_Load(textureName))) {
            fprintf(stderr, "INFO: couldn't load image from file. Exit\n");
            return 0;
        }

		glGenTextures(1, &(textures[textureName].id));
		glBindTexture(GL_TEXTURE_2D, textures[textureName].id);
        textures[textureName].width = textureImage->w;
        textures[textureName].height = textureImage->h;
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                        textureImage->w,
                        textureImage->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        SDL_FreeSurface(textureImage);
	}
    Texture* result = new Texture(this);
    result->name = &textures[textureName].name;
    result->id = textures[textureName].id;
    result->width = textures[textureName].width;
    result->height = textures[textureName].height;
    return result;
}

void ResourceManager::decreaseTextureCounter(const char* textureName) {
    textures[textureName].counter--;
    if(textures[textureName].counter == 0) {
		glDeleteTextures(1, &(textures[textureName].id));
		textures.erase(textureName);
    }
}

}

