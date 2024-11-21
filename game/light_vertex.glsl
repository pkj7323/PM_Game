layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;


uniform mat4 world;//각 객체별로 변환
uniform mat4 view;//카메라
uniform mat4 projection;//투영

out vec3 FragPos;
out vec2 TexCoord;
out vec3 Normal;

void main()
{
	gl_Position = projection * view * world * vec4(vPos, 1.0);

	FragPos = vec3(world * vec4(vPos,1.0f));

	TexCoord = vTexCoord;
	Normal = vNormal;
}