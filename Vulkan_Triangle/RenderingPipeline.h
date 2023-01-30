#pragma once
#include "LogicalDevice.h"
#include "triangle_vertices.h"
#include <string>

#define ALPHA_BLEND

class RenderingPipeline
{
public:
	RenderingPipeline(LogicalDevice* logicalDevice);
	~RenderingPipeline();
	void drawFrame();
	static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
	// initialization
	void createRenderPass();
	void createGraphicsPipeline();

	void createFramebuffers();
	void createVertexBuffer();
	void createCommandPool();
	void createCommandBuffers();
	
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	
	
	// utility functions
	VkShaderModule createShaderModule(const std::vector<char>& code);
	static std::vector<char> readFile(const std::string& filename);
	void swapChainInvalidateReplace();
	void cleanupSwapchain();
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	// other member variables
	LogicalDevice* logicalDevice;

	VkRenderPass renderPass;
	VkPipelineLayout pipelineLayout;
	VkPipeline graphicsPipeline;

	VkBuffer vertexBuffer;
	VkDeviceMemory vertexBufferMemory;
	
	std::vector<VkCommandBuffer> commandBuffers;
	std::vector<VkFramebuffer> swapChainFramebuffers;
	
	VkCommandPool commandPool;
	bool framebufferResized = false;

	uint32_t currentFrame = 0;
};

