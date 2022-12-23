#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 tangent;
layout(location = 3) in vec2 uv0;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// uniform vec3 viewPos;
// uniform vec3 lightPos;

out vec3 t_coord;
// out vec3 o_positionWorld;
// out vec3 tang_viewPos;
// out vec2 o_uv0;
// out vec3 tang_lightPos;
// out vec3 tang_pos;


void main() {

  // o_positionWorld = vec3(model * vec4(position, 1.0));
  // mat3 normalMatrix = mat3(transpose(inverse(model)));
  // o_uv0 = uv0;
  // vec3 tang = normalize(normalMatrix * tangent);
  // vec3 norm = normalize(normalMatrix * normal);
  // tang = normalize(tang - dot(tang, norm) * norm);
  // vec3 bitan = cross(norm, tang);

  // mat3 tan_bitan_norm = transpose(mat3(tang, bitan, norm));
  // tang_lightPos = tan_bitan_norm * lightPos;
  // tang_viewPos = tan_bitan_norm * viewPos;
  // tang_pos = tan_bitan_norm * o_positionWorld;

  // gl_Position = projection * view * model * vec4(position, 1.0);

  // Pour la skybox
  t_coord = position;
  gl_Position = projection * view * vec4(position, 1.0);

}
