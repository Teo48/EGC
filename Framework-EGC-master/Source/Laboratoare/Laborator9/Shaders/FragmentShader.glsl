#version 330
 
uniform sampler2D texture_1;
uniform sampler2D texture_2;
 
in vec2 texcoord;

layout(location = 0) out vec4 out_color;

uniform int is_mixed;

void main()
{
	// TODO : calculate the out_color using the texture2D() function
	// LE: Fix pentru exercitiul 8, nu dadeam discard pentru a doua culoare
	vec4 first_color = texture2D(texture_1, texcoord);
	vec4 second_color = texture2D(texture_2, texcoord);

	if (first_color.a < 0.5f) {
		discard;
	}

	if (second_color.a < 0.5f) {
		discard;
	}

	if (is_mixed == 1) {
		out_color = mix(first_color, second_color, 0.5f);
	} else {
		out_color = first_color;
	}
}