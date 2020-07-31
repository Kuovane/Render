
#include "TRRender.h"
#include <stdlib.h>
#include <string>

TRRender::TRRender(unsigned int width,unsigned int height,unsigned int format)
:m_pScreenBuffer(nullptr)
{
    m_width = width;
    m_height = height;
    m_format = format;
    m_pixelCount = 4;
    genScreenBuffer(m_width,m_height,m_format);
}

TRRender::~TRRender()
{
     if(m_pScreenBuffer)
    {
        free(m_pScreenBuffer);
        m_pScreenBuffer = nullptr;
    }
}

void TRRender::genScreenBuffer(unsigned int width, unsigned int height, unsigned int format)
{
    if(!m_pScreenBuffer)
    {
        m_pScreenBuffer = (unsigned char*)malloc(width*height*m_pixelCount);
        memset(m_pScreenBuffer,100,width*height*m_pixelCount);
    }
    
}

unsigned char* TRRender::getPositionPoint(int x,int y)
{
    int index = (y*m_width+x)*m_pixelCount;
    if(index <0 || index >= m_width*m_height*m_pixelCount)
    {
        return nullptr;
    }
    return &m_pScreenBuffer[index];
}

void TRRender::drawPoint(float x, float y, float size)
{

 /*for(int i = 0 ; i < m_height; i++ )
    {
        for(int j = 0 ; j < m_width; j++ )
        {
            int index = (i*m_width+j)*m_pixelCount;
            m_pScreenBuffer[index] = 255;
            m_pScreenBuffer[index+1] = 0;
            m_pScreenBuffer[index+2] = 0;
            m_pScreenBuffer[index+3] = 255;
        }
    }*/


    //memset(m_pScreenBuffer,rand()%255,m_width*m_height*m_pixelCount);
    int mid = size/2;
    int len = size;

    for(int i = -mid ; i < len; i++ )
    {
        for(int j = -mid ; j < len; j++ )
        {
            unsigned char* p = getPositionPoint(x+i,y+j);
            if(p)
            {
                p[0] = 255;
                p[1] = 0;
                p[2] = 0;
                p[3] = 255;
            }
            
        }

    }
   
}

void TRRender::drawLine(float sx, float sy, float tx, float ty, float size)
{
}

void TRRender::drawTriangle(float sx, float sy, float tx, float ty, float size)
{
}