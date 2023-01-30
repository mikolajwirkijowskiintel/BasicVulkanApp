#pragma once
#include "Window.h"

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class VulkanInstance {
public:

  VulkanInstance(Window *window);
  ~VulkanInstance();

  // Getters
  VkInstance getInstance() { return instance; }
  VkSurfaceKHR getWindowSurface() { return windowSurface; }
  Window* getWindow() { return window; }

  const std::vector<const char*> getValidationLayers() { return validationLayers; }
private:
  // Object creation
  static VkResult CreateDebugUtilsMessengerEXT(
      VkInstance instance,
      const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
      const VkAllocationCallbacks *pAllocator,
      VkDebugUtilsMessengerEXT *pDebugMessenger);

  void createWindowSurface();
  void createInstance();
  void createDebugMessenger();

  // Struct population
  void populateAppInfo(VkApplicationInfo &appInfo);
  void populateInstanceCreateInfo(
      VkInstanceCreateInfo &createInfo, VkApplicationInfo &appInfo,
      VkDebugUtilsMessengerCreateInfoEXT &debugCreateInfo);
  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &debugCreateInfo);

  // Checks
  bool bInstanceValidationLayersSupported();

  // Object destruction
  static void
  DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                VkDebugUtilsMessengerEXT debugMessenger,
                                const VkAllocationCallbacks *pAllocator);

  // Vulkan Instance class member variables
  Window *window;
  VkSurfaceKHR windowSurface;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  const std::vector<const char *> validationLayers;

  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData);
};
