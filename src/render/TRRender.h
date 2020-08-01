#pragma once
#include "primitives/TRPrimitives.h"

class TRRender {
public:
    TRRender(unsigned int width,unsigned int height,unsigned int format);
    virtual ~TRRender();
   

    void drawPoint(float x,float y,float size);
	void drawOnePoint(float x, float y);
	void drawHPoint(float x, float y, float size);
    void drawLine(float sx,float sy,float tx,float ty,float size);

	void swapIfLager(int &x1, int &x2);
	void drawHTriangle(float *sx, int fillStyle);
    void drawTriangle(float *sx,int pointCount, int fillStyle);

	bool getLinesIntersectPoint(TRLine&a, TRLine&b, TRPoint&out);
    unsigned int getWidth(){return m_width;}
    unsigned int getHeight(){return m_height;}
    unsigned int getPixelCount(){return m_pixelCount;}

    unsigned char* getScreenBuffer(){return m_pScreenBuffer;}
protected:
    void genScreenBuffer(unsigned int width,unsigned int height,unsigned int format);
    unsigned char* getPositionPoint(int x,int y);
	void drawOnePointNoCheck(float x, float y);
	void drawHSegmentNoCheck(int x1, int x2, int y);
	float fclampX1(float x1);
	float fclampX2(float x2);
	float fclampY1(float y1);
	float fclampY2(float y2);
private:
    unsigned char* m_pScreenBuffer;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_format;
    unsigned int m_pixelCount;
};