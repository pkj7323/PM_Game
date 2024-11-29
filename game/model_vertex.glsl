#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in vec3 aBoneIDs;
layout (location = 6) in vec3 aWeights;

#define NR_POINT_LIGHTS 4



out VS_OUT{
	vec3 FragPos;
    vec2 TexCoords;
	vec3 TangentSpotLightPos;
	vec3 TangentPointLightPos[NR_POINT_LIGHTS];
    vec3 TangentViewPos;
    vec3 TangentFragPos;
} vs_out;

uniform vec3 PointLightPos[NR_POINT_LIGHTS];
uniform vec3 SpotLightPos;
uniform vec3 viewPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;



void main()
{
	vs_out.FragPos = vec3(model * vec4(aPos, 1.0));   
    vs_out.TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * aTangent);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T, B, N));    

    for (int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        vs_out.TangentPointLightPos[i] = TBN * PointLightPos[i];
    }
    vs_out.TangentSpotLightPos = TBN * SpotLightPos;
    vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
        
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
}