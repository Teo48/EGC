#version 330

uniform sampler2D texture_1;
uniform sampler2D texture_2;

in vec3 frag_normal;
in vec2 frag_texture;
in vec3 frag_color;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec3 out_texture;

void main()
{
	out_normal	= vec4(frag_normal, 1);
	out_texture = vec3(frag_texture, 1);
	vec4 first_color = texture2D(texture_1, frag_texture);
	vec4 second_color = texture2D(texture_2, frag_texture);

	if (first_color.a < 0.5f) {
		discard;
	}

	if (second_color.a < 0.5f) {
		discard;
	}

	out_color = first_color;
}