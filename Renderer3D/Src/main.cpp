#include <iostream>
#include <iostream>
#include <cassert>
#include <chrono>
#include <string>

#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "Shader.hpp"

// External Libraries
#include <GLFW/glfw3.h>
#include <glad/glad.h> 

using namespace BenScr;

void Run() {
	assert(glfwInit());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,

	    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f,
	};

	GLuint indices[] = {
		0, 3, 5,
		3, 2, 4,
		5, 4, 1
	};

	GLFWwindow* window = glfwCreateWindow(800, 800, "Renderer3D", nullptr, nullptr);
	assert(window);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glViewport(0, 0, 800, 800);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");

	VAO va;
	va.Bind();

	VBO vb(vertices, sizeof(vertices));
	EBO eb(indices, sizeof(indices));

	va.LinkVBO(vb, 0);

	va.Unbind();
	vb.Unbind();
	eb.Unbind();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto last = std::chrono::steady_clock::now();

	while (!glfwWindowShouldClose(window)) {

		int w, h;
		glfwGetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);

		auto now = std::chrono::steady_clock::now();

		auto elapsed = std::chrono::duration<double>(now - last);
		double deltaTime = elapsed.count();

		std::string title = std::to_string(1.0 / deltaTime) + " FPS\n";
		glfwSetWindowTitle(window, title.c_str());

		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		va.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		last = now;
	}

	vb.Delete();
	eb.Delete();
	va.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
}

int main() {
	std::cout << "Hello World!";

	try {
		Run();
	}
	catch (const std::exception& ex) {
		std::cout << "Caught Exception: " << ex.what();
		return -1;
	}


	return 0;
}