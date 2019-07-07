#include <vunikEngine/window.hpp>

#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>

namespace vunikEngine {
    Window::Window (void) {}

    Window::~Window (void) {
        if (window) {
            glfwDestroyWindow((GLFWwindow*)window);
        }
    }

    bool Window::createWindow (int width, int height, std::string title) {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            fprintf_s(stderr, "GLFW Error: Failed to create window\n");
            return false;
        }

		return true;
    }

	void Window::render (void) {
		while (!glfwWindowShouldClose((GLFWwindow*)window)) {
			glfwPollEvents();
		}
	}

	bool Window::init(void) {
		/* Initialize glfw */
		glfwSetErrorCallback([](int errorCode, const char* errorDescription) {
			fprintf_s(stderr, "GLFW Error: %s\n", errorDescription);
		});

		if (!glfwInit()) {
			fprintf_s(stderr, "GLFW Error: Failed to initialize\n");
			return false;
		}

		/* Do not use OpenGL */
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		/* Anti-aliasing */
		glfwWindowHint(GLFW_SAMPLES, 4);

		return true;
	}

	void Window::deinit(void) {
		glfwTerminate();
	}
}
