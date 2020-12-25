#version 330

uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
in vec2 texcoord;
in vec3 frag_color;
uniform float Clock;


layout(location = 0) out vec4 out_color;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	vec4 first_color = texture2D(texture_1, texcoord);
	vec4 second_color = texture2D(texture_2, texcoord);

	if (first_color.a < 0.5f) {
		discard;
	}

	if (second_color.a < 0.5f) {
		discard;
	}

	out_color = first_color * vec4(frag_color, 0.5f);
}