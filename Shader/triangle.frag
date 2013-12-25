/* Fragment shader */

#version 300 es

uniform sampler2D tex;
//uniform int useTexture;

in mediump vec2 ex_TexCoord;
in lowp vec4 ex_Color;
out lowp vec4 out_Color;

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
