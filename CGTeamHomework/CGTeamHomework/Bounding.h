#include "OurMath.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <cstdlib>
//球形包围盒
class SphereBoundingVolume1
{
public:
	CVector pos;	//球心
	float radius;   //半径
	SphereBoundingVolume();
	SphereBoundingVolume(CVector pos,float r);

	void setpos(CVector pos);
	bool OverlapTest(SphereBoundingVolume SBV);   //重叠检测,重叠返回True，否则返回False
};


//方形包围盒
class CubeBoundingVolume1
{
public:
	CVector pos;	//立方体中心
	CVector dir;	//包围盒方向，指向length方向，不考虑三维，所以heigth方向恒指向y轴方向
	float length,width,heigth; //长宽高
	CVector point_pos[8];		//八个顶点位置，可以自动计算出来
	CubeBoundingVolume();
	CubeBoundingVolume(CVector pos,float length,float width,float heigth,CVector dir);  //长宽高分别对应x，z，y轴上的边

	void setpos(CVector pos,CVector dir);
	bool OverlapTest(CubeBoundingVolume CBV);   //重叠检测
};


