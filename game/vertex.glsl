#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec3 aBoneIDs;
layout (location = 6) in vec3 aWeights;


out VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
} vs_out;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.FragPos = vec3(model * vec4(aPos, 1.0));
    vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;  
    vs_out.TexCoords = aTexCoords;
    vs_out.Tangent = mat3(transpose(inverse(model))) * aTangent;



    gl_Position = projection * view * vec4(vs_out.FragPos, 1.0);
}