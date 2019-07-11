#include <iostream>
#include <vector>
#include <vunikEngine/projectManager.hpp>
#include <vunikEngine/shader.hpp>
#include <vunikEngine/window.hpp>

int main (void) {
    vunikEngine::ProjectManager::init();

	vunikEngine::Shader vert = vunikEngine::Shader(vunikEngine::ShaderKind::VERTEX);
	vert.readFile("shader/vert.spv");

	vunikEngine::Shader frag = vunikEngine::Shader(vunikEngine::ShaderKind::FRAGMENT);
	frag.readFile("shader/frag.spv");

	std::vector<vunikEngine::Shader> shaders;

	shaders.push_back(vert);
	shaders.push_back(frag);

	vunikEngine::Window window;
	window.createWindow(1024, 768, "Hello world");
	window.createGraphicsPipeline(shaders);

	window.render();
    
	vunikEngine::ProjectManager::deinit();
    return 0;
}
