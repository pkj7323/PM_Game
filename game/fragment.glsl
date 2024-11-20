#version 460 core

in vec3 outColor;
out vec4 FragColor;
in vec2 TexCoord;

uniform sampler2D Texture;
uniform bool useTexture; // 텍스처 사용 여부를 나타내는 유니폼 변수

void main ()
{
    if (useTexture) {
        FragColor = texture(Texture, TexCoord) * vec4(outColor, 1.0);
    } else {
        FragColor = vec4(outColor, 1.0); // 텍스처가 없을 때 기본 색상 사용
    }
}