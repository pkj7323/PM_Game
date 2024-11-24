#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
uniform samplerCube skybox;

void main()
{    
    float ratio = 1.00 / 1.33; // 유리 반사 계수 1.52 물 1.33 얼음 1.309 다이아몬드 2.42
    vec3 I = normalize(Position - cameraPos);
    vec3 R = refract(I, normalize(Normal), ratio);// reflect아님 refract임 주의
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}