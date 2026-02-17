#include <iostream>
#include <iostream>
#include <cassert>
#include <chrono>
#include <string>

#include "VBO.hpp"
#include "EBO.hpp"
#include "VAO.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

// External Libraries
#include <GLFW/glfw3.h>
#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace BenScr;

GLfloat vertices[] =
{ //     COORDINATES     /        COLORS      /   TexCoord  //
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

void Run() {
	assert(glfwInit());
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Renderer3D", nullptr, nullptr);
	assert(window);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));

	glViewport(0, 0, 800, 800);
	glClearColor(0.1f, 0.1f, 0.1f, 1.f);

	Shader shaderProgram("Shaders/default.vert", "Shaders/default.frag");
	shaderProgram.Activate();

	VAO va;
	va.Bind();

	VBO vb(vertices, sizeof(vertices));
	EBO eb(indices, sizeof(indices));

	va.LinkAttrib(vb, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	va.LinkAttrib(vb, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	va.LinkAttrib(vb, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	va.Unbind();
	vb.Unbind();
	eb.Unbind();


	GLuint uniID = glGetUniformLocation(shaderProgram.GetProgram(), "scale");

	Texture texture("brick.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
	texture.TexUnit(shaderProgram, "tex0", 0);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto last = std::chrono::steady_clock::now();
	float rotation = 0.f;

	while (!glfwWindowShouldClose(window)) {

		int w, h;
		glfwGetWindowSize(window, &w, &h);
		glViewport(0, 0, w, h);

		auto now = std::chrono::steady_clock::now();

		auto elapsed = std::chrono::duration<double>(now - last);
		double deltaTime = elapsed.count();

		std::string title = std::to_string(1.0 / deltaTime) + " FPS\n";
		glfwSetWindowTitle(window, title.c_str());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);
		view = glm::translate (view, glm::vec3(0.0f, -0.5f, -2.0f));
		proj = glm::perspective(glm::radians(45.0f), (float)(w / h), 0.1f, 100.f);

		rotation += deltaTime * 10.f;
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

		int modelLoc = glGetUniformLocation(shaderProgram.GetProgram(), "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		int viewLoc = glGetUniformLocation(shaderProgram.GetProgram(), "view");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		int projLoc = glGetUniformLocation(shaderProgram.GetProgram(), "proj");
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));


		glUniform1f(uniID, 0.5f);
		texture.Bind();
		va.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

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