#ifndef SHADER_H_INCLUDED
#define SHADER_H_INCLUDED
#include <vector>
#include <string>
#include <cstring>
#include <GL/glew.h>
class Shader {
public:
	static GLuint createShader(GLenum eShaderType, const std::string &strShaderFile);
	static GLuint createShader(GLenum eShaderType, const char* fileName);
	static GLuint createProgram(const std::vector<GLuint> &shaderList);
};

#endif // SHADER_H_INCLUDED
