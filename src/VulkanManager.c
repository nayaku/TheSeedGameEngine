#include "VulkanManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// GLFW窗口
static GLFWwindow* window;
// Vulkan实例
static VkInstance instance;
// 物理设备
static VkPhysicalDevice physicalDevice;
// 使用的队列家族编号
static uint32_t queueFamilyIndex = -1;
// 逻辑设备
static VkDevice logicalDevice;

/* 初始化实例 */
static void InitInstance(const char* title)
{
    // 应用信息
    VkApplicationInfo appInfo = {
        .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
        .pApplicationName = title,
        .applicationVersion = VK_MAKE_VERSION(1, 0, 0),
        .pEngineName = "The Seed Game Engine",
        .engineVersion = VK_MAKE_VERSION(1, 0, 0),
        .apiVersion = VK_API_VERSION_1_0,
    };

    // 使用glfw扩展
    unsigned int glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // 实例信息
    VkInstanceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
        .pApplicationInfo = &appInfo,
        .enabledExtensionCount = glfwExtensionCount,
        .ppEnabledExtensionNames = glfwExtensions,
        .enabledLayerCount = 0
    };

    // 创建实例
    VkResult result = vkCreateInstance(&createInfo, NULL, &instance);
    if (result == VK_SUCCESS)
    {
        printf("Vulkan instance created success.\n");
    }
    else
    {
        printf("Vulkan instance created failed.\n");
        abort();
    }
}

/* 销毁实例 */
static void DestroyInstance()
{
    vkDestroyInstance(instance, NULL);
    printf("Vulkan instance destroyed.");
    glfwDestroyWindow(window);
}

/* 获取物理设备 */
static void PickPhysicalDevice()
{
    uint32_t deviceCount;
    VkResult result = vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);
    assert(result == VK_SUCCESS);
    if (deviceCount == 0)
    {
        printf("Failed to find GPUs with Vulkan support!");
        abort();
    }
    VkPhysicalDevice* devices = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    // 选择可用的物理设备
    physicalDevice = devices[0];//没啥特殊要求，直接选择第一个设备即可
    free(devices);
    // 输出选择的物理设备信息
    VkPhysicalDeviceProperties deviceProperties;
    vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
    printf("Current Physical Info:ID:  %I32u\nName:  %s\nVulkan Version:  %I32u\n",
        deviceProperties.deviceID,
        deviceProperties.deviceName,
        deviceProperties.apiVersion);


    // 获取设备队列族的数量
    uint32_t queueFamilyCount;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);
    VkQueueFamilyProperties
        * queueFamilyProperties = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);

    // 遍历队列族
    for (uint32_t i = 0; i < queueFamilyCount; i++)
    {
        // 支持图形工作
        if (queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            queueFamilyIndex = i;
            break;
        }
    }
    free(queueFamilyProperties);
}

/* 创建逻辑设备 */
static void CreateLogicalDevice()
{
    // 队列优先级
    float queuePriority = 1.0f;
    VkDeviceQueueCreateInfo queueCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = queueFamilyIndex,
        .queueCount = 1,// 只需要创建一个队列
        .pQueuePriorities = &queuePriority
    };
    const char* deviceExtensionNames[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
    VkDeviceCreateInfo createInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .pQueueCreateInfos = &queueCreateInfo,
        .queueCreateInfoCount = 1,
        .ppEnabledExtensionNames = deviceExtensionNames,
        .enabledLayerCount = 0 // 先不开启验证层
    };
    VkResult result = vkCreateDevice(physicalDevice, &createInfo, NULL, &logicalDevice);
}

void InitWindow(int width, int height, const char* title)
{
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    window = glfwCreateWindow(width, height, title, NULL, NULL);

    InitInstance(title);
    PickPhysicalDevice();
}

int WindowShouldClose()
{
    int flag = glfwWindowShouldClose(window);
    if (!flag)
    {
        glfwPollEvents();
    }
    return flag;
}
void CloseWindow()
{
    DestroyInstance();
    glfwTerminate();
}
