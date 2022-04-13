#type vertex
#version 460 core

layout (location = 0) in vec4 pos;
layout (location = 1) in vec4 color;

uniform mat4 vpMatrix;

out vec4 vertColor;

void main() {
    vertColor = color;
    gl_Position = vpMatrix * pos;
}

#type fragment
#version 460 core

in vec4 vertColor;

layout (location = 0) out vec4 fragColor;

void main() {
    fragColor = vertColor;
}