#version 460 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_OUT{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
} vs_out[];


out vec3 Normal;
out	vec3 FragPos;
out	vec2 TexCoords;
out vec3 Tangent;


uniform float time;
vec4 explode(vec4 pos,vec3 normal)
{
	float magnitude = 2.0;
	vec3 direction = normal * sin(time) * magnitude;
	return pos + vec4(direction, 0.0);
}
vec3 getNormal()
{
	vec3 v1 = gl_in[0].gl_Position.xyz - gl_in[1].gl_Position.xyz;
	vec3 v2 = gl_in[2].gl_Position.xyz - gl_in[1].gl_Position.xyz;
	return normalize(cross(v1, v2));
}
void main()
{

	Normal = vs_out[0].Normal;
	FragPos = vs_out[0].FragPos;
	Tangent = vs_out[0].Tangent;
	
	vec3 normal = getNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	TexCoords = vs_out[0].TexCoords;
	EmitVertex();
	gl_Position = explode(gl_in[1].gl_Position, normal);
	TexCoords = vs_out[1].TexCoords;
	EmitVertex();
	gl_Position = explode(gl_in[2].gl_Position, normal);
	TexCoords = vs_out[2].TexCoords;
	EmitVertex();
	EndPrimitive();
	
}