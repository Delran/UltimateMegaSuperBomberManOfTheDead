#version 330 core

layout (location = 0) in vec3 layoutPosition;
layout (location = 1) in vec3 layoutColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 vertexColor;

void main()
{
    gl_Position = projection * view * model * vec4(layoutPosition, 1.0f);
    vertexColor = vec4(layoutColor, 1.0);
}
