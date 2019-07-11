#include <vunikEngine/shader.hpp>
#include <fstream>
#include <vector>

namespace vunikEngine {
	Shader::Shader (ShaderKind kind) {
		this->kind = kind;
	}

	Shader::~Shader (void) {}

	bool Shader::readFile (const std::string& fileName) {
		std::ifstream file(fileName, std::ios::ate | std::ios::binary);

		if (!file.is_open()) {
			fprintf_s(stderr, "Failed to open file '%s'\n", fileName.c_str());
			return false;
		}

		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);
		
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();

		code = buffer;

		return true;
	}
}
