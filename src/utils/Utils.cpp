#include"Utils.h"
#include "io/VxFile.h"
#include "glfw3/glfw3.h"
#include "image/stb_image.h"


typedef struct
{
	const unsigned char * data;
	long size;
	int offset;
}tImageSourceData;

GLuint	s_texture[10];


unsigned int Utils::createEmptyTexture(unsigned int width,unsigned int height, unsigned int format)
{
    unsigned int textureId;
    glGenTextures(1, &textureId); // Create The Texture

	unsigned char *pData = (unsigned char *)malloc(width*height*4);
	memset(pData,255,width*height*4);
	/*for(int i =0 ; i < height; i++)
	{
		for(int j = 0; j<width;j++)
		{
			unsigned char* p = &pData[i*width+j];
			p[0] = 255;
		}
	}*/
    // Typical Texture Generation Using Data From The Bitmap
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	free(pData);
    return textureId;
}


int Utils::LoadGLTextures(std::string sFilePath, unsigned int type)									// Load Bitmaps And Convert To Textures
{
	int Status = false;									// Status Indicator

	unsigned long dataLen = 0;

	std::string sFileName =  sFilePath;//"textures/container2.png";
	//int width, height;
	//auto data = loadPng(sFileName.c_str(), dataLen, width, height);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(sFileName.c_str(), &width, &height, &nrChannels, 0);
	GLuint textureId = 0;
	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (data)
	{

		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;


		glGenTextures(1, &textureId);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);

		//delete[] data;
	}

	stbi_image_free(data);
	return textureId;										// Return The Status
}


int Utils::LoadGLTextures(unsigned char *data,int width,int height,int nrChannels)									// Load Bitmaps And Convert To Textures
{

	GLuint textureId = 0;

	if (data)
	{
		GLenum format;
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;


		glGenTextures(1, &textureId);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}


	return textureId;										// Return The Status
}



 GLuint Utils::createGLProgram(char* vertFile, char* fragFile)
{
	 std::cout << "createGLProgram\n" << std::endl;
	GLuint  vertex_shader, fragment_shader, program;

	unsigned long  nSize = 0;
	std::string sVert;
	std::string sFrag;
	const char*  vertData = (const char*)VxFile::createFileData(vertFile, "r", &nSize);
	sVert.assign(vertData, nSize);
	const char* fragData = (const char*)VxFile::createFileData(fragFile, "r", &nSize);
	sFrag.assign(fragData, nSize);
	delete[]vertData;
	delete[]fragData;


	vertData = sVert.c_str();
	fragData = sFrag.c_str();



	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertData, NULL);
	glCompileShader(vertex_shader);
	
	int  success;
	char infoLog[512];
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragData, NULL);
	glCompileShader(fragment_shader);


	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::fragment::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);


	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::program::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return program;
}


#if VX_TARGET_PLATFORM == VX_PLATFORM_WIN32
#include <Windows.h>
 struct timezone
 {
	 int tz_minuteswest;
	 int tz_dsttime;
 };

 int gettimeofday(struct timeval * val, struct timezone *)
 {
	 if (val)
	 {
		 LARGE_INTEGER liTime, liFreq;
		 QueryPerformanceFrequency(&liFreq);
		 QueryPerformanceCounter(&liTime);
		 val->tv_sec = (long)(liTime.QuadPart / liFreq.QuadPart);
		 val->tv_usec = (long)(liTime.QuadPart * 1000000.0 / liFreq.QuadPart - val->tv_sec * 1000000.0);
	 }
	 return 0;
 }



#endif 

 long long Utils::getTimeInMilliseconds()
 {
	 struct timeval tv;
	 gettimeofday(&tv, nullptr);
	 return (long long)tv.tv_sec * 1000 + tv.tv_usec / 1000;
 }

