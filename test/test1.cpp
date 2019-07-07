#include <iostream>
#include <vunikEngine/init.hpp>
#include <vunikEngine/window.hpp>

int main (void) {
    vunikEngine::Init::init();

	vunikEngine::Window window;
	window.createWindow(1024, 768, "Hello world");
	
	window.render();

    vunikEngine::Init::deinit();
    return 0;
}
