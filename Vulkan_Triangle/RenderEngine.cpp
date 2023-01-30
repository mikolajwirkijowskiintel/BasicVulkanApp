#include "RenderEngine.h"

RenderEngine::RenderEngine()
{
	window = nullptr;
	vulkanInstance = nullptr;
	physicalDeviceManager = nullptr;
	logicalDevice = nullptr;
	renderingPipeline = nullptr;

}


void RenderEngine::run()
{
	window = new Window();
	vulkanInstance = new VulkanInstance(window);
	physicalDeviceManager = new PhysicalDeviceManager(vulkanInstance);
	logicalDevice = new LogicalDevice(physicalDeviceManager);
	renderingPipeline = new RenderingPipeline(logicalDevice);

	mainLoop();
}

void RenderEngine::mainLoop()
{
	while (!glfwWindowShouldClose(window->getWindow())) {
		glfwPollEvents();
		renderingPipeline->drawFrame();
	}
	vkDeviceWaitIdle(logicalDevice->getLogicalDevice());
}

RenderEngine::~RenderEngine()
{
	delete renderingPipeline;
	delete logicalDevice;
	delete physicalDeviceManager;
	delete vulkanInstance;
	delete window;
}