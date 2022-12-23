#version 330 core

out vec4 FragColor;

// in vec2 TexCoords;
in vec3 normal;
in vec3 pos;

uniform vec3 camPos;
// uniform sampler2D _text;
uniform samplerCube skybox;

void main()
{    
    vec3 dir = normalize(pos-camPos);
    // vec3 refl = reflect(dir, normalize(normal));
    vec3 refr = refract(dir, normalize(normal), 1.00/1.52);
    // FragColor = texture(_text, TexCoords);
    FragColor = vec4(texture(skybox, refr).rgb, 1.0);
}