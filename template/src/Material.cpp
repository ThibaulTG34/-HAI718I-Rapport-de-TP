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


Material::~Material()
{
	if (m_program != 0)
	{
		glDeleteProgram(m_program);
	}
}
std::vector<std::string> skybox_faces{
	"skybox/right.jpg",
	"skybox/left.jpg",
	"skybox/top.jpg",
	"skybox/bottom.jpg",
	"skybox/front.jpg",
	"skybox/back.jpg"};

GLuint cube, skybox;

float skyboxVertices[] = {
	// positions
	-1.0f, 1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,

	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f};

unsigned int VAO, VBO;
Camera camera = Camera();

void Material::init()
{
	// TODO : Change shader by your
	sky_program = load_shaders("/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template//shaders/unlit/vertex.glsl", "/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template/shaders/unlit/fragment.glsl");
	cube_program = load_shaders("/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template//shaders/unlit/vertexShad_cube.glsl", "/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template/shaders/unlit/fragShad_cube.glsl");
	check();
	// TODO : set initial parameters
	m_color = {1.0, 1.0, 1.0, 1.0};

	// ------ Normal MAP ------------
	const char *file = "./data/test.jpg";
	const char *normalMAP = "./data/testN.jpg";
	lightPos = {1., 1., 1.};
	viewPos = {0., 0., 0.};
	// m_texture = loadTexture2DFromFilePath(file);
	// normal_texture = loadTexture2DFromFilePath(normalMAP);
	// ------------------------------

	// // skybox VAO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	skybox = SkyBox(skybox_faces);
	cube = loadTexture2DFromFilePath("data/lava.png");
}

void Material::clear()
{
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material
	if (s == 'c')
	{
		glDeleteTextures(1, &cube);
	}
	if (s == 's')
	{
		glDeleteTextures(1, &skybox);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
}

void Material::bind(char prog)
{
	check();
	s = prog;
	if (prog == 'c')
	{
		m_program = cube_program;
	}
	if (prog == 's')
	{
		m_program = sky_program;
	}
	glUseProgram(m_program);
	internalBind();
}

void Material::internalBind()
{
	// bind parameters
	GLint color = getUniform("color");
	glUniform4fv(color, 1, glm::value_ptr(m_color));
	if (skybox != 0)
	{
		// ----- Normal MAP ------
		// glActiveTexture(GL_TEXTURE0);
		// glUniform1i(getUniform("_texture"), 0);
		// glBindTexture(GL_TEXTURE_2D, m_texture);
		// -----------------------

		glDepthMask(GL_FALSE);
		glDepthFunc(GL_LEQUAL);
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		glDepthMask(GL_TRUE);
		glUniform1i(getUniform("skybox"), skybox);
		glUniform3fv(getUniform("camPos"), 1, glm::value_ptr(camera.position));
	}
	if (cube != 0 && s == 'c')
	{
		glUniform1i(getUniform("_text"), 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube);
	}
	// glUniform1i(getUniform("cube"), GL_TEXTURE0);

	// -------- Normal MAP -------
	// if (normal_texture != 0)
	// {
	// 	glActiveTexture(GL_TEXTURE1);
	// 	glUniform1i(getUniform("normal_texture"), 1);
	// 	glBindTexture(GL_TEXTURE_2D, normal_texture);
	// }
	// ---------------------------

	// glUniform3fv(getUniform("lightPos"), 1.0, glm::value_ptr(lightPos));
	// glUniform3fv(getUniform("viewPos"), 1.0, glm::value_ptr(viewPos));

	// TODO : Add your custom parameters here
}

void Material::setMatrices(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
}

GLint Material::getAttribute(const std::string &in_attributeName)
{
	check();
	return glGetAttribLocation(m_program, in_attributeName.c_str());
}

GLint Material::getUniform(const std::string &in_uniformName)
{
	check();
	return glGetUniformLocation(m_program, in_uniformName.c_str());
}
