#version 450

layout(location = 0) in vec2 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 0) out vec3 fragColor;

layout(push_constant) uniform Push {
    mat2 transform;
    vec2 offset;
} push;

void main() {
    gl_Position = vec4(push.transform*inPosition, 0.0, 1.0);
    fragColor = inColor;
}