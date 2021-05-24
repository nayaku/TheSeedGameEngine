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
find_package(OpenGL REQUIRED)


# 将源代码添加到此项目的可执行文件。
add_executable (TheSeedGameEngine
        src/main.c)
target_link_libraries(TheSeedGameEngine 
        glfw
        OpenGL::GL)
# TODO: 如有需要，请添加测试并安装目标。
