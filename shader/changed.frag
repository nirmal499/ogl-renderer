#version 460 core

layout (location = 0) in vec4 inTexColor;
layout (location = 1) in vec2 inTexCoord;

out vec4 FragColor;

uniform sampler2D Tex;

void main()
{
  FragColor = texture(Tex, inTexCoord) * (vec4(1.0) - inTexColor);
}
