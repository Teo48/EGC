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

// TODO: output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main()
{
	// TODO: send output to fragment shader
	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture = v_texture;
	frag_color = v_color + vec3(sin(Clock), 
								cos(Clock), 
								sin(Clock) * sin(Clock) + 2 * sin(Clock) * cos(Clock) + cos(Clock) * cos(Clock));

	// TODO: compute gl_Position
	// Modific pozitia dupa functia: (sin(Clock) + cos(Clock))^2
	gl_Position = Projection * (View + mat4(sin(Clock) * sin(Clock)) + mat4(2 * cos(Clock) * sin(Clock)) + 
									   mat4(cos(Clock) * cos(Clock))) * Model * vec4(v_position, 1.0);
}
