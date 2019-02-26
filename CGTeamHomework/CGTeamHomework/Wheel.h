#pragma once
#include "OurMath.h"
class Wheel
{
public:
	Wheel();
	~Wheel();
	CVector pos, dir;	//位置和方向
	float speed;		//速度
	void Draw();
};

