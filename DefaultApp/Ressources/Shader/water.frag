#version 330 core

out vec4 FragColor;

in vec4 objectColor; // the input variable from the vertex shader (same name and same type)  
in vec3 fragPosition;
in vec3 objectNormal;
in vec2 texCoords;
in vec4 clipSpace;

uniform vec3 viewPosition;

uniform sampler2D reflectionText;
uniform sampler2D refractionText;
uniform sampler2D dudvMap;

uniform float moveFactor;

const float waveStrength = 0.02;

void main()
{
    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 reflectionTexCoords = vec2(ndc.x, -ndc.y);
    vec2 refractionTexCoords = vec2(ndc.x, ndc.y);

    vec2 distortion1 = (texture(dudvMap, vec2(texCoords.x + moveFactor,texCoords.y)).rg * 2.0 - 1.0) * waveStrength;

    reflectionTexCoords += distortion1;
    reflectionTexCoords.x = clamp(reflectionTexCoords.x, 0.001, 0.999);
    reflectionTexCoords.y = clamp(reflectionTexCoords.y, -0.999, -0.001);

    refractionTexCoords += distortion1;
    refractionTexCoords = clamp(refractionTexCoords, 0.001, 0.999);

    vec4 reflectionColor = texture(reflectionText, reflectionTexCoords);
    vec4 refractionColor = texture(refractionText, refractionTexCoords);

    FragColor = mix(reflectionColor, refractionColor, 0.5);
} 