#version 460 core
layout (triangles) in;
in VS_OUT {
    vec2 texCoords;
} gs_in[];
layout (triangle_strip, max_vertices = 3) out;
out vec2 texCoords;

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
	vec3 normal = getNormal();

	gl_Position = explode(gl_in[0].gl_Position, normal);
	texCoords = gs_in[0].texCoords;
	EmitVertex();
	gl_Position = explode(gl_in[1].gl_Position, normal);
}