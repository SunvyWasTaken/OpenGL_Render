#version 330 core

layout (location = 0) in vec4 aPos; // the position variable has attribute position 0
layout (location = 1) in vec3 aColor;  

out vec4 objectColor; // specify a color output to the fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 color;

void main()
{
    gl_Position = projection * view * model * aPos; // see how we directly give a vec3 to vec4's constructor
    objectColor = vec4(color, 1.0); // set the output variable to a dark-red color
}