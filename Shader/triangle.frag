/* Fragment shader */

#version 400 core

uniform sampler2D tex;
//uniform int useTexture;

in vec2 ex_TexCoord;
in vec4 ex_Color;
out vec4 out_Color;

void main()
{
	/*if (useTexture == 1) {
		out_Color = ex_Color * texture(tex, ex_TexCoord);
	}
	else {
		out_Color = ex_Color;
	}*/
	out_Color = ex_Color * texture(tex, ex_TexCoord);
}
