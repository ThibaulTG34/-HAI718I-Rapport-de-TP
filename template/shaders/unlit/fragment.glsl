#version 330 core

// in vec3 o_positionWorld;
// in vec3 tang_viewPos;
// in vec2 o_uv0;
// in vec3 tang_lightPos;
// in vec3 tang_pos;

in vec3 t_coord;
out vec4 FragColor;
// uniform vec3 lightColor;
// uniform sampler2D _texture;
// uniform sampler2D normal_texture;




// Pour la skybox
// uniform vec3 camPos;
uniform samplerCube cube;
// uniform sampler2D _text;

void main() {

    // vec3 normal = texture(normal_texture, o_uv0).rgb;
    // normal = normalize(normal * 2.0 - 1.0);
    // vec3 color_text = texture(_texture, o_uv0).rgb;

    // vec3 ambient = color_text * 1.0;
    // vec3 lightDir = normalize(tang_lightPos - o_positionWorld);
    // float diff = max(dot(normal, lightDir), 0.0);
    // vec3 diffuse = color_text * (diff * 1.0);

    // vec3 viewDir = normalize(tang_viewPos - tang_pos);
    // vec3 reflectDir = reflect(-lightDir, normal);
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    // vec3 specular = (spec * vec3(0.2));

    // vec3 result = ambient + diffuse + specular;

    // FragColor = vec4(result, 1.0); 


    // Pour la skybox
    FragColor = texture(cube, t_coord);

    // vec3 dir = normalize(o_normalWorld - camPos);
    // vec3 refl = reflect(dir, normalize(o_normalWorld));
    // FragColor = vec4(texture(cube, refl).rgb, 1.0);


}


// DEBUG: position
//FragColor = vec4(o_positionWorld, 1.0);
// DEBUG: normal
//FragColor = vec4(0.5 * o_normalWorld + vec3(0.5) , 1.0);
// DEBUG: uv0
// FragColor = vec4(o_uv0, 1.0);