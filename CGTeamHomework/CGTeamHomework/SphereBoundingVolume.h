#pragma once
#include "OurMath.h"
class SphereBoundingVolume
{
public:
	CVector pos;	//����
	float radius;   //�뾶
	SphereBoundingVolume();
	SphereBoundingVolume(CVector pos, float r);

	void setpos(CVector pos);
	bool OverlapTest(SphereBoundingVolume SBV);   //�ص����,�ص�����True�����򷵻�False

};

