#version 330 core

layout(location=0) in vec4 Position;

uniform mat4 ProjectionCanvas;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    gl_Position = ProjectionCanvas * ViewMatrix * ModelMatrix * Position;
}