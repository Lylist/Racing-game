#pragma once
#include "CubeBoundingVolume.h"
#include "SphereBoundingVolume.h"
#include "OurMath.h"

//路段信息，存放这个路段的边界信息
/**
八种路段， type=1,z轴正方向，type=2,z轴负方向，type=3,x轴正方向，type=4,x轴负方向
type=13,正z转正x，type=23,负z转正x，type=14,正z转负x，type=24,负z转负x，
type=31,正x转正z，type=32,正x转负z，type=41,负x转正z，type=42,负x转负z，
**/
class Load
{
public:
	int type;
	float bound_max, bound_min;	//边界值，不同路段边界值含义不一样，有可能表示x轴范围，有可能表z轴方向范围
	float before, back;		//起始和结束值
	Load();
	Load(int _type, float _bound_max, float _bound_min, float _before, float _back);
};

//不同路段拼接起来的完整道路
class Track
{
public:
	Track();
	~Track();
	std::vector<Load> loads;
	void Draw();
};

