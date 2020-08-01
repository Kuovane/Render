#include "TRWindow.h"


static void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}


 GLFWwindow* TRWindow::createWindow(void* keyCallBack)
 {
	 GLFWwindow* window;
	 glfwSetErrorCallback(error_callback);
	 if (!glfwInit())
		 exit(EXIT_FAILURE);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	 glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// glfwWindowHint(GLFW_SAMPLES, 4);
#ifdef __APPLE__
	 glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	 window = glfwCreateWindow(800, 640, "Render", NULL, NULL);
	 if (!window)
	 {
		 glfwTerminate();
		 exit(EXIT_FAILURE);
	 }
	 if (keyCallBack)
	 {
		 glfwSetKeyCallback(window, (GLFWkeyfun)keyCallBack);
	 }
	 else
	 {
		 glfwSetKeyCallback(window, key_callback);
	 }
	 
	 glfwMakeContextCurrent(window);
	 gladLoadGL(glfwGetProcAddress);
	 glfwSwapInterval(1);

	 return window;
 }
