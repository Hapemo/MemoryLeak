#include "Graphics/GLShader.h"

GLShader::GLShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	programID = glCreateProgram();
	linked = false;
	paths.first = vertexShader;
	paths.second = fragmentShader;
}

GLShader::~GLShader()
{
	if (programID > 0) 
		glDeleteProgram(programID);
}

bool GLShader::CompileVertexShader()
{
	std::ifstream vertexShader(paths.first, std::ifstream::in);

	if (!vertexShader)
		throw std::string("File for vertex shader not found!");

	std::stringstream ss;
	ss << vertexShader.rdbuf();
	vertexShader.close();

	std::string str = ss.str();

	GLuint vertexHandle = glCreateShader(GL_VERTEX_SHADER);
	GLchar const* vertexCode[] = { str.c_str() };

	glShaderSource(vertexHandle, 1, vertexCode, NULL);
	glCompileShader(vertexHandle);

	GLint result;
	glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
		throw std::string("Vertex shader compilation failed.");

	glAttachShader(programID, vertexHandle);

	return true;
}

bool GLShader::CompileFragmentShader()
{
	std::ifstream fragmentShader(paths.second, std::ifstream::in);

	if (!fragmentShader)
	{
		throw std::string("File for fragment shader not found!");
		return false;
	}

	std::stringstream ss;
	ss << fragmentShader.rdbuf();
	fragmentShader.close();

	std::string str = ss.str();

	GLuint fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
	GLchar const* fragmentCode[] = { str.c_str() };

	glShaderSource(fragmentHandle, 1, fragmentCode, NULL);
	glCompileShader(fragmentHandle);

	GLint result;
	glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		throw std::string("Fragment shader compilation failed.");
		return false;
	}

	glAttachShader(programID, fragmentHandle);

	return true;
}

bool GLShader::CompileShaders()
{
	if (CompileVertexShader() && CompileFragmentShader())
		return true;
	return false;
}

bool GLShader::LinkShaders()
{
	if (linked)
		return true;

	glLinkProgram(programID);

	GLint result;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);

	if (result == GL_FALSE)
	{
		throw std::string("Linking of shaders failed.");
		return false;
	}

	linked = true;

	return true;
}

bool GLShader::CompileLinkShaders()
{
	if (CompileShaders() && LinkShaders())
		return true;
	return false;
}

bool GLShader::Validate()
{
	glValidateProgram(programID);

	GLint result;
	glGetProgramiv(programID, GL_VALIDATE_STATUS, &result);

	if (result == GL_FALSE)
	{
		throw std::string("Validation of shaders failed");
		return false;
	}

	return result;
}

void GLShader::Bind()
{
	glUseProgram(programID);
}

void GLShader::Unbind()
{
	glUseProgram(0);
}

void GLShader::RegisterUniform(const std::string& uniform)
{
	uniforms.insert(std::pair<std::string, GLint>(uniform, glGetUniformLocation(GetID(), uniform.c_str())));
	
	if (uniforms[uniform] < 0)
		throw std::string("Uniform not found!");
}

void GLShader::RegisterUniforms(const std::vector<std::string>& strings)
{
	for (const std::string& str : strings)
		RegisterUniform(str);
}

void GLShader::InsertUniform1iv(const std::string& uniform, size_t count, int* data)
{
	glUniform1iv(uniforms[uniform], count, data);
}