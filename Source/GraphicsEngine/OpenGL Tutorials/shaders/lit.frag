#version 330 core

in vec3 vNormal;
in vec4 vPosition;

uniform vec3 CameraPosition;

uniform vec3 BaseColour;
uniform vec3 LightDirection;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;

uniform float specularPower;

out vec4 Colour;

void main()
{

    vec3 N = normalize(vNormal);
    vec3 L = normalize(LightDirection);

    float lambertTerm = max(0, min(1, dot(N, -L)));

    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);
    
    float specularTerm = pow(max(0, min(1, dot(R, -V))), specularPower);

    vec3 ambient = vec3(1.0) * Ka;
    vec3 diffuse = vec3(1.0) * Kd * lambertTerm;
    vec3 specular = vec3(1.0) * Ks * specularTerm;

    Colour = vec4(ambient + diffuse + specular, 1.0);// * FragColour;
}