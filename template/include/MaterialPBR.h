#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

struct MaterialPBR
{
    GLuint program_pbr;


    virtual ~MaterialPBR();
    MaterialPBR();

};
