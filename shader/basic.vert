#version 460 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

layout (location = 0) out vec4 outTexColor;
layout (location = 1) out vec2 outTexCoord;

void main() {
  gl_Position = vec4(inPos, 1.0);
  outTexColor = vec4(inColor, 1.0);
  outTexCoord = inTexCoord;
}
