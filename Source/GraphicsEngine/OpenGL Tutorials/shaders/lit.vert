#version 330 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;

out vec3 vNormal;
out vec4 vPosition;

uniform mat4 ProjectionCanvas;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    vPosition = ModelMatrix * Position;
    vNormal = (ModelMatrix * Normal).xyz;
    gl_Position = ProjectionCanvas * ViewMatrix * ModelMatrix * Position;
}