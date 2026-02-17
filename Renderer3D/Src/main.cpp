#include <iostream>
#include <iostream>
#include <cassert>
#include <chrono>
#include <string>

// External Libraries
#include <GLFW/glfw3.h>
#include <glad/glad.h> 

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
	glClearColor(1.f, 1.f, 1.f, 1.f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto last = std::chrono::steady_clock::now();

	float hue = 0.f;

	while (!glfwWindowShouldClose(window)) {
		auto now = std::chrono::steady_clock::now();

		auto elapsed = std::chrono::duration<double>(now - last);
		double deltaTime = elapsed.count();

		std::string title = std::to_string(1.0 / deltaTime) + " FPS\n";
		glfwSetWindowTitle(window, title.c_str());

		hue = std::fmod(hue + deltaTime * 0.1f, 1.0f);

		float r = std::sin(6.28318f * hue + 0.0f) * 0.5f + 0.5f;
		float g = std::sin(6.28318f * hue + 2.09439f) * 0.5f + 0.5f;
		float b = std::sin(6.28318f * hue + 4.18879f) * 0.5f + 0.5f;

		glClearColor(r, g, b, 1.0f);

		glClearColor(r, g, b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();

		last = now;
	}

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