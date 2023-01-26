#include "vulkanConfig.h"


void vulkanConfig::configShaderModuleCreateInfo(VkShaderModuleCreateInfo* createInfo, const std::vector<char>& code)
{
	createInfo->sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo->codeSize = code.size();
	createInfo->pCode = reinterpret_cast<const uint32_t*>(code.data());
}
