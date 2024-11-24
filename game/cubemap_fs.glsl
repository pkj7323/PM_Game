#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    float ratio = 1.00 / 1.33; // ���� �ݻ� ��� 1.52 �� 1.33 ���� 1.309 ���̾Ƹ�� 2.42
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);// reflect�ƴ� refract�� ����
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}