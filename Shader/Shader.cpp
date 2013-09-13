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


#include "Shader.h"

namespace ck {

Shader::Shader() {
    programId = 0;
}

Shader::~Shader() {
    glDeleteProgram(programId);
}

void Shader::bind() {
    glUseProgram(programId);

    //Check for error
    /*GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error binding shader! %s\n", gluErrorString( error ) );
        printProgramLog( mProgramID );
        return false;
    }

    return true;*/
}

void Shader::unbind() {
    glUseProgram(0);
}

void Shader::printProgramLog(GLuint program) {
    // Make sure name is shader
    if (glIsProgram(program)) {
        // Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        // Get info string length
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // Allocate string
        char* infoLog = new char[maxLength];

        // Get info log
        glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
        if (infoLogLength > 0){
            // Print Log
            printf("%s\n", infoLog);
        }

        // Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a program\n", program);
    }
}

void Shader::printShaderLog(GLuint shader) {
    //Make sure name is shader
    if (glIsShader(shader)) {
        // Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        // Get info string length
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

        // Allocate string
        char* infoLog = new char[maxLength];

        //Get info log
        glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
        if(infoLogLength > 0) {
            // Print Log
            printf("%s\n", infoLog);
        }

        //Deallocate string
        delete[] infoLog;
    }
    else {
        printf("Name %d is not a shader\n", shader);
    }
}

GLuint Shader::loadShader(const char* filename, GLenum shaderType) {
    GLuint shaderId = glCreateShader(shaderType);

    string shaderString = fileToString(filename);
    const GLchar* shaderSource = shaderString.c_str();
    glShaderSource(shaderId, 1, (const GLchar**)&shaderSource, NULL);

    glCompileShader(shaderId);

    // Check shader for errors
    GLint shaderCompiled = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &shaderCompiled);
    if (shaderCompiled != GL_TRUE)
    {
        printf("Unable to compile shader %d!\n\nSource:\n%s\n", shaderId, shaderSource);
        printShaderLog(shaderId);
        glDeleteShader(shaderId);
        shaderId = 0;
    }

    return shaderId;
}

string Shader::fileToString(const char* filename) {
  FILE *fp = fopen(filename, "rb");
  if (fp) {
    string contents;
    fseek(fp, 0, SEEK_END);
    contents.resize(ftell(fp));
    rewind(fp);
    fread(&contents[0], 1, contents.size(), fp);
    fclose(fp);
    return(contents);
  }
  throw(errno); // check how throw works
}

}

