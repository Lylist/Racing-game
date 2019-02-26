#pragma once
#include "OurMath.h"

class CubeBoundingVolume
{
public:
	CVector pos;	//立方体中心
	CVector dir;	//包围盒方向，指向length方向，不考虑三维，所以heigth方向恒指向y轴方向
	float length, width, heigth; //长宽高
	CVector point_pos[8];		//八个顶点位置，可以自动计算出来
	CubeBoundingVolume();
	CubeBoundingVolume(CVector pos, float length, float width, float heigth, CVector dir);  //长宽高分别对应x，z，y轴上的边

	void setpos(CVector pos, CVector dir);
	bool OverlapTest(CubeBoundingVolume CBV);   //重叠检测
};

