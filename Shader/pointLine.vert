/* Vertex shader */

#version 400 core

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
//uniform vec4 red;

in vec2 in_Position;
in vec4 in_Color;
out vec4 ex_Color;
 
void main(void)
{
	/*mat4 test = mat4(1.0, 0, 0, 0,
					 0, 1.0, 0, 0,
					 0, 0, 1.0, 0,
					 0, 0, 0, 1.0);*/
	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(in_Position.x, in_Position.y, 0.0, 1.0);
	gl_Position = projectionMatrix * modelViewMatrix * vec4(in_Position.x, in_Position.y, 0.0, 1.0);

	/*mat4 mMatrix;
	mMatrix[0] = vec4(1.0, 0, 0, 0);
	mMatrix[1] = vec4(0, 1.0, 0, 0);
	mMatrix[2] = vec4(0, 0, 1.0, 0);
	mMatrix[3] = vec4(0, 0, 0, 1.0);*/

	//vec4 red = vec4(1, 0, 0, 1);
	ex_Color = in_Color;
	//ex_Color = red;
}
