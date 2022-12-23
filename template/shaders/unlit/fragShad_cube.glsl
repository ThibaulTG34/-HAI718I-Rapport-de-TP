#version 330 core

out vec4 FragColor;

in vec2 TexCoords;
// in vec3 normal;
// in vec3 pos;

// uniform vec3 camPos;
uniform sampler2D _text;

void main()
{    
    // vec3 dir = normalize(pos-camPos);
    // vec3 refl = reflect(dir, normalize(normal));
    FragColor = texture(_text, TexCoords);
}