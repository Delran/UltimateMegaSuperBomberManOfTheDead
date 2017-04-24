#version 330 core

in vec2 vertexTexturePosition;

out vec4 fragmentColor;

uniform sampler2D textureChannel;

void main()
{
    vec2 fragmentTexturePosition = vec2(vertexTexturePosition.x, 1 - vertexTexturePosition.y);
    fragmentColor = texture(textureChannel, fragmentTexturePosition);
}
