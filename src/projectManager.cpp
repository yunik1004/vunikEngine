#include <vunikEngine/projectManager.hpp>
#include <vunikENgine/window.hpp>

namespace vunikEngine {
	uint32_t ProjectManager::app_major = 1;
	uint32_t ProjectManager::app_minor = 0;
	uint32_t ProjectManager::app_patch = 0;

	uint32_t ProjectManager::vk_major = 1;
	uint32_t ProjectManager::vk_minor = 1;

    bool ProjectManager::init (void) {
        if (!Window::init()) {
            return false;
        }
        return true;
    }

    void ProjectManager::deinit (void) {
        Window::deinit();
    }

	void ProjectManager::setAppVersion(uint32_t major, uint32_t minor, uint32_t patch) {
		app_major = major;
		app_minor = minor;
		app_patch = patch;
	}

	void ProjectManager::setVulkanVersion(uint32_t major, uint32_t minor) {
		vk_major = major;
		vk_minor = minor;
	}
}
