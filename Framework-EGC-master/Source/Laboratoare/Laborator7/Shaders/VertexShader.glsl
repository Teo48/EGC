#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Uniforms for light properties
uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// Output value to fragment shader
out vec3 color;

void main()
{
	// TODO: compute world space vectors
	// In video arata cast implicit de la vec4 la vec3, doar ca am incercat asa si nu imi afisa nimic(Cel mai probabil
	// castul e facut prost de la vec4 la vec3, asa ca extrag eu componentele x, y, z.
	vec3 world_position = (Model * vec4(v_position, 1)).xyz;
	vec3 world_normal	= normalize(mat3(Model) * normalize(v_normal));
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));
	
	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(world_normal, L), 0.f);

	// TODO: compute specular light component
	float specular_light = 0.1f;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(V, R), 0.f), material_shininess);
	}

	// TODO: compute light

	float d	= distance(light_position, v_position);
	float attenuation_factor = 1 / (1 + 0.2 * d + 0.1 * d * d);

	// TODO: send color light output to fragment shader
	color = object_color * (ambient_light + attenuation_factor * (diffuse_light + specular_light));

	gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
