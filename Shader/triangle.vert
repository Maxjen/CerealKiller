/* Vertex shader */

#version 300 es

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;

in mediump vec2 in_Position;
in mediump vec2 in_TexCoord;
in lowp vec4 in_Color;
out mediump vec2 ex_TexCoord;
out lowp vec4 ex_Color;
 
void main(void)
{
	/*vec4 v = vec4(gl_Vertex);
	v.x += sin(waveWidth * v.x + waveTime) * cos(waveWidth * v.y + waveTime) * waveHeight;
	gl_Position = gl_ModelViewProjectionMatrix * v;*/

	//gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(in_Position.x, in_Position.y, 0.0, 1.0);
	gl_Position = projectionMatrix * modelViewMatrix * vec4(in_Position.x, in_Position.y, 0.0, 1.0);
	ex_TexCoord = in_TexCoord;
	ex_Color = in_Color;
}
