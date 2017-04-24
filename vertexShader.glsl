#version 330 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec2 layoutTexturePosition;

out vec2 vertexTexturePosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(layoutPosition, 1.0f);
    vertexTexturePosition = layoutTexturePosition;
}
