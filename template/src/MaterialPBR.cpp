// Local includes
#include "Material.h"
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

MaterialPBR::MaterialPBR()
{
}

MaterialPBR::~MaterialPBR()
{
    if (program_pbr != 0)
    {
        glDeleteProgram(program_pbr);
    }
}
