#pragma once
#include "VBO.hpp"
#include <glad/glad.h>

namespace BenScr {
	class VAO {
	public:
		VAO();

		void LinkAttrib(VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
		void Bind();
		void Unbind();
		void Delete();
	private:
		GLuint Id;
	};
}