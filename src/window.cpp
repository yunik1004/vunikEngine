#include <vunikEngine/window.hpp>
#include <iostream>

namespace vunikEngine {
	const std::vector<const char*> validationLayers = {
		"VK_LAYER_LUNARG_standard_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

	VkResult createDebugReportCallbackEXT (VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		} else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void destroyDebugReportCallbackEXT (VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	Window::Window(void) {}

    Window::~Window (void) {
		destroyDebugReportCallbackEXT(vkinst, callback, nullptr);

		if (vkinst) {
			vkDestroyInstance(vkinst, nullptr);
		}

        if (window) {
            glfwDestroyWindow(window);
        }
    }

    bool Window::createWindow (int width, int height, std::string title, uint32_t app_major, uint32_t app_minor, uint32_t app_patch, uint32_t vk_major, uint32_t vk_minor) {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        if (!window) {
            fprintf_s(stderr, "GLFW Error: Failed to create window\n");
            return false;
        }

		if (!createVkInstance(title, app_major, app_minor, app_patch, vk_major, vk_minor)) {
			return false;
		}

		if (!setupVkDebugCallback()) {
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

	bool Window::createVkInstance (std::string title, uint32_t app_major, uint32_t app_minor, uint32_t app_patch, uint32_t vk_major, uint32_t vk_minor) {
		if (enableValidationLayers && !checkValidationLayerSupport()) {
			fprintf_s(stderr, "Vulkan error: Requested validation layers are not available\n");
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

		auto extensions = getRequiredExtensions();
		createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();

		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		} else {
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateInstance(&createInfo, nullptr, &vkinst) != VK_SUCCESS) {
			fprintf_s(stderr, "Vulkan error: Failed to create instance\n");
			return false;
		}
		return true;
	}

	bool Window::setupVkDebugCallback (void) {
		if (!enableValidationLayers) {
			return false;
		}

		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		if (createDebugReportCallbackEXT(vkinst, &createInfo, nullptr, &callback) != VK_SUCCESS) {
			fprintf_s(stderr, "Vulkan error: Failed to set up debug callback\n");
			return false;
		}
		return true;
	}

	std::vector<const char*> Window::getRequiredExtensions (void) {
		uint32_t glfwExtensionCount = 0;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

		if (enableValidationLayers) {
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		}

		return extensions;
	}

	bool Window::checkValidationLayerSupport(void) {
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		for (const char* layerName : validationLayers) {
			bool layerFound = false;

			for (const auto& layerProperties : availableLayers) {
				if (strcmp(layerName, layerProperties.layerName) == 0) {
					layerFound = true;
					break;
				}
			}

			if (!layerFound) {
				return false;
			}
		}

		return true;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL Window::debugCallback (VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
		fprintf_s(stderr, "Vulkan error: validation layer: %s\n", msg);
		return VK_FALSE;
	}
}
