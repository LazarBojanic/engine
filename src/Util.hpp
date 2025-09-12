#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>
#include <random>
#include <thread>
#include <glad/glad.h>
#include <glfw3/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.141592

class Util {
public:
	static constexpr unsigned int MAX_BONE_INFLUENCE = 4;

	static constexpr GLuint LAYOUT_LOCATION_POSITION = 0;
	static constexpr GLuint LAYOUT_LOCATION_COLOR = 1;
	static constexpr GLuint LAYOUT_LOCATION_UV = 2;
	static constexpr GLuint LAYOUT_LOCATION_NORMAL = 3;
	static constexpr GLuint LAYOUT_LOCATION_TANGENT = 4;
	static constexpr GLuint LAYOUT_LOCATION_BITANGENT = 5;
	static constexpr GLuint LAYOUT_LOCATION_BONE_IDS = 6;
	static constexpr GLuint LAYOUT_LOCATION_WEIGHTS = 7;

	static constexpr GLint DIMENSIONS_POSITION = 3;
	static constexpr GLint DIMENSIONS_COLOR = 4;
	static constexpr GLint DIMENSIONS_UV = 2;
	static constexpr GLint DIMENSIONS_NORMAL = 3;
	static constexpr GLint DIMENSIONS_TANGENT = 3;
	static constexpr GLint DIMENSIONS_BITANGENT = 3;
	static constexpr GLint DIMENSIONS_BONE_IDS = 4;
	static constexpr GLint DIMENSIONS_WEIGHTS = 4;

	static glm::vec3 colorIntToVec3(int color) {
		float r = ((color >> 16) & 0xff) / 255.0f;
		float g = ((color >> 8) & 0xff) / 255.0f;
		float b = ((color) & 0xff) / 255.0f;
		return glm::vec3(r, g, b);
	}

	static std::string getDebugMeaning(GLenum number) {
		switch (number) {
		case GL_DEBUG_OUTPUT_SYNCHRONOUS:
			return "GL_DEBUG_OUTPUT_SYNCHRONOUS";
		case GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH:
			return "GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH";
		case GL_DEBUG_CALLBACK_FUNCTION:
			return "GL_DEBUG_CALLBACK_FUNCTION";
		case GL_DEBUG_CALLBACK_USER_PARAM:
			return "GL_DEBUG_CALLBACK_USER_PARAM";
		case GL_DEBUG_SOURCE_API:
			return "GL_DEBUG_SOURCE_API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
			return "GL_DEBUG_SOURCE_WINDOW_SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			return "GL_DEBUG_SOURCE_SHADER_COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			return "GL_DEBUG_SOURCE_THIRD_PARTY";
		case GL_DEBUG_SOURCE_APPLICATION:
			return "GL_DEBUG_SOURCE_APPLICATION";
		case GL_DEBUG_SOURCE_OTHER:
			return "GL_DEBUG_SOURCE_OTHER";
		case GL_DEBUG_TYPE_ERROR:
			return "GL_DEBUG_TYPE_ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			return "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			return "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY:
			return "GL_DEBUG_TYPE_PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE:
			return "GL_DEBUG_TYPE_PERFORMANCE";
		case GL_DEBUG_TYPE_OTHER:
			return "GL_DEBUG_TYPE_OTHER";
		case GL_MAX_DEBUG_MESSAGE_LENGTH:
			return "GL_MAX_DEBUG_MESSAGE_LENGTH";
		case GL_MAX_DEBUG_LOGGED_MESSAGES:
			return "GL_MAX_DEBUG_LOGGED_MESSAGES";
		case GL_DEBUG_LOGGED_MESSAGES:
			return "GL_DEBUG_LOGGED_MESSAGES";
		case GL_DEBUG_SEVERITY_HIGH:
			return "GL_DEBUG_SEVERITY_HIGH";
		case GL_DEBUG_SEVERITY_MEDIUM:
			return "GL_DEBUG_SEVERITY_MEDIUM";
		case GL_DEBUG_SEVERITY_LOW:
			return "GL_DEBUG_SEVERITY_LOW";
		case GL_DEBUG_TYPE_MARKER:
			return "GL_DEBUG_TYPE_MARKER";
		case GL_DEBUG_TYPE_PUSH_GROUP:
			return "GL_DEBUG_TYPE_PUSH_GROUP";
		case GL_DEBUG_TYPE_POP_GROUP:
			return "GL_DEBUG_TYPE_POP_GROUP";
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			return "GL_DEBUG_SEVERITY_NOTIFICATION";
		case GL_MAX_DEBUG_GROUP_STACK_DEPTH:
			return "GL_MAX_DEBUG_GROUP_STACK_DEPTH";
		case GL_DEBUG_GROUP_STACK_DEPTH:
			return "GL_DEBUG_GROUP_STACK_DEPTH";
		default: return "";
		}
	}

	static std::string generateGUID() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<uint32_t> dis32;
		std::uniform_int_distribution<uint16_t> dis16;
		std::stringstream ss;
		ss << std::hex << std::setfill('0')
			<< std::setw(8) << dis32(gen) << "-"
			<< std::setw(4) << dis16(gen) << "-"
			<< std::setw(4) << ((dis16(gen) & 0x0FFF) | 0x4000) << "-" // UUID v4
			<< std::setw(4) << ((dis16(gen) & 0x3FFF) | 0x8000) << "-" // variant 1
			<< std::setw(4) << dis16(gen)
			<< std::setw(8) << dis32(gen);
		return ss.str();
	}
	static void log(const std::string& message) {
		std::cout << message << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
};
