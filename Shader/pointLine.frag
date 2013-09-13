/* Fragment shader */

#version 400 core

in vec4 ex_Color;
out vec4 out_Color;

void main()
{
	out_Color = ex_Color;
	//out_Color = vec4(0.0f, 1.0f, 0.0f, 1.0f);
}
