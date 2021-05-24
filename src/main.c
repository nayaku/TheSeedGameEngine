#include<GLFW/glfw3.h>

int main()
{
	GLFWwindow* window;
	// 初始化GLFW库
	if (!glfwInit())
		return -1;
	// 创建窗口和OpenGL的内容
	window = glfwCreateWindow(640, 480, "The Seed Game Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// 创建内容
	glfwMakeContextCurrent(window);

	// 主循环
	while (!glfwWindowShouldClose(window))
	{
		// 渲染
		glClear(GL_COLOR_BUFFER_BIT);

		// 交换缓冲
		glfwSwapBuffers(window);

		// 处理事件消息
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}
