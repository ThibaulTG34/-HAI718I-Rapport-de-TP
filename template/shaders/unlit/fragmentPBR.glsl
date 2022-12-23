
#version 330 core

in vec3 v_position;
in vec3 v_normal;
in vec2 v_texCoord;

uniform vec3 u_albedoColor;
uniform sampler2D u_albedo;
uniform sampler2D u_metalness;
uniform float u_metalnessValue;
uniform sampler2D u_roughness;
uniform float u_roughnessValue;
uniform sampler2D u_AO;
uniform float u_AOValue;



void main() {
  // calcule l'albedo
  vec3 albedo;
  if (u_albedo != 0) {
    albedo = texture(u_albedo, v_texCoord).rgb;
  } else {
    albedo = u_albedoColor;
  }
  
  // calcule le metalness
  float metalness;
  if (u_metalness != 0) {
    metalness = texture(u_metalness, v_texCoord).r;
  } else {
    metalness = u_metalnessValue;
  }
  
  // calcule la roughness
  float roughness;
  if (u_roughness != 0) {
    roughness = texture(u_roughness, v_texCoord).r;
  } else {
    roughness = u_roughnessValue;
  }
  
  // calcule l'AO
  float ao;
  if (u_AO!= 0) {
    ao = texture(u_AO, v_texCoord).r;
  } else {
    ao = u_AOValue;
  }
  
  // calcule la couleur finale
  vec3 finalColor = albedo * (1.0 - metalness) + vec3(1.0, 1.0, 1.0) * metalness;
  finalColor *= 1.0 - roughness;
  finalColor *= ao;
  
  // affiche la couleur finale
  gl_FragColor = vec4(finalColor, 1.0);
}