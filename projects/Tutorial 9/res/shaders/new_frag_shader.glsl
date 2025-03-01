#version 440


layout(location = 0) in vec3 inWorldPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNormal;
layout(location = 3) in vec2 inUV;

// We output a single color to the color buffer
layout(location = 0) out vec4 frag_color;

////////////////////////////////////////////////////////////////
/////////////// Frame Level Uniforms ///////////////////////////
////////////////////////////////////////////////////////////////

// The position of the camera in world space
uniform vec3  u_CamPos;

////////////////////////////////////////////////////////////////
/////////////// Instance Level Uniforms ////////////////////////
////////////////////////////////////////////////////////////////

// Represents a collection of attributes that would define a material
// For instance, you can think of this like material settings in 
// Unity
struct Material {
	sampler2D Diffuse;
	sampler2D Specular;
};
// Create a uniform for the material
uniform Material u_Material;

////////////////////////////////////////////////////////////////
///////////// Application Level Uniforms ///////////////////////
////////////////////////////////////////////////////////////////

#include "fragments/multiple_point_lights.glsl"

const float LOG_MAX = 2.40823996531;

// https://learnopengl.com/Advanced-Lighting/Advanced-Lighting
void main() {
	// Normalize our input normal
	vec3 normal = normalize(inNormal);

	vec3 toEye = normalize(u_CamPos - inWorldPos);
	vec3 environmentDir = reflect(-toEye, normal);
	vec3 reflected = SampleEnvironmentMap(environmentDir);

	float textureSpecular=0.30f;

	// Will accumulate the contributions of all lights on this fragment
	// This is defined in the fragment file "multiple_point_lights.glsl"
	//vec3 lightAccumulation = CalcAllLightContribution(inWorldPos, normal, u_CamPos, u_Material.Shininess);
	vec3 lightAccumulation = CalcAllLightContribution(inWorldPos, normal, u_CamPos, textureSpecular);

	// Get the albedo from the diffuse / albedo map
	//vec4 textureColor = texture(u_Material.Diffuse, inUV);

	vec4 textureColor = texture(u_Material.Specular, inUV);

	// combine for the final result
	vec3 result = lightAccumulation  * inColor * textureColor.rgb;

	frag_color = vec4(mix(result, reflected, textureSpecular), textureColor);
}