#pragma once
#include "PhysicalDeviceManager.h"
/// <summary>
/// Manages the VkLogicaDevice and associated queues, and the swapchain.
/// </summary>
class LogicalDevice
{
public:
	LogicalDevice(PhysicalDeviceManager* physicalDeviceManager);
	~LogicalDevice();
	VkDevice getLogicalDevice() { return logicalDevice; }
	VkFormat getSwapChainImageFormat() const { return swapChainImageFormat; }

	VkExtent2D getSwapChainExtent() const { return swapChainExtent; }
	std::vector<VkImage> getSwapChainImages() const { return swapChainImages; }
	std::vector<VkImageView> getSwapChainImageViews() const { return swapChainImageViews; }
	PhysicalDeviceManager* getPhysicalDeviceManager() const { return physicalDeviceManager; }

	VkPhysicalDevice getCurrentPhysicalDevice() const { return currentPhysicalDevice; }

	std::vector<VkFence> getInFlightFence() const { return inFlightFences; }
	std::vector<VkSemaphore> getRenderFinishedSemaphore() const { return renderFinishedSemaphores; }
	std::vector<VkSemaphore> getImageAvailableSemaphore() const { return imageAvailableSemaphores; }
	VkSwapchainKHR getSwapChain() const { return swapChain; }
	VkQueue getGraphicsQueue() const { return graphicsQueue; }
	VkQueue getPresentationQueue() const { return presentationQueue; }
	void onRenderingPipelineSwapChainInvalidateReplace(); // Somehow avoid having that public?
	
	static const int MAX_FRAMES_IN_FLIGHT = 3;

private:

	void createLogicalDevice();
	void createSwapchain();
	void createImageViews();
	void createSyncObjects();
	void cleanupSwapChain();

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentationMode(const std::vector<VkPresentModeKHR>& availableFormats);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

	// Core variables
	PhysicalDeviceManager* physicalDeviceManager;
	VkPhysicalDevice currentPhysicalDevice;
	
	
	VkQueue graphicsQueue;
	VkQueue presentationQueue;
	VkDevice logicalDevice;

	// Swapchain directly related variables
	VkSwapchainKHR swapChain;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapChainImageViews;
	VkFormat swapChainImageFormat;
	VkExtent2D swapChainExtent;
	// Asynchronous synchronization objects
	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;

};

