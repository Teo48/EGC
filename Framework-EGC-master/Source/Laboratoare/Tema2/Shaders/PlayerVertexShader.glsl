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

	if (frag_position.y >= 0.15f) {
		frag_color = vec3(1.f, 0.f, 0.13f);
	} else if (frag_position.y >= 0.f && frag_position.y < 0.15f) {
		frag_color = vec3(0.f, 0.f, 0.f);
	} else if (frag_position.y < 0.f) {
		//frag_color = vec3(0.f, 0.4667f, 1.f);
		frag_color = vec3(1.f, 1.f, 1.f);
	}

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
