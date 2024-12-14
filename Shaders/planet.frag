#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
in vec3 GlobalVertexPos;
in vec3 Normal;

uniform sampler2D Texture;

out vec4 color;

const vec3 sunColor = vec3(1.0f, 0.5f, 0.0f);
const vec3 sunPos = vec3(0.0f, 0.0f, 0.0f);


void main()
{
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(sunPos - GlobalVertexPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

    color = texture(Texture, TexCoord) * vec4(diffuse, 1.0f);
}