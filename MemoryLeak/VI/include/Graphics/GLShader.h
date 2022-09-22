#pragma once
#include "pch.h"
#include "Logger.h"

class GLShader
{
public:
	GLShader(const std::string& vertexShader, const std::string& fragmentShader);
	~GLShader();
	bool CompileVertexShader();
	bool CompileFragmentShader();
	bool CompileShaders();
	bool LinkShaders();
	bool CompileLinkShaders();
	bool Validate();
	void Bind();
	void Unbind();
	void RegisterUniform(const std::string& uniform);
	void RegisterUniforms(const std::vector<std::string>& strings);
	void InsertUniform1iv(const std::string& uniform, size_t count, int* data);
	GLuint GetID() { return programID; }
	bool IsLinked() { return linked; }

private:
	bool linked;
	GLuint programID;
	std::pair<std::string, std::string> paths;
	std::unordered_map<std::string, GLint> uniforms;
};

