#include "VAO.hpp"

namespace BenScr {
	VAO::VAO() {
		glGenVertexArrays(1, &Id);
	}


	void VAO::LinkVBO(VBO& vbo, GLuint layout) {
		vbo.Bind();
		glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		glEnableVertexAttribArray(layout);
		vbo.Unbind();
	}
	void VAO::Bind() {
		glBindVertexArray(Id);
	}
	void VAO::Unbind() {
		glBindVertexArray(0);
	}
	void VAO::Delete() {
		glDeleteVertexArrays(1, &Id);
	}
}