#version 330 core

layout(location = 0) in vec4 Position;
layout(location = 1) in vec4 Normal;
layout(location = 2) in vec2 TexCoord;
layout(location = 3) in vec4 Tangent;

out vec3 vNormal;
out vec4 vPosition;
out vec2 vTexCoord;
out vec3 vTangent;
out vec3 vBiTangent;

uniform mat4 ProjectionCanvas;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main()
{
    vTexCoord = TexCoord;
    vPosition = ModelMatrix * Position;
    vNormal = (ModelMatrix * Normal).xyz;
    vTangent = (ModelMatrix * vec4(Tangent.xyz, 0.0)).xyz;
    vBiTangent = cross(vNormal, vTangent) * Tangent.w;

    gl_Position = ProjectionCanvas * ViewMatrix * ModelMatrix * Position;
}