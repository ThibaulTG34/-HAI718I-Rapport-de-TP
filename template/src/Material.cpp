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
	if (cube_program != 0)
	{
		glDeleteProgram(cube_program);
	}
}
std::vector<std::string> skybox_faces{
	"skybox/right.jpg",
	"skybox/left.jpg",
	"skybox/top.jpg",
	"skybox/bottom.jpg",
	"skybox/front.jpg",
	"skybox/back.jpg"};

GLuint cube;

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

float cubeVertices[] = {
	// positions          // texture Coords
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

float cubeVertices_normals[] = {
	// positions          // normals
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};

unsigned int cubeVAO, cubeVBO;
unsigned int skyboxVAO, skyboxVBO;
Camera camera = Camera();

void Material::init()
{
	// TODO : Change shader by your
	m_program = load_shaders("/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template//shaders/unlit/vertex.glsl", "/home/thibault/Documents/Programmation3D/TP_Texture_V2/prog-3D-2022/template/shaders/unlit/fragment.glsl");
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

	// cube VAO
	// glGenVertexArrays(1, &cubeVAO);
	// glGenBuffers(1, &cubeVBO);
	// glBindVertexArray(cubeVAO);
	// glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
	// // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	// glEnableVertexAttribArray(1);
	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
	// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	// // skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	m_texture = SkyBox(skybox_faces);
	cube = loadTexture2DFromFilePath("data/lava.png");
}

void Material::clear()
{
	// nothing to clear
	// TODO: Add the texture or buffer you want to destroy for your material
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVBO);
	glDeleteVertexArrays(1, &cubeVAO);
	glDeleteBuffers(1, &cubeVBO);
}

void Material::bind()
{
	check();
	glUseProgram(m_program);
	glUseProgram(cube_program);
	internalBind();
}

void Material::internalBind()
{
	// bind parameters
	GLint color = getUniform("color");
	glUniform4fv(color, 1, glm::value_ptr(m_color));
	// glm::mat4 model = glm::mat4(1.0f);
	// glm::mat4 view = camera.getViewMatrix();
	// glm::mat4 projection = glm::perspective(glm::radians(camera.getFovAngle()), (float)SCREENWIDTH / (float)SCREENHEIGHT, 0.1f, 100.0f);
	// setMatrices(projection, view, model);
	if (m_texture != 0)
	{
		// ----- Normal MAP ------
		// glActiveTexture(GL_TEXTURE0);
		// glUniform1i(getUniform("_texture"), 0);
		// glBindTexture(GL_TEXTURE_2D, m_texture);
		// -----------------------

		glUseProgram(cube_program);
		glUniform1i(getUniform_cube("_text"), 0);
		// glm::mat4 projection = camera.getProjectionMatrix();
		// glUniform3fv(getUniform_cube("camPos"), 1, &camera.position[0]);
		// setMatrices_cube(projection, view, model);

		// glBindVertexArray(cubeVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cube);

		glUseProgram(m_program);
		// glUniform1i(getUniform("cube"), 0);
		glDepthFunc(GL_LEQUAL);
		// view = glm::mat4(glm::mat3(camera.getViewMatrix())); // remove translation from the view matrix
		// glm::mat4 projection = camera.getProjectionMatrix();

		// setMatrices(projection, view, model);
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);

		// glUniform1i(getUniform("cube"), GL_TEXTURE0);
	}
	if (cube != 0)
	{

	}

	// -------- Normal MAP -------
	// if (normal_texture != 0)
	// {
	// 	glActiveTexture(GL_TEXTURE1);
	// 	glUniform1i(getUniform("normal_texture"), 1);
	// 	glBindTexture(GL_TEXTURE_2D, normal_texture);
	// }
	// ---------------------------

	glUniform3fv(getUniform("lightPos"), 1.0, glm::value_ptr(lightPos));
	glUniform3fv(getUniform("viewPos"), 1.0, glm::value_ptr(viewPos));

	// TODO : Add your custom parameters here
}

void Material::setMatrices(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix)
{
	check();
	glUniformMatrix4fv(getUniform("projection"), 1, false, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(getUniform("view"), 1, false, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniform("model"), 1, false, glm::value_ptr(modelMatrix));
	// glUniformMatrix4fv(getUniform_cube("projection"), 1, false, glm::value_ptr(projectionMatrix));
	// glUniformMatrix4fv(getUniform_cube("view"), 1, false, glm::value_ptr(viewMatrix));
	// glUniformMatrix4fv(getUniform_cube("model"), 1, false, glm::value_ptr(modelMatrix));
}

void Material::setMatrices_cube(glm::mat4 &projectionMatrix, glm::mat4 &viewMatrix, glm::mat4 &modelMatrix)
{
	glUniformMatrix4fv(getUniform_cube("projection"), 1, false, &projectionMatrix[0][0]);
	glUniformMatrix4fv(getUniform_cube("view"), 1, false, &viewMatrix[0][0]);
	glUniformMatrix4fv(getUniform_cube("model"), 1, false, &modelMatrix[0][0]);
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

GLint Material::getUniform_cube(const std::string &in_uniformName)
{
	check();
	return glGetUniformLocation(cube_program, in_uniformName.c_str());
}