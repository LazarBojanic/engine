#include "Shader.hpp"

#include "ResourceManager.hpp"

Shader::Shader() {
	this->guid = Util::generateGUID();
	this->name = "";
	this->shaderType = SHADING_TYPE::PHONG;
	this->vertexShaderPath = "";
	this->fragmentShaderPath = "";
	this->vertexShaderSource = "";
	this->fragmentShaderSource = "";
	this->vertexShaderID = 0;
	this->fragmentShaderID = 0;
	this->shaderProgram = 0;
}

Shader::Shader(const std::string& name, const std::string& vertexShaderPath, const std::string& fragmentShaderPath, SHADING_TYPE shaderType) {
	this->guid = Util::generateGUID();
	this->name = name;
	this->shaderType = shaderType;
	createVertexShader();
	createFragmentShader();

	this->vertexShaderPath = ResourceManager::getInstance()->getAssetPath(vertexShaderPath).string();
	this->fragmentShaderPath = ResourceManager::getInstance()->getAssetPath(fragmentShaderPath).string();

	this->vertexShaderSource = loadShaderSource(this->vertexShaderPath);
	this->fragmentShaderSource = loadShaderSource(this->fragmentShaderPath);

	compile(this->vertexShaderID, this->vertexShaderSource);
	compile(this->fragmentShaderID, this->fragmentShaderSource);

	createProgramAndAttachShaders(this->vertexShaderID, this->fragmentShaderID);
}

Shader::~Shader() {
	glDeleteProgram(this->shaderProgram);
}

std::string Shader::loadShaderSource(const std::string& shaderPath) {
	std::string shaderSource;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		std::stringstream shaderStream;
		shaderFile.open(shaderPath);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderSource = shaderStream.str();
		shaderStream.clear();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ. Reason: " << e.what() << std::endl;
	}
	return shaderSource;
}

void Shader::createVertexShader() {
	this->vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
}

void Shader::createFragmentShader() {
	this->fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
}

void Shader::compile(unsigned int shader, const std::string& shaderSource) {
	const char* shaderSourceCString = shaderSource.c_str();
	glShaderSource(shader, 1, &shaderSourceCString, NULL);
	glCompileShader(shader);
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error compiling shader " << this->name << "\n" << infoLog << std::endl;
	}
}

void Shader::createProgramAndAttachShaders(unsigned int vertexShader, unsigned int fragmentShader) {
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, vertexShader);
	glAttachShader(this->shaderProgram, fragmentShader);
	glLinkProgram(this->shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shaderProgram, 512, NULL, infoLog);
		std::cout << "Error linking shader " << this->name << "\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::bind() {
	glUseProgram(this->shaderProgram);
}

void Shader::unbind() {
	glUseProgram(0);
}

void Shader::setBool(const std::string& name, bool value) {
	this->bind();
	glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) {
	this->bind();
	glUniform1i(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) {
	this->bind();
	glUniform1f(glGetUniformLocation(this->shaderProgram, name.c_str()), value);
}

void Shader::setVector2f(const std::string& name, const glm::vec2& value) {
	this->bind();
	glUniform2f(glGetUniformLocation(this->shaderProgram, name.c_str()), value.x, value.y);
}

void Shader::setVector3f(const std::string& name, const glm::vec3& value) {
	this->bind();
	glUniform3f(glGetUniformLocation(this->shaderProgram, name.c_str()), value.x, value.y, value.z);
}

void Shader::setVector4f(const std::string& name, const glm::vec4& value) {
	this->bind();
	glUniform4f(glGetUniformLocation(this->shaderProgram, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4f(const std::string& name, const glm::mat4& value) {
	this->bind();
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
