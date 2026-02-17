#pragma once
#include "VBO.hpp"
#include <glad/glad.h>

namespace BenScr {
	class VAO {
	public:
		VAO();

		void LinkVBO(VBO& vbo, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
	private:
		GLuint Id;
	};
}