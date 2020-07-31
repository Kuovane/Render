#include <stdio.h>
#include "TRWindow.h"
#include <windows.h>
#include "Utils.h"
#include "render/TRRender.h"

  struct _vertiesType
{
	float x, y, z,u,v;
};


static const struct _vertiesType vertices[] = {
	{-0.5f, -0.5f, 0.0f, 0.0,0.0 },
	{0.5f, -0.5f, 0.0f,  0.0,1.0},
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
    

    GLuint vpos_location = glGetAttribLocation(programId, "vPos");
    GLuint vtex_location = glGetAttribLocation(programId, "vTex");


	GLuint vertexBufferId;
	GLuint vertexArrayId;
	glGenBuffers(1, &vertexBufferId);
	glGenVertexArrays(1,&vertexArrayId);

	glBindVertexArray(vertexArrayId);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)0);
    glVertexAttribPointer(vtex_location, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (void*)12);
	glEnableVertexAttribArray(0);


	int width, height;
	glfwGetFramebufferSize(pWindow, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


    s_textureId =  Utils::createEmptyTexture(width,height,GL_RGBA);
   glBindTexture(GL_TEXTURE_2D,s_textureId);
  

    auto pTRender=new TRRender(width,height,4);

    glUseProgram(programId);


    
 
    //memset()

    while (!glfwWindowShouldClose(pWindow))
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        glBindVertexArray(vertexArrayId);
	    pTRender->drawPoint(100,100,100);

        updateWithData(pTRender->getScreenBuffer(),0,0,width,height);

		glDrawArrays(GL_TRIANGLES, 0, 6);

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
