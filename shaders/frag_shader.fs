/*
	This is a simple fragment shader.
*/

#version 330

out vec4 fragColor;
in vec2 texCoord_vf;
in vec4 color_vf;
uniform sampler2D tex;

void main(void)
{
	
	fragColor = color_vf * texture(tex, texCoord_vf);
}
