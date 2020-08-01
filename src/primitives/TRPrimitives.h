#pragma once

struct TRPoint{
public:
	float x;
	float y;
	//float z;
};


struct TRLine{
public:
	TRPoint from;
	TRPoint to;
	float getK();
	float getB();
	void getKAndB(float &k,float &b);
};


struct TRTriange {
public:
	TRPoint a;
	TRPoint b;
	TRPoint c;
};