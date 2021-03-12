#version 330 core

uniform vec4 BaseColour;
out vec4 Colour;

void main()
{
    Colour = BaseColour;
}