#pragma once

#include <string>
#include <vector>
#include <vulkan/vulkan.h>
#include <vunikEngine/window.hpp>

namespace vunikEngine {
	enum class ShaderKind {
		VERTEX = VK_SHADER_STAGE_VERTEX_BIT,
		FRAGMENT = VK_SHADER_STAGE_FRAGMENT_BIT
	};

	class Shader {
	friend class Window;

	public:
		Shader (ShaderKind kind);
		~Shader (void);

		bool readFile (const std::string& fileName);

	private:
		ShaderKind kind;

		std::vector<char> code;
	};
}
