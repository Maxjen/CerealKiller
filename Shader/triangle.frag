/* Fragment shader */

#version 400 core

uniform sampler2D tex;

in vec2 ex_TexCoord;
in vec4 ex_Color;
out vec4 out_Color;

void main()
{
	out_Color = ex_Color * texture(tex, ex_TexCoord);
	//out_Color = ex_Color * texture(tex, vec2(0.5,0.5));
}
