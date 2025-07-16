#version 330 core
layout (location = 0) in vec3 Position;

uniform vec3 deltaPosition;

void main() {
    gl_Position = vec4(Position + deltaPosition, 1.0);
}