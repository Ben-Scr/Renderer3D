#pragma once

#include"Shader.hpp"
#include<glad/glad.h>

namespace BenScr {
	class Texture
	{
	public:
		GLuint Id;
		GLenum type;
		Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

		void TexUnit(Shader& shader, const char* uniform, GLuint unit);

		void Bind();
		void Unbind();
		void Delete();
	};
}