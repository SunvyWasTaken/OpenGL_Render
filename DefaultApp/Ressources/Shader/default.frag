#version 330 core

out vec4 FragColor;

in vec4 objectColor; // the input variable from the vertex shader (same name and same type)  
in vec3 fragPosition;
in vec3 objectNormal;
in vec2 texCoords;

#define MAX_POINT_LIGHTS 10
uniform int pointLightsCount;
uniform vec3 viewPosition;

struct Material 
{
    //vec3 diffuse;
    sampler2D diffuse;
    //vec3 specular;
    sampler2D specular;
    float shininess;
};

uniform Material material;

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight directionalLight;

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform PointLight pointLights[MAX_POINT_LIGHTS];

vec3 CalcDirLight(DirectionalLight light, vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 normal = normalize(objectNormal);
    vec3 viewDir = normalize(viewPosition - fragPosition);

    // get directional light
    vec3 result = CalcDirLight(directionalLight, normal, viewDir);

    // for on pointLights
    for(int i = 0; i < pointLightsCount; i++)
        result += CalcPointLight(pointLights[i], normal, fragPosition, viewDir); 

    FragColor = vec4(result, 1.0);
} 

vec3 CalcDirLight(DirectionalLight light, vec3 normal,vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    //diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    //diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    //specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoords));
    vec3 specular = light.specular * vec3(texture(material.specular, texCoords)) * spec;

    // apply attenuation
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}