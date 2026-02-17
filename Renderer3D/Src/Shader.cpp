#include "Shader.hpp"
#include <sstream>

namespace BenScr {
	std::string ReadAllText(const std::string& path) {
		std::ifstream file(path, std::ios::binary);
		if (!file) {
			throw std::runtime_error("Failed to open file at path: " + path);
		}

		std::ostringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	Shader::Shader(const std::string& vertPath, const std::string& fragPath) {
		std::string vert = ReadAllText(vertPath);
		std::string frag = ReadAllText(fragPath);

		const char* vertContent = vert.c_str();
		const char* fragContent = frag.c_str();

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertContent, nullptr);
		glCompileShader(vertexShader);

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragContent, nullptr);
		glCompileShader(fragmentShader);

		Id = glCreateProgram();
		glAttachShader(Id, vertexShader);
		glAttachShader(Id, fragmentShader);

		glLinkProgram(Id);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void Shader::Activate() {
		glUseProgram(Id);
	}
	void Shader::Delete() {
		glDeleteProgram(Id);
	}
}