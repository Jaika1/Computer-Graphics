#version 330 core

layout(location = 0) in vec4 Position;

uniform mat4 ProjectionCanvas;

void main()
{
    gl_Position = ProjectionCanvas * Position;
}