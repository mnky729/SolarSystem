#version 330 core

layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 PV;
uniform mat4 model;

out vec2 TexCoord;
out vec3 Normal;
out vec3 GlobalVertexPos; 

void main()
{
    gl_Position = PV * model * vec4(vertexPos, 1.0f);
    TexCoord = texCoord;
    Normal = mat3(transpose(inverse(model))) * normal;
    GlobalVertexPos = vec3(model * vec4(vertexPos, 1.0f));
}