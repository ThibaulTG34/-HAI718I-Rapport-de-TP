#version 330 core


layout (location = 0) vec3 a_position;
layout(location = 1) vec3 a_normal;
layout(location = 2) vec2 a_texCoord;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;

out vec3 v_position;
out vec3 v_normal;
out vec2 v_texCoord;

void main() {
  // calcule la position
  vec4 position = u_projectionMatrix * u_viewMatrix * u_modelMatrix * vec4(a_position, 1.0);
  gl_Position = position;
  v_position = vec3(position);
  
  // calcule la normale
  v_normal = normalize(mat3(u_modelMatrix) * a_normal);
  
  // calcule la texture
  v_texCoord = a_texCoord;
}