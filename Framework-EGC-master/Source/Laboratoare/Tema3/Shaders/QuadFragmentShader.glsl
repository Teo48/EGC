#version 330

uniform sampler2D texture_1;
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

void main()
{
	vec4 first_color = texture2D(texture_1, texcoord);
	
	if (first_color.a < 0.5f) {
		discard;
	}

	out_color = first_color;
}