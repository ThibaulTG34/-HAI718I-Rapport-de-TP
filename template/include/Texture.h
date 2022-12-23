#ifndef TEXTURE_H_DEFINED
#define TEXTURE_H_DEFINED

#include <string>
#include <GL/glew.h>
#include <vector>

GLuint computeNormalMap(const char *path);

GLuint loadTexture2DFromFilePath(const char* path);

GLuint SkyBox(std::vector<std::string> cube_faces);

void setDefaultTexture2DParameters(GLuint texture);

#endif
