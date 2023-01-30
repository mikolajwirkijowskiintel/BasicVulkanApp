#pragma once
#include "Window.h"
#include "VulkanInstance.h"
#include "PhysicalDeviceManager.h"
#include "LogicalDevice.h"
#include "RenderingPipeline.h"

class RenderEngine
{
public:
	RenderEngine();
	~RenderEngine();
	void run();
private:
	void mainLoop();

	VulkanInstance* vulkanInstance;
	Window* window;
	PhysicalDeviceManager* physicalDeviceManager;
	LogicalDevice* logicalDevice;
	RenderingPipeline* renderingPipeline;
};

