#pragma once

#include <string>
#include <vector>
#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include <vunikEngine/init.hpp>

namespace vunikEngine {
	struct VKQueueFamilyIndices {
		int graphicsFamily = -1;
		int presentFamily = -1;

		bool isComplete() {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

    class Window {
    friend class Init;

    public:
        Window (void);
        ~Window (void);

        bool createWindow (int width, int height, std::string title, uint32_t app_major = 1, uint32_t app_minor = 0, uint32_t app_patch = 0, uint32_t vk_major = 1, uint32_t vk_minor = 1);

		void render (void);

    private:
        static bool init (void);
        static void deinit (void);

		GLFWwindow* window = nullptr;

		VkInstance vkinst = VK_NULL_HANDLE;
		VkDebugReportCallbackEXT callback = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;

		VkQueue graphicsQueue = VK_NULL_HANDLE;
		VkQueue presentQueue = VK_NULL_HANDLE;

		bool initVulkan (std::string title, uint32_t app_major, uint32_t app_minor, uint32_t app_patch, uint32_t vk_major, uint32_t vk_minor);
		void cleanVulkan (void);

		bool createVkInstance (std::string title, uint32_t app_major, uint32_t app_minor, uint32_t app_patch, uint32_t vk_major, uint32_t vk_minor);
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
