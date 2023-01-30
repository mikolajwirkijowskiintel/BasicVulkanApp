#pragma once
#include "VulkanInstance.h"
#include <optional>

struct QueueFamilyIndices {
	std::optional<uint32_t> graphicsFamily;
	std::optional<uint32_t> presentationFamily;
	bool bQueueFamilySupportComplete() {
		return graphicsFamily.has_value() && presentationFamily.has_value();
	}
};

struct SwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class PhysicalDeviceManager
{
public:
	PhysicalDeviceManager(VulkanInstance* instanceWrapper);
	VkPhysicalDevice findCompatibleDevice();
	QueueFamilyIndices findQueueFamiliesIndices(VkPhysicalDevice device);
	SwapChainSupportDetails querySwapchainSupportDetails(VkPhysicalDevice device);
	const std::vector<const char*> getDeviceRequiredExtensions() { return deviceRequiredExtensions; }

	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice);

	VulkanInstance* getVulkanInstance() { return instance; }

private:
	
	bool bDeviceMeetsAllRequirements(VkPhysicalDevice device);
	bool bDeviceSupportsRequiredExtensions(VkPhysicalDevice device);
	bool bDeviceSupportsBasicSwapchain(VkPhysicalDevice device);
	
	// Private member variables
	std::vector<VkPhysicalDevice> allPhysicalDevices;
	VulkanInstance* instance;
	const std::vector<const char*> deviceRequiredExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
};

