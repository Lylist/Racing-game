#pragma once
#include "OurMath.h"
class SphereBoundingVolume
{
public:
	CVector pos;	//球心
	float radius;   //半径
	SphereBoundingVolume();
	SphereBoundingVolume(CVector pos, float r);

	void setpos(CVector pos);
	bool OverlapTest(SphereBoundingVolume SBV);   //重叠检测,重叠返回True，否则返回False

};

