#version 330 core

out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)  
in vec2 textCoord;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, textCoord) * vertexColor;
    //FragColor = vertexColor;
} 