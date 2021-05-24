#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
/*!
 * 初始化窗口
 * @param width
 * @param height
 * @param title
 */
void InitWindow(int width,int height,const char* title);
/*!
 * 判断窗口是否需要关闭
 * @return
 */
int WindowShouldClose();
/*!
 * 关闭窗口
 */
void CloseWindow();