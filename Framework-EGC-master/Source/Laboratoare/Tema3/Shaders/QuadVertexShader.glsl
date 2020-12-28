#version 330

// TODO: get vertex attributes from each location

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;

// TODO: output values to fragment shader

out vec2 texcoord;
void main()
{
	texcoord = v_texture_coord;
	gl_Position = Model * vec4(v_position, 1.0);
}
