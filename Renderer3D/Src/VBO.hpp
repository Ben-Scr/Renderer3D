#pragma once

#include <glad/glad.h>

namespace BenScr {
	class VBO {
	public:
		VBO(GLfloat* vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	private:
		GLuint Id;
	};
}