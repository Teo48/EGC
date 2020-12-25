#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
out vec2 texcoord;
out vec3 frag_color;
uniform int Collide;
uniform int Color;

void main() {
	texcoord = v_texture_coord;
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);

	if (Color == 0) {
		frag_color = vec3(0.f, 0.4667f, 1.f);
	};

	if (Color == 1) {
		frag_color = vec3(0.f, 0.0167f, 1.f);
	}

	if (Color == 2) {
		frag_color = vec3(1.f, 0.f, 0.f);
	}

	if (Color == 3) {
		frag_color = vec3(1.f, 1.f, 0.f);
	}

	if (Color == 4) {
		frag_color = vec3(1.f, 0.4f, 0.f);
	}

	if (Color == 5) {
		frag_color = vec3(0.0433f, 0.65f, 0.f);
	}

	if (Color == 6) {
		frag_color = vec3(1.f, 1.f, 1.f);
	}

	if (Color == 7) {
		frag_color = vec3(0.f, 1.f, 0.75f);
	}

	if (Collide == 1 && Color != 6) {
		frag_color = vec3(0.6167f, 0.f, 1.f);
	}
}