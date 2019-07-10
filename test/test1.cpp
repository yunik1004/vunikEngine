#include <iostream>
#include <vunikEngine/projectManager.hpp>
#include <vunikEngine/window.hpp>

int main (void) {
    vunikEngine::ProjectManager::init();
	vunikEngine::Window window;
	window.createWindow(1024, 768, "Hello world");
	window.render();
    vunikEngine::ProjectManager::deinit();
    return 0;
}
