#version 330 core

out vec4 FragColor;

in vec4 objectColor; // the input variable from the vertex shader (same name and same type)  
in vec3 fragPosition;
in vec3 objectNormal;
in vec2 texCoords;

uniform sampler2D tex0;

uniform vec3 lightPosition;
uniform vec4 lightColor;

uniform vec3 viewPosition;

vec3 obColor = vec3(0.1f, 1.f, 1.0f);

struct Material 
{
    //vec3 diffuse;
    sampler2D diffuse;
    vec3 specular;
    float shininess;
};

uniform Material material;

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

void main()
{
    //FragColor = texture(tex0, textCoord) * obColor;

    // ambient
    //vec3 ambient = light.ambient * material.ambient;
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));

    // diffuse
    vec3 normal = normalize(objectNormal);
    vec3 lightDir = normalize(lightPosition - fragPosition);

    float dotDiffuse = max(dot(objectNormal, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (dotDiffuse * material.diffuse);
    vec3 diffuse = light.diffuse * dotDiffuse * vec3(texture(material.diffuse, texCoords));

    // specular
    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);
} 