// Local includes
#include "Shader.h"
// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// OPENGL includes
#include <GL/glew.h>
#include <GL/glut.h>
#include "Texture.h"
#include <vector>
#include "Camera.h"
#include "Context.h"
#include "MaterialPBR.h"

void MaterialPBR::init(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix)
{
    program_pbr = load_shaders("/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template//shaders/unlit/vertexPBR.glsl", "/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template/shaders/unlit/fragmentPBR.glsl");
    check();
    albedoColor = {0.5, 0.5, 0.5};
    metalnessValue = 0.5;
    roughnessValue = 0.5;
    aoValue = 0.5;
    glUseProgram(program_pbr);
    // albedoTexture = loadTexture2DFromFilePath("data/albedo.png");
    // metalnessTexture = loadTexture2DFromFilePath("data/metallic.png");
    // roughnessTexture = loadTexture2DFromFilePath("data/roughness.png");
    // aoTexture = loadTexture2DFromFilePath("data/ao.png");
    // injectionParametre();
    // setMatrices(projectionMatrix, viewMatrix, modelMatrix);
}

void MaterialPBR::injectionParametre()
{
    glUniform3fv(getUniform("u_albedoColor"), 1, glm::value_ptr(albedoColor));
    glUniform1f(getUniform("u_metalnessValue"), metalnessValue);
    glUniform1f(getUniform("u_roughnessValue"), roughnessValue);
    glUniform1f(getUniform("u_AOValue"), aoValue);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, albedoTexture);
    glUniform1i(getUniform("u_albedo"), 0);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, metalnessTexture);
    glUniform1i(getUniform("u_metalness"), 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, roughnessTexture);
    glUniform1i(getUniform("u_roughness"), 2);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, aoTexture);
    glUniform1i(getUniform("u_AO"), 3);
}

MaterialPBR::~MaterialPBR()
{
    if (program_pbr != 0)
    {
        glDeleteProgram(program_pbr);
    }
}

void MaterialPBR::setMatrices(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
}


GLint MaterialPBR::getUniform(const std::string &in_uniformName)
{
    check();
    return glGetUniformLocation(program_pbr, in_uniformName.c_str());
}

