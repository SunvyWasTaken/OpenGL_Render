#version 330 core

layout (location = 0) in vec3 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;  
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNormal;

out vec4 objectColor; // specify a color output to the fragment shader
out vec3 fragPosition;
out vec3 objectNormal;
out vec2 texCoords;
out vec4 clipSpace;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

const float tiling = 10.0;


void main()
{   
    clipSpace = projection * view * model * vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    gl_Position = clipSpace;
    texCoords = aTexCoords * tiling; 
}