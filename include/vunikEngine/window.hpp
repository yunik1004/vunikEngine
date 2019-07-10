#pragma once

#include <string>
#include <vector>
#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include <vunikEngine/projectManager.hpp>

namespace vunikEngine {
	struct VKQueueFamilyIndices {
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

    class Window {
    friend class ProjectManager;

    public:
        Window (void);
        ~Window (void);

        bool createWindow (int width, int height, std::string title);

		void render (void);

    private:
        static bool init (void);
        static void deinit (void);

		GLFWwindow* window = nullptr;

		std::string win_title = "";

		VkInstance vkinst = VK_NULL_HANDLE;
		VkDebugReportCallbackEXT callback = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;

		VkQueue graphicsQueue = VK_NULL_HANDLE;
		VkQueue presentQueue = VK_NULL_HANDLE;

		bool initVulkan (void);
		void cleanVulkan (void);

		bool createVkInstance (void);
		bool setupVkDebugCallback (void);

		bool createVkSurface (void);

		bool pickVkPhysicalDevice (void);
		bool isVkDeviceSuitable (VkPhysicalDevice device);

		VKQueueFamilyIndices findVkQueueFamilies (VkPhysicalDevice device);

		bool createVkLogicalDevice (void);

		std::vector<const char*> Window::getRequiredExtensions (void);
		bool checkValidationLayerSupport (void);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
    };
}
