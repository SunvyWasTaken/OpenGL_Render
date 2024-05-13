#version 330 core

out vec4 FragColor;

in vec4 objectColor; // specify a color output to the fragment shader

void main()
{
    FragColor = objectColor;
} 