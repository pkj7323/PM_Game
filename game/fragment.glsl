#version 460 core

in vec3 outColor;
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform bool useTexture; // �ؽ�ó ��� ���θ� ��Ÿ���� ������ ����

void main ()
{
    if (useTexture) {
        FragColor = texture(Texture, TexCoord) * vec4(outColor, 1.0);
    } else {
        FragColor = vec4(outColor, 1.0); // �ؽ�ó�� ���� �� �⺻ ���� ���
    }
}