#version 330 core

in vec3 vNormal;
in vec4 vPosition;
in vec2 vTexCoord;
in vec3 vTangent;
in vec3 vBiTangent;

uniform vec3 CameraPosition;

const int MAX_LIGHTS = 4;
uniform int numLights;
uniform vec3 LightDirection;
//uniform vec3 PointLightColour[MAX_LIGHTS];
uniform vec3 PointLightPosition[MAX_LIGHTS];

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


vec3 diffuse(vec3 direction, vec3 colour, vec3 normal)
{
    return colour * max(0, dot(normal, -direction));
}

vec3 specular(vec3 direction, vec3 colour, vec3 normal, vec3 view)
{
    vec3 R = reflect(direction, normal);
    float specularTerm = pow(max(0, min(1, dot(R, view))), specularPower);
    return specularTerm * colour;
}

void main()
{

    vec3 N = normalize(vNormal);
    vec3 T = normalize(vTangent);
    vec3 B = normalize(vBiTangent);
    vec3 L = normalize(LightDirection);

    mat3 TBN = mat3(T,B,N);
    vec3 texNormal = (texture(normalTexture, vTexCoord).rgb * 2) - 1;

    N = TBN * (texNormal * 2 - 1);

    //float lambertTerm = max(0, min(1, dot(N, -L)));
    vec3 diffuseTotal = diffuse(L, vec3(1.0), N);

    vec3 V = normalize(CameraPosition - vPosition.xyz);
    //vec3 R = reflect(L, N);
    
    //float specularTerm = pow(max(0, min(1, dot(R, -V))), specularPower);
    vec3 specularTotal = specular(L, vec3(1.0), N, V);

    for (int i = 0; i < numLights; i++)
    {
        vec3 direction = vPosition.xyz -PointLightPosition[i];
        float distance = length(direction);
        direction = direction/distance;

        // attenuate the light intensity with inverse square law
        vec3 colour = vec3(0.0, 0.9, 2.0)/(distance * distance);
        diffuseTotal += diffuse(direction, colour, N);
        specularTotal += specular(direction, colour, N, V);
    }

    vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;
    vec3 texSpecular = texture(specularTexture, vTexCoord).rgb;

    vec3 ambient = vec3(1.0) * Ka * texDiffuse;
    vec3 diffuse = Kd * texDiffuse * diffuseTotal;
    vec3 specular = Ks * texSpecular * specularTotal;

    Colour = vec4(ambient + diffuse + specular, 1.0);
}