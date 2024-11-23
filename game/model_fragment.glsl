#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

void main()
{    
    vec3 ambient = vec3(1, 1, 1);
    FragColor = vec4(ambient * vec3(texture(texture_diffuse1, TexCoords)), 1.0);
}