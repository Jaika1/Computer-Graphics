#version 330 core

in vec3 vNormal;
in vec4 vPosition;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 CameraPosition;

uniform vec3 LightDirection;
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D normalTexture;

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
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);

    mat3 TBN = mat3(T,B,N);
    vec3 texNormal = (texture(normalTexture, vTexCoord).rgb * 2) - 1;

    N = TBN * (texNormal * 2 - 1);

    float lambertTerm = max(0, min(1, dot(N, -L)));

    vec3 V = normalize(CameraPosition - vPosition.xyz);
    vec3 R = reflect(L, N);
    
    float specularTerm = pow(max(0, min(1, dot(R, -V))), specularPower);

    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;

    vec3 ambient = vec3(1.0) * Ka * texDiffuse;
    vec3 diffuse = vec3(1.0) * Kd * texDiffuse * lambertTerm;
    vec3 specular = vec3(1.0) * Ks * texSpecular * specularTerm;

    Colour = vec4(ambient + diffuse + specular, 1.0);
    //Colour = vec4(lambertTerm,lambertTerm,lambertTerm, 1.0);
}