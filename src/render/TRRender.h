#pragma once

class TRRender {
public:
    TRRender(unsigned int width,unsigned int height,unsigned int format);
    virtual ~TRRender();
   

    void drawPoint(float x,float y,float size);

    void drawLine(float sx,float sy,float tx,float ty,float size);

    void drawTriangle(float sx,float sy,float tx,float ty,float size);


    unsigned int getWidth(){return m_width;}
    unsigned int getHeight(){return m_height;}
    unsigned int getPixelCount(){return m_pixelCount;}

    unsigned char* getScreenBuffer(){return m_pScreenBuffer;}
protected:
    void genScreenBuffer(unsigned int width,unsigned int height,unsigned int format);
    unsigned char* getPositionPoint(int x,int y);
private:
    unsigned char* m_pScreenBuffer;
    unsigned int m_width;
    unsigned int m_height;
    unsigned int m_format;
    unsigned int m_pixelCount;
};