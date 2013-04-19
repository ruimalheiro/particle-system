/*
	The directive layout(location=?) "hard-codes" the location of the attributes	
*/

#version 330

layout (location=0) in vec4 vertex;
layout (location=1) in vec2 texCoord;
layout (location=2) in vec3 normal;
out vec2 texCoord_vf;
out vec4 color_vf;

uniform mat4 pMatrix;
uniform mat4 vMatrix;
uniform mat4 mMatrix;
uniform mat3 nMatrix;

uniform vec3 lightDir;
uniform vec4 lightIntensity;
uniform vec4 ambientIntensity;
uniform vec4 diffuseColor;

void main()
{
	texCoord_vf = texCoord;
	
	vec3 transfNormal = normalize(nMatrix * normal);
	vec3 normalizedLightDir = normalize(lightDir);
	float cosAng = dot(transfNormal, normalizedLightDir);
	cosAng = clamp(cosAng, 0, 1);
	
	color_vf = (diffuseColor * lightIntensity * cosAng) + (diffuseColor * ambientIntensity);
	gl_Position = pMatrix * vMatrix * mMatrix * vertex;
}

