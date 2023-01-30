#pragma once
#include "LogicalDevice.h"
#include <string>
#define ALPHA_BLEND

class RenderingPipeline
{
public:
	RenderingPipeline(LogicalDevice* logicalDevice);
	~RenderingPipeline();
	void drawFrame();

private:
	// initialization
	void createRenderPass();
	void createGraphicsPipeline();

	void createFramebuffers();

	void createCommandPool();
	void createCommandBuffers();
	
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	
	
	// utility functions
	VkShaderModule createShaderModule(const std::vector<char>& code);
	static std::vector<char> readFile(const std::string& filename);


	// member variables
	LogicalDevice* logicalDevice;

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkCommandPool commandPool;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	std::vector<VkCommandBuffer> commandBuffers;

	uint32_t currentFrame = 0;
};

