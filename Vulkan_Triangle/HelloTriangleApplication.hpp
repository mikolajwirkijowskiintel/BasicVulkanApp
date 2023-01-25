#pragma once
#include <vector>
#include <optional>
#include <functional>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace TriangleApp {
#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 640;

    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        /// <summary>
        /// Checks if all members of the struct are initialized
        /// </summary>
        /// <returns></returns>
        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    class HelloTriangleApplication {
    public:

        void run();



    private:
        // static functions
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData);

        static void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

        static VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);

        // setup
        void initVulkan();

        void initWindow();

        void createSwapChain();
        
        void createImageViews();
        
        void createLogicalDevice();

        void createInstance();

        void createSurface();

        void pickPhysicalDevice();

        void setupAppInfo(VkApplicationInfo& appInfo);

        void setupDebugMessenger();

        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);

        void mainLoop();

        // utility

		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        bool checkDeviceExtensionSupport(VkPhysicalDevice device);

        bool checkGLFWLayersSupport();

        std::vector<const char*> getRequiredExtensions();

        bool checkValidationLayerSupport();

        template <class Info, class Value, class FReturnType>
        std::vector<Value> fillVectorFromFunction(Info info, FReturnType(*func)(Info, uint32_t*, Value*));

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        bool isDeviceSuitable(VkPhysicalDevice device);

        void cleanup();

        // Member variables
        
        // Vulkan base
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        
        // Devices
        VkPhysicalDevice physicalDevice;
        VkDevice device;
        
        // Draw
        GLFWwindow* window;
        VkSurfaceKHR surface;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        
		// Swap chain variables
        std::vector<VkImageView> swapChainImageViews;
        VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
    };

    template <class Info, class Value, class FReturnType>
    std::vector<Value> HelloTriangleApplication::fillVectorFromFunction(Info info, FReturnType(*func)(Info, uint32_t*, Value*))
    {
        uint32_t count = 0;
        func(info, &count, nullptr);
        std::vector<Value> resultVector(count);
        func(info, &count, resultVector.data());
        return resultVector;
    }
}