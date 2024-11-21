layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoord;


uniform mat4 world;//�� ��ü���� ��ȯ
uniform mat4 view;//ī�޶�
uniform mat4 projection;//����

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