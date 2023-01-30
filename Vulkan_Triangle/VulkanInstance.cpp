#include "VulkanInstance.h"

#include <iostream>
#include <stdexcept>



VulkanInstance::VulkanInstance(Window* window)
  : validationLayers({ "VK_LAYER_KHRONOS_validation" })
  , window(window)
{
    createInstance();
    createDebugMessenger();
    createWindowSurface();

}

VulkanInstance::~VulkanInstance()
{
	if (enableValidationLayers) {
		DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
	}
    vkDestroySurfaceKHR(instance, windowSurface, nullptr);
    vkDestroyInstance(instance, nullptr);
}

void VulkanInstance::createInstance()
{
	bool bRequestedLayersUnavailable =
		enableValidationLayers && !bInstanceValidationLayersSupported();
	if (bRequestedLayersUnavailable) {
		throw std::runtime_error("Requested validation layers not available.");
	}

	VkApplicationInfo appInfo;
	populateAppInfo(appInfo);

	VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
	populateDebugMessengerCreateInfo(debugCreateInfo);

	VkInstance retrievedInstance;
	VkInstanceCreateInfo createInfo;
	populateInstanceCreateInfo(createInfo, appInfo, debugCreateInfo);
	VkResult instanceCreationResult =
		vkCreateInstance(&createInfo, nullptr, &retrievedInstance);

	if (instanceCreationResult != VK_SUCCESS) {
		throw std::runtime_error("failed to create instance!");
	}

	instance = retrievedInstance;
}

void VulkanInstance::createDebugMessenger()
{
    if (!enableValidationLayers) return;
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
    populateDebugMessengerCreateInfo(debugCreateInfo);
	if (CreateDebugUtilsMessengerEXT(
		instance, &debugCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
		throw std::runtime_error("failed to set up debug messenger!");
	}
}

void
VulkanInstance::populateAppInfo(VkApplicationInfo& appInfo)
{
  appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Hello Intel";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;
}

void
VulkanInstance::populateInstanceCreateInfo(
  VkInstanceCreateInfo& createInfo,
  VkApplicationInfo& appInfo,
  VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo)
{
  createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

  if (enableValidationLayers) {
    // Populate enabled layers fields with validation layers
    createInfo.enabledLayerCount =
      static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();

    // Populate debug messenger create info, creation handled externally
    createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
  } else {
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
  }

  createInfo.pApplicationInfo = &appInfo;
  auto req_extensions = window->getVulkanExtensionsRequiredByWindow();
  if (enableValidationLayers)
    req_extensions->push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
  createInfo.enabledExtensionCount =
    static_cast<uint32_t>(req_extensions->size());
  createInfo.ppEnabledExtensionNames = req_extensions->data();
}

void
VulkanInstance::populateDebugMessengerCreateInfo(
  VkDebugUtilsMessengerCreateInfoEXT& debugCreateInfo)
{
  debugCreateInfo = {};
  debugCreateInfo.sType =
    VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
  debugCreateInfo.messageSeverity =
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
    VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;

  debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;

  debugCreateInfo.pfnUserCallback = debugCallback;
}

bool
VulkanInstance::bInstanceValidationLayersSupported()
{
  uint32_t layerCount;
  vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
  std::vector<VkLayerProperties> availableLayersProperties;
  availableLayersProperties.resize(layerCount);
  vkEnumerateInstanceLayerProperties(&layerCount,
                                     availableLayersProperties.data());

  // If each of validation layers is contained in available layers, only then
  // validation is supported
  for (const char* layerName : validationLayers) {
    bool layerFound = false;

    for (const auto& layerProperties : availableLayersProperties) {
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


void
VulkanInstance::DestroyDebugUtilsMessengerEXT(
  VkInstance instance,
  VkDebugUtilsMessengerEXT debugMessenger,
  const VkAllocationCallbacks* pAllocator)
{
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance, "vkDestroyDebugUtilsMessengerEXT");
  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

VkResult
VulkanInstance::CreateDebugUtilsMessengerEXT(
  VkInstance instance,
  const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
  const VkAllocationCallbacks* pAllocator,
  VkDebugUtilsMessengerEXT* pDebugMessenger)
{
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(
    instance, "vkCreateDebugUtilsMessengerEXT");

  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  }
  return VK_ERROR_EXTENSION_NOT_PRESENT;
}

void VulkanInstance::createWindowSurface()
{
	if (glfwCreateWindowSurface(instance, window->getWindow(), nullptr, &windowSurface) != VK_SUCCESS) {
		throw std::runtime_error("failed to create window surface!");
	}
}

VKAPI_ATTR VkBool32 VKAPI_CALL
VulkanInstance::debugCallback(
  VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
  VkDebugUtilsMessageTypeFlagsEXT messageType,
  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
  void* pUserData)
{
  std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

  return VK_FALSE;
}
