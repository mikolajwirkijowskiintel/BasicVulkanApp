#pragma once
#include <vector>
#include <optional>
#include <functional>
#include <string>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define ALPHA_BLEND

namespace TriangleApp {


    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };




    

    class HelloTriangleApplication {
    public:

        void run();



    private:
        // static functions

        static std::vector<char> readFile(const std::string& filename);

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

        void createGraphicsPipeline();

        void createSwapChain();
        
        void createImageViews();
        
        void createRenderPass();
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

        VkShaderModule createShaderModule(const std::vector<char>& code);

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

        // Graphics pipeline variables
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;

        // Vulkan base variables
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