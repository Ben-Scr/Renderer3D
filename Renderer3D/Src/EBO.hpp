#pragma once

#include <glad/glad.h>

namespace BenScr {
	class EBO {
	public:
		EBO(GLuint* indices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
	private:
		GLuint Id;
	};
}