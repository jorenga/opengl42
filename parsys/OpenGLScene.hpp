#ifndef OPENGLSCENE_HPP
# define OPENGLSCENE_HPP

# include <map>
# include <vector>
# include "OpenCL.hpp"
# include "OpenGLShader.hpp"

class							OpenGLScene
{
	public:
								OpenGLScene();
								~OpenGLScene();
		int						createShaderProg(std::string VSFile, std::string FSFile);

		int						drawScene(OpenGLMatrix view, OpenGLMatrix project, float t);
		void					addMatricesToProgram(GLuint progID, OpenGLMatrix model,
										OpenGLMatrix view, OpenGLMatrix project);
void					OpenGLScene::initVbo();
		OpenGLMatrix*			getModelMatrix();

	private:
		OpenGLShader*			_shader;
		GLuint					_vao;
		GLuint					_vbo[2];

		OpenGLMatrix			_modelMatrix;
		OpenGLMatrix			_projectionMatrix;
		GLuint					_nbParticles;
};


#endif
