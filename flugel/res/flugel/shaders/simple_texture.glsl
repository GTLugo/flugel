#type vertex
#version 460 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

void main() {
    TexCoords = texCoords;
    gl_Position = pos;
}

#type fragment
#version 460 core

in vec2 TexCoords;

layout (location = 0) out vec4 fragColor;

uniform sampler2D screenTexture;

void main() {
    fragColor = texture(screenTexture, TexCoords);
}