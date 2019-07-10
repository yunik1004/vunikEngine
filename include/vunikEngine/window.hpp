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

		bool isComplete (void) {
			return graphicsFamily >= 0 && presentFamily >= 0;
		}
	};

	struct VKSwapChainSupportDetails {
		VkSurfaceCapabilitiesKHR capabilities = { 0, 0, {0, 0}, {0, 0}, {0, 0}, 0, 0, VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, 0, 0};
		std::vector<VkSurfaceFormatKHR> formats;
		std::vector<VkPresentModeKHR> presentModes;
	};

    class Window {
    friend class ProjectManager;

    public:
        Window (void);
        ~Window (void);

        bool createWindow (uint32_t width, uint32_t height, std::string title);

		void render (void);

    private:
        static bool init (void);
        static void deinit (void);

		GLFWwindow* window = nullptr;

		uint32_t win_width = 0;
		uint32_t win_height = 0;
		std::string win_title = "";

		VkInstance vkinst = VK_NULL_HANDLE;
		VkDebugReportCallbackEXT callback = VK_NULL_HANDLE;
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		
		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		VkDevice device = VK_NULL_HANDLE;

		VkQueue graphicsQueue = VK_NULL_HANDLE;
		VkQueue presentQueue = VK_NULL_HANDLE;

		VkSwapchainKHR swapChain = VK_NULL_HANDLE;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat = VK_FORMAT_UNDEFINED;
		VkExtent2D swapChainExtent = {0, 0};

		std::vector<VkImageView> swapChainImageViews;

		bool initVulkan (void);
		void cleanVulkan (void);

		bool createVkInstance (void);
		bool setupVkDebugCallback (void);

		bool createVkSurface (void);

		bool pickVkPhysicalDevice (void);
		bool isVkDeviceSuitable (VkPhysicalDevice device);
		bool checkDeviceExtensionSupport (VkPhysicalDevice device);

		VKQueueFamilyIndices findVkQueueFamilies (VkPhysicalDevice device);

		bool createVkLogicalDevice (void);

		bool createVkSwapChain (void);

		VkSurfaceFormatKHR chooseSwapSurfaceFormat (const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode (const std::vector<VkPresentModeKHR> availablePresentModes);
		VkExtent2D chooseSwapExtent (const VkSurfaceCapabilitiesKHR& capabilities);

		VKSwapChainSupportDetails querySwapChainSupport (VkPhysicalDevice device);

		bool createImageViews (void);

		bool createGraphicsPipeline (void);

		std::vector<const char*> Window::getRequiredExtensions (void);
		bool checkValidationLayerSupport (void);

		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData);
    };
}
