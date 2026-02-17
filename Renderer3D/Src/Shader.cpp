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

		CompileErrors(vertexShader, "Vertex");

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragContent, nullptr);
		glCompileShader(fragmentShader);

		CompileErrors(fragmentShader, "Fragment");

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

	void Shader::CompileErrors(unsigned int shader, const char* name)
	{
		const bool isProgram =
			(std::string(name).find("PROGRAM") != std::string::npos) ||
			(std::string(name).find("Program") != std::string::npos) ||
			(std::string(name).find("program") != std::string::npos);

		GLint success = 0;
		if (isProgram) {
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
		}
		else {
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		}

		if (success == GL_TRUE) return;

		GLint logLen = 0;
		if (isProgram) {
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		}
		else {
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
		}

		std::string log;
		log.resize((logLen > 1) ? static_cast<size_t>(logLen) : 1);

		if (isProgram) {
			glGetProgramInfoLog(shader, logLen, nullptr, log.data());
		}
		else {
			glGetShaderInfoLog(shader, logLen, nullptr, log.data());
		}

		throw std::runtime_error(std::string(name) + " failed:\n" + log);
	}
}