#include "OpenGLScene.hpp"

OpenGLScene::OpenGLScene()
{
}

OpenGLScene::~OpenGLScene()
{
}

int					OpenGLScene::addShaderProg(std::string VSFile, std::string FSFile)
{
	this->_shader = new OpenGLShader;
	shader->addShader(GL_VERTEX_SHADER, VSFile);
	shader->addShader(GL_FRAGMENT_SHADER , FSFile);
	if (!shader->createProgram())
		return (-1);
	glUseProgram(this->_shader->getProgram());
	std::cout << "Program created: " << this->_shader->getProgram() << std::endl;
	return (this->_progID - 1);
}

int					OpenGLScene::drawScene(OpenGLMatrix view, OpenGLMatrix project)
{
	this->addMatricesToProgram(this->_shader->getProgram(), this->_modelMatrix, view, project);
	glDrawElements(GL_POINTS, this->_nbParticles, GL_UNSIGNED_INT, 0);
	glFinish();
	return (1);
}

void					OpenGLScene::addMatricesToProgram(GLuint progID, OpenGLMatrix model, OpenGLMatrix view, OpenGLMatrix project)
{
	GLint			uloc_M;
	GLint			uloc_V;
	GLint			uloc_P;

    uloc_M = glGetUniformLocation(progID, "M");
    uloc_V = glGetUniformLocation(progID, "V");
    uloc_P = glGetUniformLocation(progID, "P");

    glUniformMatrix4fv(uloc_M, 1, GL_FALSE, model.getMatrixArray());
    glUniformMatrix4fv(uloc_V, 1, GL_FALSE, view.getMatrixArray());
    glUniformMatrix4fv(uloc_P, 1, GL_FALSE, project.getMatrixArray());
}

OpenGLMatrix*		OpenGLScene::getModelMatrix()
{
	return this->_modelMatrix;
}

void					OpenGLScene::initVbo()
{
	std::cout << "binding vbo to program: " << program << std::endl; 
	glGenVertexArrays(1, &(this->_vao));
	glBindVertexArray(this->_vao);
	glGenBuffers(1, this->_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, this->_vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * this->_nbParticles, NULL, GL_STREAM_DRAW);
	attrloc = glGetAttribLocation(this->_shader->getProgram(), "in_Position");
	glVertexAttribPointer(attrloc, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attrloc);

//	glBindVertexArray(0);
}

void				OpenGLScene::getVbo()
{
	return this->_vbo[0];
}
