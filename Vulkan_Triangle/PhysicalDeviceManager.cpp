#include "PhysicalDeviceManager.h"
#include <set>
#include <stdexcept>
#include <string>

PhysicalDeviceManager::PhysicalDeviceManager(VulkanInstance *instance)
    : instance(instance) {
  // The manager must obtain the list of all Vulkan compatible devices.
  uint32_t physicalDeviceCount;
  vkEnumeratePhysicalDevices(instance->getInstance(), &physicalDeviceCount,
                             nullptr);
  allPhysicalDevices.resize(physicalDeviceCount);
  vkEnumeratePhysicalDevices(instance->getInstance(), &physicalDeviceCount,
                             allPhysicalDevices.data());

  if (allPhysicalDevices.empty()) {
    throw std::runtime_error("failed to find GPUs with Vulkan support!");
  }
}

VkPhysicalDevice PhysicalDeviceManager::findCompatibleDevice() {
  VkPhysicalDevice returnDevice = VK_NULL_HANDLE;

  for (VkPhysicalDevice physicalDevice : allPhysicalDevices) {
    if (bDeviceMeetsAllRequirements(physicalDevice)) {
      returnDevice = physicalDevice;
    }
  }

  if (returnDevice == VK_NULL_HANDLE) {
    throw std::runtime_error("Found no supported devices.");
  }

  return returnDevice;
}

bool PhysicalDeviceManager::bDeviceMeetsAllRequirements(
    VkPhysicalDevice device) {
  QueueFamilyIndices qFamilyIndices = findQueueFamiliesIndices(device); // Name to be revised
	
  return qFamilyIndices.bQueueFamilySupportComplete() && bDeviceSupportsRequiredExtensions(device) && bDeviceSupportsBasicSwapchain(device);
}

bool PhysicalDeviceManager::bDeviceSupportsRequiredExtensions(
    VkPhysicalDevice device) {
  uint32_t extensionCount;
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                       nullptr);
  std::vector<VkExtensionProperties> availableExtensions(extensionCount);
  vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,
                                       availableExtensions.data());

  std::set<std::string> requiredExtensions(deviceRequiredExtensions.begin(),
                                           deviceRequiredExtensions.end());

  for (const auto &extension : availableExtensions) {
    requiredExtensions.erase(extension.extensionName);
  }

  bool allExtensionsFoundOnDevice = requiredExtensions.empty();

  return allExtensionsFoundOnDevice;
}

SwapChainSupportDetails PhysicalDeviceManager::querySwapchainSupportDetails(VkPhysicalDevice device)
{
	VkSurfaceKHR surface = instance->getWindowSurface();
	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device, surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, surface, &formatCount, details.formats.data());
	}

	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, surface, &presentModeCount, details.presentModes.data());
	}

	return details;

}

uint32_t PhysicalDeviceManager::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties, VkPhysicalDevice physicalDevice)
{
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		bool memoryTypeCorrect = typeFilter & (1 << i);
		bool memorySupportsProperties = (memProperties.memoryTypes[i].propertyFlags & properties) == properties;
		
		if (memoryTypeCorrect && memorySupportsProperties) {
			return i;
		}

	}

	throw std::runtime_error("failed to find suitable memory type!");

}

bool PhysicalDeviceManager::bDeviceSupportsBasicSwapchain(VkPhysicalDevice device)
{
	SwapChainSupportDetails details = querySwapchainSupportDetails(device);
	
	bool deviceSupportsFormats = !details.formats.empty();
	bool deviceSupportsPresentationModes = !details.presentModes.empty();

	return deviceSupportsFormats && deviceSupportsPresentationModes;
}

QueueFamilyIndices
PhysicalDeviceManager::findQueueFamiliesIndices(VkPhysicalDevice device) {
	QueueFamilyIndices indices;
	
	uint32_t queueFamilyCount;
	std::vector<VkQueueFamilyProperties> queueFamilyProperties;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	queueFamilyProperties.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilyProperties.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilyProperties) {
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, instance->getWindowSurface(), &presentSupport);
		if (presentSupport) {
			indices.presentationFamily = i;
		}
		if (indices.bQueueFamilySupportComplete()) break;
		i++;
	}
	return indices;
}
