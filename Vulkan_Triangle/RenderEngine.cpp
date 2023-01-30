#include "RenderEngine.h"
#include "ScopeTimer.h"
#include <thread>

bool shouldClose = false;

void renderingThreadFunction(RenderingPipeline* renderPipeline) {
	while (!shouldClose) {
		renderPipeline->drawFrame();
	}
}

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
	auto glfwWindow = window->getWindow();
	std::thread renderingThread(renderingThreadFunction, renderingPipeline);

	while(!shouldClose) {
		glfwPollEvents();
		shouldClose = glfwWindowShouldClose(glfwWindow);
	}
	renderingThread.join();
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