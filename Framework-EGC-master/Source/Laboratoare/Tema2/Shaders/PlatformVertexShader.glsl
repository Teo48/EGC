#version 330

// TODO: get vertex attributes from each location

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Clock;
uniform int Collide;
uniform int Color;
// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main()
{
	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture = v_texture;

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
		frag_color = vec3(0.f, 0.f, 0.f);
	}

	if (Color == 7) {
		frag_color = vec3(0.f, 1.f, 0.75f);
	}

	if (Collide == 1) {
		frag_color = vec3(0.6167f, 0.f, 1.f);
	}
	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
