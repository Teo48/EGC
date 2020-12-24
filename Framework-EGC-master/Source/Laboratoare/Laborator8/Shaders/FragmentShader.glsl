#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

uniform int is_spotlight;
uniform float cut_off;

layout(location = 0) out vec4 out_color;

void main()
{	
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));
	vec3 N = normalize(world_normal);
	// TODO: define ambient light component
	float ambient_light = 0.25;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max(dot(normalize(N), L), 0.f);

	// TODO: compute specular light component
	float specular_light = 0;

	if (diffuse_light > 0)
	{
		specular_light = material_ks * pow(max(dot(N, H), 0), material_shininess);
	}

	// TODO: compute light
	float d	= distance(light_position, world_position);
	float attenuation_factor = 1 / (1 + 0.2 * d + 0.1 * d * d);
	float light = ambient_light + attenuation_factor * (diffuse_light + specular_light);

	if (is_spotlight == 1) {
		float cut_off_angle = radians(cut_off);
		float spot_light = dot(-L, light_direction);
		float spot_light_limit = cos(cut_off_angle);
		
		if (spot_light > spot_light_limit) {
			// Quadratic attenuation
			float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
			float light_att_factor = pow(linear_att, 2);
			light = ambient_light + light_att_factor * (diffuse_light + specular_light);
		} else {
			light = ambient_light;
		}
	}

	// TODO: write pixel out color
	out_color = vec4(object_color * light, 1.f);
}