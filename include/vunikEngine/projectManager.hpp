#pragma once

#include <cstdint>

namespace vunikEngine {
    class ProjectManager {
    public:
        static bool init (void);
        static void deinit (void);

		static void setAppVersion(uint32_t app_major, uint32_t app_minor, uint32_t app_patch);
		static void setVulkanVersion(uint32_t vk_major, uint32_t vk_minor);

		static uint32_t app_major;
		static uint32_t app_minor;
		static uint32_t app_patch;

		static uint32_t vk_major;
		static uint32_t vk_minor;
    };
}
