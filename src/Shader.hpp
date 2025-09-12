#pragma once

#include "Util.hpp"

enum class SHADING_TYPE {
	PHONG = 0,
	PBR = 1
};

class Shader {
private:
	std::string guid;
	std::string name;
	unsigned int shaderProgram;
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;
	SHADING_TYPE shaderType;
public:
	Shader();
	Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, SHADING_TYPE shaderType);
	~Shader();

	std::string loadShaderSource(const std::string& shaderPath);
	void createVertexShader();
	void createFragmentShader();
	void compile(unsigned int shader, const std::string& shaderSource);
	void createProgramAndAttachShaders(unsigned int vertexShader, unsigned int fragmentShader);
	void bind();
	void unbind();

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVector2f(const std::string& name, const glm::vec2& value);
	void setVector3f(const std::string& name, const glm::vec3& value);
	void setVector4f(const std::string& name, const glm::vec4& value);
	void setMatrix4f(const std::string& name, const glm::mat4& value);

	const std::string& getGUID() {
		return this->guid;
	}

	const std::string& getName() {
		return this->name;
	}

	unsigned int getShaderProgram() {
		return this->shaderProgram;
	}

	const std::string& getVertexShaderSource() {
		return this->vertexShaderSource;
	}

	const std::string& getFragmentShaderSource() {
		return this->fragmentShaderSource;
	}

	unsigned int getVertexShaderID() {
		return this->vertexShaderID;
	}

	unsigned int getFragmentShaderID() {
		return this->fragmentShaderID;
	}
};

