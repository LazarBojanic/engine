#pragma once

#include "Util.hpp"
#include <unordered_map>

enum class SHADING_TYPE {
	PHONG = 0,
	PBR = 1
};

class Shader {
private:
	std::string guid;
	std::string name;
	unsigned int shaderProgram;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;
	SHADING_TYPE shaderType;
	std::unordered_map<std::string, int> uniformCache;

	int getUniformLocation(const std::string& name);

public:
	Shader();
	Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, SHADING_TYPE shaderType);
	~Shader();

	std::string loadShaderSource(const std::string& shaderPath);
	void createVertexShader();
	void createFragmentShader();
	void compile(unsigned int shader, const std::string& shaderSource);
	void createProgramAndAttachShaders(unsigned int vertexShader, unsigned int fragmentShader);
	void bind() const;
	void unbind() const;

	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVector2f(const std::string& name, const glm::vec2& value);
	void setVector3f(const std::string& name, const glm::vec3& value);
	void setVector4f(const std::string& name, const glm::vec4& value);
	void setMatrix4f(const std::string& name, const glm::mat4& value);
	void setVector3fArray(const std::string& name, const glm::vec3* values, int count);
	void setVector4fArray(const std::string& name, const glm::vec4* values, int count);

	const std::string& getGUID() const {
		return this->guid;
	}

	const std::string& getName() const {
		return this->name;
	}

	unsigned int getShaderProgram() const {
		return this->shaderProgram;
	}

	const std::string& getVertexShaderPath() const {
		return this->vertexShaderPath;
	}
	const std::string& getFragmentShaderPath() const {
		return this->fragmentShaderPath;
	}

	const std::string& getVertexShaderSource() const {
		return this->vertexShaderSource;
	}

	const std::string& getFragmentShaderSource() const {
		return this->fragmentShaderSource;
	}

	unsigned int getVertexShaderID() const {
		return this->vertexShaderID;
	}

	unsigned int getFragmentShaderID() const {
		return this->fragmentShaderID;
	}

	SHADING_TYPE getShaderType() const {
		return this->shaderType;
	}
};
