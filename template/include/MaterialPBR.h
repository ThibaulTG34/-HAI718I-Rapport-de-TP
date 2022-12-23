#ifndef MATERIALPBR_H_DEFINED
#define MATERIALPBR_H_DEFINED
#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <stdexcept>

struct MaterialPBR
{
    GLuint program_pbr;
    glm::vec3 albedoColor;
    GLuint albedoTexture;
    float metalnessValue;
    GLuint metalnessTexture;
    float roughnessValue;
    GLuint roughnessTexture;
    float aoValue;
    GLuint aoTexture;

    inline void check()
    {
        if (program_pbr == 0)
        {
            throw std::runtime_error("Shader program not initialized");
        }
    }

    virtual ~MaterialPBR();

    virtual void init(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix);

    MaterialPBR() : program_pbr(0)
    {

    }

    void injectionParametre();

    void setMatrices(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix);

    GLint getUniform(const std::string &in_uniformName);
};

#endif