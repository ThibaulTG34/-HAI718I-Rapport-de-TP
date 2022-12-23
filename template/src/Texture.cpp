#include "Texture.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include "stb_image.h"
#include "math.h"
#include <stdexcept>
#include "Vec3.h"
#include <vector>
#include "iostream"

GLuint computeNormalMap(const char *path)
{
	GLuint texture;
	glGenTextures(1, &texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
	unsigned char *NormalMap = new unsigned char[width * height * 3];
	int s = 1;
	if (data)
	{
		for (int i = 0; i < width-1; i++)
		{
			for (int j = 0; j < height-1; j++)
			{
				float dx = (s / 2) * ((int)data[(i - 1) * width + j] - (int)data[(i - 1) * width + j]);
				float dy = (s / 2) * ((int)data[i * width + (j + 1)] - (int)data[i * width + (j - 1)]);
				Vec3 dirU = Vec3(1, 0, dx);
				Vec3 dirV = Vec3(0, 1, dy);
				Vec3 m = (Vec3::cross(dirU, dirV));
				m.normalize();

				NormalMap[i * width * 3 + j * 3] = std::floor((m[0] * 0.5 + 0.5) * 255);
				NormalMap[i * width * 3 + (j * 3) + 1] = std::floor((m[1] * 0.5 + 0.5) * 255);
				NormalMap[i * width * 3 + (j * 3) + 2] = std::floor((m[2] * 0.5 + 0.5) * 255);
			}
		}
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NormalMap);
		glGenerateMipmap(GL_TEXTURE_2D);

		

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// delete[] NormalMap;
		stbi_image_free(NormalMap);
	}
	else
	{
		std ::cout << " Failed to load texture " << std ::endl;
		stbi_image_free(data);
	}
	// setDefaultTexture2DParameters(texture);
	return texture;
}



GLuint loadTexture2DFromFilePath(const char *path)
{
	GLuint texture;
	glGenTextures(1, &texture);

	int width = 0;
	int height = 0;
	int channels = 3;
	unsigned char *data = stbi_load(path, &width, &height, &channels, 3);
	if (data)
	{
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std ::cout << " Failed to load texture " << std ::endl;
		stbi_image_free(data);
	}
	// setDefaultTexture2DParameters(texture);
	return texture;
}

GLuint SkyBox(std::vector<std::string> cube_faces)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < cube_faces.size(); i++)
	{
		unsigned char *data = stbi_load(cube_faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
						 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "failed to load: " << cube_faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return texture;
}

void setDefaultTexture2DParameters(GLuint texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
