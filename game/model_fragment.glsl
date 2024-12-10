#version 330 core
out vec4 FragColor;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normalMap;
	float shininess;
}; 

struct DirLight {
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;
	
	float constant;//���� �����
	float linear;//���� ������(1��)
	float quadratic;//���� ������(2��)
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
  
	float constant;//���� �����
	float linear;//���� ������(1��)
	float quadratic;//���� ������(2��)
  
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;       
};

#define NR_POINT_LIGHTS 4

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;
in vec3 Tangent;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;



// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcBumpNormal()
{
	vec3 normal = normalize(Normal);
	vec3 tangent = normalize(Tangent);
	tangent = normalize(tangent - dot(tangent, normal) * normal);
	vec3 bitangent = cross(tangent, normal);
	vec3 BumpMapNormal = texture(material.normalMap, TexCoords).xyz * 2.0 - 1.0; // �� �ٸ� �ʿ��մϴ�.
	vec3 NewNormal;
	mat3 TBN = mat3(tangent, bitangent, normal);
    NewNormal = TBN * BumpMapNormal;
	NewNormal = normalize(NewNormal);
	return NewNormal;
}

void main()
{    
	
	// properties
	vec3 norm = CalcBumpNormal();
	vec3 viewDir = normalize(viewPos - FragPos);
	
	// =======================================================
	// �츮�� ������ 3�ܰ�� �����˴ϴ�: ���⼺ ����, �� ����, �׸��� �������� �������Դϴ�. 
	// �� �ܰ踶�� �ش� ������ ������ ����ϴ� calculate �Լ��� ���ǵǾ� �ֽ��ϴ�. 
	// main() �Լ������� ��� ���� ������ �ջ��Ͽ� �� �����׸�Ʈ�� ���� ������ ����ϴ�.
	// =======================================================
	// phase 1: directional lighting(���⼺ ����, �¾籤)
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	//vec3 result = vec3(0);
	// phase 2: point lights ( �� ���� )
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
	// phase 3: spot light (������)
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
	
	FragColor = vec4(result, 1.0);
}

// ���⼺ ������ ����� �� ������ ����մϴ�.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	float spec = 0.0;
	vec3 halfDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfDir), 0.0), material.shininess);
//	else
//	{
//		vec3 reflectDir = reflect(-lightDir, normal);
//		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	}
	if (dot(viewDir, normal) < 0.0f) {
		diff = spec = 0.0f;
	}
	// combine results 
	// ���� ȥ��
	// �ֺ���(ambient) ������ ����մϴ�. �ֺ����� ��ü�� ����(diffuse �ؽ�ó)�� ������ �ֺ��� ����(light.ambient)�� ���Ͽ� ����ϴ�.
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	return (ambient + diffuse + specular);
}

// �� ������ ����� �� ������ ����մϴ�.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	float spec = 0.0;
	
	vec3 halfDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfDir), 0.0), material.shininess);
		
//	else
//	{
//		vec3 reflectDir = reflect(-lightDir, normal);
//		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	}
	if (dot(viewDir, normal) < 0.0f) {
		diff = spec = 0.0f;
	}
	// attenuation
	// ���� (Attenuation)�� ���� ��ü�� ������ �� ���� ������ �����ϴ� ���� �ǹ��մϴ�.
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	// combine results
	// �ֺ���(ambient) ������ ����մϴ�. �ֺ����� ��ü�� ����(diffuse �ؽ�ó)�� ������ �ֺ��� ����(light.ambient)�� ���Ͽ� ����ϴ�.
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient *= attenuation;// ���� (Attenuation)�� ���� ��ü�� ������ �� ���� ������ �����ϴ� ���� �ǹ��մϴ�.
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

// ����Ʈ����Ʈ ������ ����� �� ������ ����մϴ�.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	float spec = 0.0;
	
	vec3 halfDir = normalize(lightDir + viewDir);
	spec = pow(max(dot(normal, halfDir), 0.0), material.shininess);
		
//	else
//	{
//		vec3 reflectDir = reflect(-lightDir, normal);
//		spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
//	}
	if (dot(viewDir, normal) < 0.0f) {
		diff = spec = 0.0f;
	}
	// attenuation
	// ���� (Attenuation)�� ���� ��ü�� ������ �� ���� ������ �����ϴ� ���� �ǹ��մϴ�.
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction)); 
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	return (ambient + diffuse + specular);
}