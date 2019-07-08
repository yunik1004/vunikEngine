#include <vunikEngine/window.hpp>
#include <iostream>

namespace vunikEngine {
    Window::Window (void) {}

    Window::~Window (void) {
		if (vkinst) {
			vkDestroyInstance(vkinst, nullptr);
		}

        if (window) {
            glfwDestroyWindow(window);
        }
    }

    bool Window::createWindow (int width, int height, std::string title, uint32_t vk_major, uint32_t vk_minor, uint32_t app_major, uint32_t app_minor, uint32_t app_patch) {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            fprintf_s(stderr, "GLFW Error: Failed to create window\n");
            return false;
        }

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = title.c_str();
		appInfo.applicationVersion = VK_MAKE_VERSION(app_major, app_minor, app_patch);
		appInfo.pEngineName = "vunikEngine";
		appInfo.apiVersion = VK_MAKE_VERSION(vk_major, vk_minor, 0);

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = 0;

		if (vkCreateInstance(&createInfo, nullptr, &vkinst) != VK_SUCCESS) {
			fprintf_s(stderr, "Vulkan error: Failed to create instance\n");
			return false;
		}
		return true;
    }

	void Window::render (void) {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();
		}
	}

	bool Window::init(void) {
		/* Initialize glfw */
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
