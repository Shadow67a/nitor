#version 460 core
out vec4 FragColor;

uniform vec4 color;

void main()
{
    FragColor = vec4(color.xyz, 1.0f);
} 
