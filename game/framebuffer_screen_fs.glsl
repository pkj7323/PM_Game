#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

const float offset = 1.0 / 300.0; // 텍스처의 크기에 따라 조정// 간단히 원하는대로 정할 수 있는 상수 값
void main()
{
	vec2 offsets[9] = vec2[](
			vec2(-offset,  offset), // 좌측 상단
			vec2( 0.0f,    offset), // 중앙 상단
			vec2( offset,  offset), // 우측 상단
			vec2(-offset,  0.0f),   // 좌측 중앙
			vec2( 0.0f,    0.0f),   // 정중앙
			vec2( offset,  0.0f),   // 우측 중앙
			vec2(-offset, -offset), // 좌측 하단
			vec2( 0.0f,   -offset), // 중앙 하단
			vec2( offset, -offset)  // 우측 하단   
		);

	float kernel[9] = float[](
		1/16.0, 2/16.0, 1/16.0,
		2/16.0, 4/16.0, 2/16.0,
		1/16.0, 2/16.0, 1/16.0
	);
	
	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
	}
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
		col += sampleTex[i] * kernel[i];
	
	FragColor = vec4(col, 1.0);
} 