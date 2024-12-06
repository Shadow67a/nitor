#version 460 core
in vec2 texCoord;
out vec4 FragColor;

uniform vec4 color;

uniform sampler2D imageTexture;

void main()
{
    FragColor = texture(imageTexture, texCoord);
} 
