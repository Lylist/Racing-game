#pragma once
#include "OurMath.h"
class Wheel
{
public:
	Wheel();
	~Wheel();
	CVector pos, dir;	//λ�úͷ���
	float speed;		//�ٶ�
	void Draw();
};

