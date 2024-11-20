#version 460 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform sampler2D Texture;
uniform bool useTexture; // �ؽ�ó ��� ���θ� ��Ÿ���� ������ ����

uniform vec3 lightPos; //--- ������ ��ġ 
uniform vec3 lightColor; //--- ������ �� 
uniform vec3 objectColor;//--- ������Ʈ ���� 1��
uniform vec3 viewPos; //--- ī�޶��� ��ġ

void main ()
{
    vec3 ambientLight = vec3(0.3, 0.3, 0.3);
    vec3 normVector = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diffuseLight = max(dot(normVector, lightDir), 0.0);


    vec3 ambient = ambientLight * lightColor;
    vec3 diffuse = diffuseLight * lightColor;

    int shininess = 128; // -- ���õ� sh
    vec3 viewDir = normalize(viewPos-FragPos);
    vec3 reflectDir = reflect(-lightDir, normVector);
    float specularLight = max(dot(viewDir, reflectDir), 0.0);
    specularLight = pow(specularLight, shininess);
    vec3 specular = specularLight * lightColor;
    
    vec3 lighting = ambient + diffuse + specular;
    if (useTexture) {
        vec4 texColor = texture(Texture, TexCoord);
        FragColor = vec4(texColor.rgb * lighting, texColor.a);
    } else {
        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result, 1.0); // �ؽ�ó�� ���� �� �⺻ ���� ���
    }
}