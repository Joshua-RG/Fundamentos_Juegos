#include "GLSProgram.h"
#include <fstream>
#include <vector>
#include <iostream>
#include "Error.h"

using namespace std;



GLSProgram::GLSProgram() : programID(0), vertexShaderID(0),
fragmentShaderID(0), numAtribute(0)
{
}


void GLSProgram::linkShader() {
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);

	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int*)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

		//We don't need the program anymore.
		glDeleteProgram(programID);
		//Don't leak shaders either.
		fatalError("Shaders do not linked "
			+ printf("%s", &(infoLog[0])));

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}


void GLSProgram::compileShaders(const string& vertexShaderFilePath,
	const string& fragmentShaderFilePath) {

	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) {

	}

	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0) {

	}
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLSProgram::compileShader(const string& shaderPath, GLuint id) {

	string filecontent = "";
	string line = "";

	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		fatalError("Could not open " + shaderPath);
	}
	while (getline(shaderFile, line)) {
		filecontent += line + "\n";
	}
	shaderFile.close();
	const char* contents = filecontent.c_str();
	glShaderSource(id, 1, &contents, nullptr);

	glCompileShader(id);

	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &infoLog[0]);

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.

		std::cout << shaderPath << endl;
		fatalError("Shaders do not compiled " +
			+printf("%s", &(infoLog[0])));

		glDeleteShader(id); // Don't leak the shader.
		return;
	}
}


GLSProgram::~GLSProgram()
{
}

void GLSProgram::addAtribute(const string atributeName) {
	glBindAttribLocation(programID,
		numAtribute++,
		atributeName.c_str());
}

void GLSProgram::use() {
	glUseProgram(programID);
	for (int i = 0; i < numAtribute; i++)
	{
		glEnableVertexAttribArray(i);
	}
}
void GLSProgram::unuse() {
	glUseProgram(0);
	for (int i = 0; i < numAtribute; i++)
	{
		glDisableVertexAttribArray(i);
	}
}