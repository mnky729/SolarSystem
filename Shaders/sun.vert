#version 330 core
layout(location = 0) in vec3 vertexPos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 PVM; 

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = PVM * vec4(vertexPos, 1.0f);
    TexCoord = texCoord;
}