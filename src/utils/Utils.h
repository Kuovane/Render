
#pragma once
#include "glad/gl.h"
#include "glfw3/glfw3.h"
//#include "glfw3/glfw3native.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>

class  Utils
{
public:
    static unsigned int createEmptyTexture(unsigned int width,unsigned int height, unsigned int format);
	static int LoadGLTextures(std::string sFilePath, unsigned int type);
	static int LoadGLTextures(unsigned char *data, int width, int height, int nrChannels);
	static unsigned char* loadPng(const char* fileName, unsigned long &nSize, int &width, int &height);

	static GLuint createGLProgram(char* vertFile, char* fragFile);
	static long long getTimeInMilliseconds();

};
