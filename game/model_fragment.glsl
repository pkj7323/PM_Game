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
	
	float constant;//감쇠 상수항
	float linear;//감쇠 선형항(1차)
	float quadratic;//감쇠 제곱항(2차)
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;
  
	float constant;//감쇠 상수항
	float linear;//감쇠 선형항(1차)
	float quadratic;//감쇠 제곱항(2차)
  
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
	vec3 BumpMapNormal = texture(material.normalMap, TexCoords).xyz * 2.0 - 1.0; // 이 줄만 필요합니다.
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
	// 우리의 조명은 3단계로 설정됩니다: 방향성 조명, 점 조명, 그리고 선택적인 손전등입니다. 
	// 각 단계마다 해당 램프의 색상을 계산하는 calculate 함수가 정의되어 있습니다. 
	// main() 함수에서는 모든 계산된 색상을 합산하여 이 프래그먼트의 최종 색상을 만듭니다.
	// =======================================================
	// phase 1: directional lighting(방향성 조명, 태양광)
	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	//vec3 result = vec3(0);
	// phase 2: point lights ( 점 조명 )
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
	// phase 3: spot light (손전등)
	result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    
	
	FragColor = vec4(result, 1.0);
}

// 방향성 조명을 사용할 때 색상을 계산합니다.
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
	// 색상 혼합
	// 주변광(ambient) 색상을 계산합니다. 주변광은 물체의 재질(diffuse 텍스처)과 조명의 주변광 색상(light.ambient)을 곱하여 얻습니다.
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	return (ambient + diffuse + specular);
}

// 점 조명을 사용할 때 색상을 계산합니다.
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
	// 감쇠 (Attenuation)는 빛이 물체에 도달할 때 빛의 강도가 감소하는 것을 의미합니다.
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
	// combine results
	// 주변광(ambient) 색상을 계산합니다. 주변광은 물체의 재질(diffuse 텍스처)과 조명의 주변광 색상(light.ambient)을 곱하여 얻습니다.
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient *= attenuation;// 감쇠 (Attenuation)는 빛이 물체에 도달할 때 빛의 강도가 감소하는 것을 의미합니다.
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}

// 스포트라이트 조명을 사용할 때 색상을 계산합니다.
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
	// 감쇠 (Attenuation)는 빛이 물체에 도달할 때 빛의 강도가 감소하는 것을 의미합니다.
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