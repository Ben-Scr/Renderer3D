#pragma once
#include <glad/glad.h>
#include <string>
#include <cerrno>
#include <fstream>
#include <iostream>

namespace BenScr {
	std::string ReadAllText(const std::string& path);

	class Shader {
	public:
		Shader(const std::string& vertPath, const std::string& fragPath);

		void Activate();
		void Delete();
	private:
		GLuint Id;
	};
}