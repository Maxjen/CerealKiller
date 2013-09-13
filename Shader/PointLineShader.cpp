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


#include "PointLineShader.h"

namespace ck {

PointLineShader::PointLineShader() {
    GLuint vertexShaderId = loadShader("Shader/pointLine.vert", GL_VERTEX_SHADER);
    GLuint fragmentShaderId = loadShader("Shader/pointLine.frag", GL_FRAGMENT_SHADER);

    programId = glCreateProgram();
    glAttachShader(programId, vertexShaderId);
    glAttachShader(programId, fragmentShaderId);
    glLinkProgram(programId);

    // Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programId, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        printf("Error linking program %d!\n", programId);
        printProgramLog(programId);
        glDeleteProgram(programId);
        programId = 0;
        //return false;
    }

    glDetachShader(programId, vertexShaderId);
    glDetachShader(programId, fragmentShaderId);

    glDeleteShader(vertexShaderId);
    glDeleteShader(fragmentShaderId);

    glUseProgram(programId);

    positionLocation = glGetAttribLocation(programId, "in_Position");
    if (positionLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "in_Position");
    }

    colorLocation = glGetAttribLocation(programId, "in_Color");
    if (colorLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "in_Color");
    }

    projectionMatrixLocation = glGetUniformLocation(programId, "projectionMatrix");
    if (projectionMatrixLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "projectionMatrix");
    }

    modelViewMatrixLocation = glGetUniformLocation(programId, "modelViewMatrix");
    if (modelViewMatrixLocation == -1) {
        printf("%s is not a valid glsl program variable!\n", "modelViewMatrix");
    }

    glUseProgram(0);
}

void PointLineShader::setProjectionMatrix(glm::mat4 projectionMatrix) {
    glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}

void PointLineShader::setModelViewMatrix(glm::mat4 modelViewMatrix) {
    glUniformMatrix4fv(modelViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
}

void PointLineShader::setPositionPointer(GLsizei stride, const GLvoid* offset) {
    glVertexAttribPointer(positionLocation, 2, GL_FLOAT, GL_FALSE, stride, offset);

    /*glVertexAttribPointer(pointLinePositionLocation, 2, GL_FLOAT, GL_FALSE, sizeof(PointLineVertex), 0);
    glVertexAttribPointer(pointLineColorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(PointLineVertex), (GLvoid*)(2 * sizeof(float)));*/
}

void PointLineShader::setColorPointer(GLsizei stride, const GLvoid* offset) {
    glVertexAttribPointer(colorLocation, 4, GL_UNSIGNED_BYTE, GL_TRUE, stride, offset);
}

void PointLineShader::enablePositionPointer() {
    glEnableVertexAttribArray(positionLocation);
}

void PointLineShader::enableColorPointer() {
    glEnableVertexAttribArray(colorLocation);
}

void PointLineShader::disablePositionPointer() {
    glDisableVertexAttribArray(positionLocation);
}

void PointLineShader::disableColorPointer() {
    glDisableVertexAttribArray(colorLocation);
}

}

