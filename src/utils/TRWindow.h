
#pragma once
#include "glad/gl.h"
#include "glfw3/glfw3.h"
//#include "glfw3/glfw3native.h"
#include <stdlib.h>
#include <stdio.h>

class  TRWindow
{
public:
	static GLFWwindow* createWindow(void* keyCallBack = nullptr);

};
