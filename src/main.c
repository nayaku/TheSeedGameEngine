#include<GLFW/glfw3.h>

int main()
{
	GLFWwindow* window;
	// ��ʼ��GLFW��
	if (!glfwInit())
		return -1;
	// �������ں�OpenGL������
	window = glfwCreateWindow(640, 480, "The Seed Game Engine", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// ��������
	glfwMakeContextCurrent(window);

	// ��ѭ��
	while (!glfwWindowShouldClose(window))
	{
		// ��Ⱦ
		glClear(GL_COLOR_BUFFER_BIT);

		// ��������
		glfwSwapBuffers(window);

		// �����¼���Ϣ
		glfwPollEvents();
	}

	glfwTerminate();
	
	return 0;
}
