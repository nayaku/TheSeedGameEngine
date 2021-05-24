# CMakeList.txt: TheSeedGameEngine 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("TheSeedGameEngine"
        VERSION 0.0.1
        DESCRIPTION "A 2D multi-platform game engine"
        HOMEPAGE_URL "https://github.com/nayaku/TheSeedGameEngine"
        LANGUAGES C CXX)

# 添加glwf库
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw-3.3.4)
# 找到OpenGL
find_package(Vulkan REQUIRED)
if (NOT Vulkan_FOUND)
    MESSAGE("Cannot find Vulkan!")
endif ()

# 添加文件
add_library(TheSeedGameEngineLib
        STATIC
        src/VulkanManager.c)
target_link_libraries(TheSeedGameEngineLib
        glfw
        Vulkan::Vulkan)

add_executable(TheSeedGameEngine src/main.c)
target_link_libraries(TheSeedGameEngine
        TheSeedGameEngineLib)
