#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class GLSProgram
{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint vertexShaderID;

	void compileShader(const string& shaderPath, GLuint id);

public:
	GLSProgram();
	~GLSProgram();
	int numAtribute;
	void addAtribute(const string atributeName);
	void use();
	void unuse();
	void compileShaders(const string& vertexShaderFilePath,
		const string& fragmentShaderFilePath);

	void linkShader();

};