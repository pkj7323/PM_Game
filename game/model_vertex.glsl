#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec3 aBoneIDs;
layout (location = 6) in vec3 aWeights;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 Tangent;

out VS_OUT
{
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
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    TexCoords = aTexCoords;
    Tangent = mat3(transpose(inverse(model))) * aTangent;

    vs_out.FragPos = FragPos;
    vs_out.Normal = Normal;
    vs_out.TexCoords = TexCoords;
    vs_out.Tangent = Tangent;


    gl_Position = projection * view * vec4(FragPos, 1.0);
}