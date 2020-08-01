
#include "TRPrimitives.h"


float TRLine::getK()
{
	float dx = to.x - from.x;
	if (dx != 0.0)
	{
		float k = (to.y - from.y) / dx;
		return k;
	}
	else
	{
		return 0;
	}
	
}

float TRLine::getB()
{
	float b = from.y - getK()* from.x;
	return b;
}

void TRLine::getKAndB(float &k, float &b)
{
	k = getK();
	b = from.y - k* from.x;
}