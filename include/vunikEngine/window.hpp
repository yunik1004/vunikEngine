#pragma once

#include <string>
#ifndef GLFW_INCLUDE_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif
#include <GLFW/glfw3.h>
#include <vunikEngine/init.hpp>

namespace vunikEngine {
    class Window {
    friend class Init;

    public:
        Window (void);
        ~Window (void);

        bool createWindow (int width, int height, std::string title, uint32_t vk_major = 1, uint32_t vk_minor = 1, uint32_t app_major = 1, uint32_t app_minor = 0, uint32_t app_patch = 0);

		void render (void);

    private:
        static bool init (void);
        static void deinit (void);

		VkInstance vkinst = nullptr;
        GLFWwindow* window = nullptr;
    };
}
