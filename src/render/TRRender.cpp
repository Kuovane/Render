
#include "TRRender.h"
#include <stdlib.h>
#include <string>

#include <algorithm>

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

float TRRender::fclampX1(float x1)
{
	if (x1 < 0)
	{
		return 0;
	}
	return x1;
}

float TRRender::fclampX2(float x2)
{
	if (x2 > m_width )
	{
		return m_width ;
	}
	return x2;
}

float TRRender::fclampY1(float y1)
{
	if (y1 <0)
	{
		return 0;
	}
	return y1;
}

float TRRender::fclampY2(float y2)
{
	if (y2 > m_height)
	{
		return m_height;
	}
	return y2;
}


void TRRender::drawOnePointNoCheck(float x, float y)
{
	int index = (y*m_width + x)*m_pixelCount;

	unsigned char* p = &m_pScreenBuffer[index];

	p[0] = 255;
	p[1] = 0;
	p[2] = 0;
	p[3] = 255;
}

void TRRender::drawHSegmentNoCheck(int x1, int x2, int y)
{
	swapIfLager(x1, x2);
	x1 = fclampX1(x1);
	x2 = fclampX1(x2 + 1);

	for (int i = x1; i < x2; ++i)
	{
		//drawOnePoint(i, j);
		int index = (y*m_width + i)*m_pixelCount;

		unsigned char* p = &m_pScreenBuffer[index];

		p[0] = 255;
		p[1] = 0;
		p[2] = 0;
		p[3] = 255;
	}
}

void TRRender::drawPoint(float x, float y, float size)
{
    float mid = size*0.5;
    int len = size;

	float t= -mid + x;
	int x1 = fclampX1(t);

	t = -mid + x + len;
	int x2 = fclampX2(t);

	t = -mid + y;
	int y1 = fclampY1(t);

	t = -mid + y + len;
	int y2 = fclampY2(t);


    for(int i = x1; i < x2; ++i )
    {
        for(int j = y1 ; j < y2; ++j )
        {
			drawOnePointNoCheck(i,j);
            
        }

    }
   
}

void TRRender::drawOnePoint(float x, float y)
{
	unsigned char* p = getPositionPoint(x , y);
	if (p)
	{
		p[0] = 255;
		p[1] = 0;
		p[2] = 0;
		p[3] = 255;
	}
}

void TRRender::drawHPoint(float x, float y, float size)
{
	int mid = size / 2;
	int len = size;

	for (int i = -mid; i < len; ++i)
	{
			unsigned char* p = getPositionPoint(x + i, y);
			if (p)
			{
				p[0] = 255;
				p[1] = 0;
				p[2] = 0;
				p[3] = 255;
			}
	}
}

void TRRender::drawLine(float sx, float sy, float tx, float ty, float size)
{
	if (tx != sx)
	{
		float k = (ty - sy) / (tx - sx);
		float b = sy - k * sx;
		if (sx < tx)
		{
			for (int i = sx; i <= tx; ++i)
			{
				int y = i * k + b;
				drawHPoint(i, y, size);
			}
		}
		else
		{
			for (int i = sx; i >= tx; --i)
			{
				int y = i * k + b;
				drawHPoint(i, y, size);
			}
		}
		
	}
	else
	{
		float y0 = sy;
		float y1 = ty;
		if (sy > ty)
		{
			y0 = ty;
			y1 = sy;
		}
		for (int y= y0; y <= y1; y++)
		{
			drawHPoint(sx, y, size);
		}
	}
	
}

bool comparePoint(TRPoint&a, TRPoint&b)
{
	return a.y > b.y;
}


void TRRender::swapIfLager(int &x1, int&x2)
{
	if (x1 > x2)
	{
		int t = x1;
		x1 = x2;
		x2 = t;
	}
}

void TRRender::drawHTriangle(float *p, int fillStyle)
{
	TRPoint tp[3];
	memcpy(&tp[0],p,24);

	std::sort(&tp[0],&tp[3], comparePoint);

	TRLine sLine[3] = { tp[1],tp[0],tp[1],tp[2],tp[0],tp[2]};
	float k[3] = { 0 }, b[3] = { 0 }, ik[3] = {0};
	sLine[0].getKAndB(k[0], b[0]);
	sLine[1].getKAndB(k[1], b[1]);
	sLine[2].getKAndB(k[2], b[2]);
	for (int i = 0; i < 3; ++i)
	{
		if (k[i] != 0)
		{
			ik[i] = 1 / k[i];
		}
	}
	
	if (tp[0].x == tp[1].x && tp[1].x == tp[2].x)
	{
		drawLine(tp[0].x, tp[0].y, tp[1].x, tp[2].y,1);
	}
	else
	{

		float b1 = b[0], b2 = b[2];
		float ik1 = ik[0], ik2 = ik[2];
		if (tp[1].x > tp[0].x)
		{
			b1 = b[2];
			ik1 = ik[2];

			b2 = b[0];
			ik2 = ik[0];
		}


		if (k[0] != 0 && k[2] != 0  )
		{
			float y1 = fclampY1(tp[1].y);
			float y2 = fclampY2(tp[0].y+1);

			for (int j = y1; j < y2; ++j)
			{
				float x1 = (j - b1) * ik1;
				float x2 = (j - b2) * ik2;

				drawHSegmentNoCheck(x1, x2, j);
			}
		}
		else if(tp[0].x == tp[1].x)
		{
			float y1 = fclampY1(tp[1].y);
			float y2 = fclampY2(tp[0].y + 1);

			for (int j = y1; j <y2; ++j)
			{
				float x1 = tp[0].x;
				float x2 = (j - b[2]) * ik[2];
				drawHSegmentNoCheck(x1, x2, j);
			}
			
		}
		else if (tp[0].x == tp[2].x)
		{
			float y1 = fclampY1(tp[1].y);
			float y2 = fclampY2(tp[0].y + 1);
			for (int j = y1; j < y2; ++j)
			{
				float x1 = (j - b[0]) * ik[0];
				float x2 = tp[0].x;
				drawHSegmentNoCheck(x1, x2, j);
			}

		}



		if (k[1] != 0 && k[2] != 0)
		{
			float y1 = fclampY1(tp[2].y-1);
			float y2 = fclampY2(tp[1].y + 1);

			for (int j = y1; j < y2; ++j)
			{
				float x1 = (j - b[1]) * ik[1];
				float x2 = (j - b[2]) * ik[2];
				drawHSegmentNoCheck(x1, x2, j);
			}
		}
		else if (tp[2].x == tp[1].x)
		{
			float y1 = fclampY1(tp[2].y-1);
			float y2 = fclampY2(tp[1].y + 1);
			float x1 = tp[2].x;

			for (int j = y1; j < y2; ++j)
			{
				
				float x2 = (j - b[2]) * ik[2];
				drawHSegmentNoCheck(x1, x2, j);
			}

		}
		else if (tp[0].x == tp[2].x)
		{
			float y1 = fclampY1(tp[2].y-1);
			float y2 = fclampY2(tp[1].y + 1);
			float x2 = tp[2].x;
			for (int j = y1; j < y2; ++j)
			{
				float x1 = (j - b[0]) * ik[0];
				
				drawHSegmentNoCheck(x1, x2, j);
			}

		}

	}



}

void TRRender::drawTriangle(float *p, int triangeCount, int fillStyle)
{
	for (int i = 0; i < triangeCount; i = i + 1)
	{

		drawHTriangle(p+i*6, fillStyle);
	}
	
}

bool TRRender::getLinesIntersectPoint(TRLine &a, TRLine &b, TRPoint&out)
{
	return false;
}
