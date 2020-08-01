#include <stdio.h>
#include "TRWindow.h"
#include <windows.h>
#include "Utils.h"
#include "render/TRRender.h"
#include "primitives/TRPrimitives.h"

  struct _vertiesType
{
	float x, y, z,u,v;
};

#if defined( _DEBUG ) || defined( DEBUG ) || defined (__DEBUG__)
#   ifndef DEBUG
#       define DEBUG
#   endif
#endif

#ifdef DEBUG
#define CHECK_GL_ERROR_DEBUG() { GLenum __error = glGetError(); if(__error) printf("OpenGL error 0x%04X in %s %d\n", __error, __FUNCTION__, __LINE__); }
#else
#define CHECK_GL_ERROR_DEBUG()
#endif

static const struct _vertiesType vertices[] = {
	{-0.5f, -0.5f, 0.0f, 0.0,0.0 },
	{0.5f, -0.5f, 0.0f,  1.0,0.0},
	{0.5f,  0.5f, 0.0f, 1.0,1.0},
    {0.5f,  0.5f, 0.0f, 1.0,1.0},
	{-0.5f, 0.5f, 0.0f, 0.0,1.0 },
	{-0.5f,  -0.5f, 0.0f,0.0,0.0 },
};

unsigned int s_textureId;
bool updateWithData(const void *data,int offsetX,int offsetY,int width,int height)
{
    if (s_textureId)
    {
       glBindTexture(GL_TEXTURE_2D,s_textureId);
       
        glTexSubImage2D(GL_TEXTURE_2D,0,offsetX,offsetY,width,height,GL_RGBA,GL_UNSIGNED_BYTE,data);

        return true;
    }
    return false;
}

int main()
{
    auto pWindow = TRWindow::createWindow();
    GLuint programId = Utils::createGLProgram("../res/shaders/texture.vert", "../res/shaders/texture.frag");
	//GLuint s_textureId = Utils::LoadGLTextures("../res/awesomeface.png", GL_RGBA);

    GLuint vpos_location = glGetAttribLocation(programId, "vPos");
    GLuint vtex_location = glGetAttribLocation(programId, "vTex");
	GLuint texutre_location = glGetUniformLocation(programId, "texture");

	CHECK_GL_ERROR_DEBUG()
	GLuint vertexBufferId;
	GLuint vertexArrayId;
	glGenBuffers(1, &vertexBufferId);
	glGenVertexArrays(1,&vertexArrayId);

	glBindVertexArray(vertexArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
    glVertexAttribPointer(vtex_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)12);
	glEnableVertexAttribArray(vpos_location);
	glEnableVertexAttribArray(vtex_location);

	CHECK_GL_ERROR_DEBUG()
	int width, height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


    s_textureId =  Utils::createEmptyTexture(width,height,GL_RGBA);
   glBindTexture(GL_TEXTURE_2D,s_textureId);
  

    auto pTRender=new TRRender(width,height,4);

    glUseProgram(programId);

	glUniform1i(texutre_location, 0);
	CHECK_GL_ERROR_DEBUG()

		//memset()
		TRPoint s[] = { 300,200, 500,100, 400,300 , 520,20,600,20,420,0 };
		//TRPoint s[] = {  520,10,520,20,420,50 };


    while (!glfwWindowShouldClose(pWindow))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


        glBindVertexArray(vertexArrayId);
	
		float pre = glfwGetTime();
		pTRender->drawPoint(100,100,100);
		pTRender->drawLine(250, 200, 300, 150, 2);

		for (int i = 0; i < 1000; i++)
		{
			pTRender->drawTriangle((float*)s, sizeof(s) / 24, 0);
		}
		
		
		float cur = glfwGetTime();
		printf("time = %f\n", cur - pre);
        updateWithData(pTRender->getScreenBuffer(),0,0,width,height);
		
		CHECK_GL_ERROR_DEBUG()
		glDrawArrays(GL_TRIANGLES, 0, 6);
		CHECK_GL_ERROR_DEBUG()
        glfwSwapBuffers(pWindow);
        glfwPollEvents();
        Sleep(42);
    }

    delete pTRender;
    glfwDestroyWindow(pWindow);
    glfwTerminate();
    exit(EXIT_SUCCESS);
    return 0;
}
