#include "HelloTriangleApplication.hpp"

#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>
namespace TriangleApp
{
	
	void HelloTriangleApplication::run()
	{
	    initWindow();
	    initVulkan();
	    mainLoop();
	    cleanup();
	    checkValidationLayerSupport();
	}
	
	void HelloTriangleApplication::mainLoop()
	{
	    while (!glfwWindowShouldClose(window)) {
	        glfwPollEvents();
	    }
		
	}
	
	VkExtent2D HelloTriangleApplication::chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) return capabilities.currentExtent;
		else {
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			VkExtent2D actualExtent = {
				static_cast<uint32_t>(width),
				static_cast<uint32_t>(height)
			};
			actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
			actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);
			return actualExtent;
		}
	}

	VkSurfaceFormatKHR HelloTriangleApplication::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
	{
		for (const auto& availableFormat : availableFormats) {
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				return availableFormat;
			}
		}
		
		return availableFormats[0];
	}

	SwapChainSupportDetails HelloTriangleApplication::querySwapChainSupport(VkPhysicalDevice device)
	{
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

	bool HelloTriangleApplication::checkDeviceExtensionSupport(VkPhysicalDevice device)
	{
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());
	
		std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());
	
		for (const auto& extension : availableExtensions) {
			requiredExtensions.erase(extension.extensionName);
		}
	
		return requiredExtensions.empty();
	
	}
	
	void HelloTriangleApplication::DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator)
	{
	    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
	    if (func != nullptr) {
	        func(instance, debugMessenger, pAllocator);
	    }  
	}
	
	VkResult HelloTriangleApplication::CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger)
	{
	    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
	    if (func != nullptr) {
	        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
	    }
	    else {
	        return VK_ERROR_EXTENSION_NOT_PRESENT;
	    }
	
	}
	
	void HelloTriangleApplication::initVulkan()
	{
	    createInstance();
	    setupDebugMessenger();
		createSurface();
	    pickPhysicalDevice();
	    createLogicalDevice();
		createSwapChain();
		
	
	}
	
	void HelloTriangleApplication::createInstance()
	{
	    if (enableValidationLayers && !checkValidationLayerSupport()) {
	        throw std::runtime_error("Requested validation layers not available.");
	    }
	    VkApplicationInfo appInfo{};
	    setupAppInfo(appInfo);
	
	    VkInstanceCreateInfo createInfo{};
	    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	
	    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
	    if (enableValidationLayers) {
	        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
	        createInfo.ppEnabledLayerNames = validationLayers.data();
	        populateDebugMessengerCreateInfo(debugCreateInfo);
	        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
	    }
	    else {
	        createInfo.enabledLayerCount = 0;
	        createInfo.pNext = nullptr;
	    }
	    createInfo.pApplicationInfo = &appInfo;
	    auto req_extensions = getRequiredExtensions();
	    createInfo.enabledExtensionCount = static_cast<uint32_t>(req_extensions.size());
	    createInfo.ppEnabledExtensionNames = req_extensions.data();
	
	
	    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); 
	
	    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
	        throw std::runtime_error("failed to create instance!");
	    }
	    //uint32_t extensionCount = 0;
	    //vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	
	    //std::vector<VkExtensionProperties> extensions(extensionCount);
	    //vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
	    
	
	}
	
	void HelloTriangleApplication::createSurface()
	{
		if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS) {
			throw std::runtime_error("failed to create window surface!");
		}
	
	}
	
	void HelloTriangleApplication::createLogicalDevice()
	{
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	
	    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	    std::set<uint32_t> uniqueQueueFamilies =
	    {
	        indices.graphicsFamily.value(),
	        indices.presentFamily.value()
	    };
		float queuePriority = 1.0f;
		
	    for (uint32_t queueFamily : uniqueQueueFamilies) {
			VkDeviceQueueCreateInfo queueCreateInfo{};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &queuePriority;
			queueCreateInfos.push_back(queueCreateInfo);
		}
	
	    VkPhysicalDeviceFeatures deviceFeatures{};
	
		VkDeviceCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	
		createInfo.pEnabledFeatures = &deviceFeatures;
	
		createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
	    createInfo.ppEnabledExtensionNames = deviceExtensions.data();
	
		if (enableValidationLayers) {
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else {
			createInfo.enabledLayerCount = 0;
		}
		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
			throw std::runtime_error("failed to create logical device!");
		}
	    vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
	    vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
	}
	
	bool HelloTriangleApplication::checkGLFWLayersSupport()
	{
	    uint32_t glfwExtensionCount = 0;
	    std::vector<const char*> glfwExtensions;
	
	    glfwExtensions = getRequiredExtensions();
	
	    std::vector<VkExtensionProperties> extensions = fillVectorFromFunction(static_cast<const char*>(nullptr), vkEnumerateInstanceExtensionProperties);
	
	    for (int i = 0; i < glfwExtensionCount; i++) {
	        bool matched = false;
	        for (const auto& extension : extensions) {
	            bool extensionNamesEqual = std::strcmp(glfwExtensions[i], extension.extensionName) == 0;
	            if (extensionNamesEqual) {
	                matched = true;
	            }
	        }
	        if (!matched) return false;
	        return true;
	    }
	    return true;
	}
	
	std::vector<const char*> HelloTriangleApplication::getRequiredExtensions()
	{
	    uint32_t glfwExtensionCount = 0;
	    const char** glfwExtensions;
	    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	
	    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
	
	    if (enableValidationLayers) {
	        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
	    }
	
	    return extensions;
	}
	
	void HelloTriangleApplication::pickPhysicalDevice()
	{
	    physicalDevice = VK_NULL_HANDLE;
	    std::vector<VkPhysicalDevice> physicalDevices = fillVectorFromFunction<VkInstance,VkPhysicalDevice,VkResult>(instance, &vkEnumeratePhysicalDevices);
		if (physicalDevices.empty()) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}
	
	    
	
	
	    for (auto& device : physicalDevices) {
	        if (isDeviceSuitable(device)) {
	            physicalDevice = device;
	            break;
	        }
	    }
	    if (physicalDevice == VK_NULL_HANDLE) {
	        throw std::runtime_error("Found no supported devices.");
	    }
	}
	
	
	
	void HelloTriangleApplication::setupAppInfo(VkApplicationInfo& appInfo)
	{
	    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	    appInfo.pApplicationName = "Hello Intel";
	    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	    appInfo.pEngineName = "No Engine";
	    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	    appInfo.apiVersion = VK_API_VERSION_1_0;
	}
	
	void HelloTriangleApplication::initWindow()
	{
	    glfwInit();
	    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	    
	    window = glfwCreateWindow(WIDTH, HEIGHT, "AMAZING TRIANGLE", nullptr, nullptr);
	
	}
	
	bool HelloTriangleApplication::checkValidationLayerSupport()
	{
	    uint32_t layerCount;
	
	    vkEnumerateInstanceLayerProperties(&layerCount,nullptr);
	    std::vector<VkLayerProperties> availableLayers;
	    availableLayers.resize(layerCount);
	    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
	
	
	    for (const char* layerName : validationLayers) {
	        bool layerFound = false;
	
	        for (const auto& layerProperties : availableLayers) {
	            if (strcmp(layerName, layerProperties.layerName) == 0) {
	                layerFound = true;
	                break;
	            }
	        }
	
	        if (!layerFound) {
	            return false;
	        }
	    }
	    return true;
	
	}
	
	void HelloTriangleApplication::setupDebugMessenger()
	{
	    if (!enableValidationLayers) return;
	    VkDebugUtilsMessengerCreateInfoEXT createInfo;
	    populateDebugMessengerCreateInfo(createInfo);
	
	    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	    createInfo.pfnUserCallback = debugCallback;
	    createInfo.pUserData = nullptr; // Optional
	
	    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
	        throw std::runtime_error("failed to set up debug messenger!");
	    }
	}
	
	void HelloTriangleApplication::populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo)
	{
	    createInfo = {};
	    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	    createInfo.pfnUserCallback = debugCallback;
	}
	
	VkPresentModeKHR HelloTriangleApplication::chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes)
	{
		for (const auto& availablePresentMode : availablePresentModes) {
			{
				if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
					return availablePresentMode;
				}
			}
			return VK_PRESENT_MODE_FIFO_KHR;
		}
	}

	QueueFamilyIndices HelloTriangleApplication::findQueueFamilies(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices;
	    std::vector<VkQueueFamilyProperties> queueFamilies = fillVectorFromFunction(device, &vkGetPhysicalDeviceQueueFamilyProperties);
		int i = 0;
	 
		for (const auto& queueFamily : queueFamilies) {
			if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
				indices.graphicsFamily = i;
			}
			VkBool32 presentSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
			if (presentSupport) {
				indices.presentFamily = i;
			}
	        if (indices.isComplete()) break;
			i++;
		}
		return indices;
	}
	
	bool HelloTriangleApplication::isDeviceSuitable(VkPhysicalDevice device)
	{
		QueueFamilyIndices indices = findQueueFamilies(device);
		bool extensionsSupported = checkDeviceExtensionSupport(device);

		bool swapChainAdequate = false;
		if (extensionsSupported) {
			SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
			swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
		}
		// return true if queue families are found, extensions are supported and swapchain is adequate
		return indices.isComplete() && extensionsSupported && swapChainAdequate;
	}
	
	
	VKAPI_ATTR VkBool32 VKAPI_CALL HelloTriangleApplication::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
	{
	    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
	
	    return VK_FALSE;
	}
	
	void HelloTriangleApplication::cleanup()
	{
	    if (enableValidationLayers) {
	        DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	    }
	    vkDestroySurfaceKHR(instance, surface, nullptr);
	    vkDestroyInstance(instance, nullptr);
	    vkDestroyDevice(device,nullptr);
	    glfwDestroyWindow(window);
	    glfwTerminate();
	}

	void HelloTriangleApplication::createSwapChain()
	{
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice);
		
		VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
		VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
		VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
		
		uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1; // the 1 just prevents the pipeline from being blocked while waiting ig
		if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
			imageCount = swapChainSupport.capabilities.maxImageCount;
		}
		
		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = surface;
		createInfo.minImageCount = imageCount;
		createInfo.imageFormat = surfaceFormat.format;
		createInfo.imageColorSpace = surfaceFormat.colorSpace;
		createInfo.imageExtent = extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		
		QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
		uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
		
		// If we have set up different queues for graphics and presentation, we need to set up a queue family ownership transfer
		if (indices.graphicsFamily != indices.presentFamily) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2; // number of queue families
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			createInfo.queueFamilyIndexCount = 0; // pretty odd if you ask me
			createInfo.pQueueFamilyIndices = nullptr;
		}
		createInfo.preTransform = swapChainSupport.capabilities.currentTransform; 
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = VK_NULL_HANDLE;
		
		vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain);

		
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
		swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
		
		swapChainImageFormat = surfaceFormat.format;
		swapChainExtent = extent;
	}

}
