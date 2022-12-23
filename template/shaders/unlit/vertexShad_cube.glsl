#version 330 core

layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec2 aTexCoords;
layout (location = 1) in vec3 anormal;

// out vec2 TexCoords;
out vec3 normal;
out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    normal = mat3(transpose(inverse(model))) * anormal;
    pos = vec3(model * vec4(aPos, 1.0));
    // TexCoords = aTexCoords; 
    gl_Position = projection * view * vec4(aPos, 1.0);
       
    // gl_Position = projection * view * model * vec4(aPos, 1.0);
}