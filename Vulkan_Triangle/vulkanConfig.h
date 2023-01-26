#pragma once

#include <vulkan/vulkan_core.h>
#include <vector>

/// <summary>
/// Functions responsible for setting up createInfo structs
/// </summary>
namespace vulkanConfig
{
	void configShaderModuleCreateInfo(VkShaderModuleCreateInfo* createInfo, const std::vector<char>& code);


};

