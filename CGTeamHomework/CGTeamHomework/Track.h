#pragma once
#include "CubeBoundingVolume.h"
#include "SphereBoundingVolume.h"
#include "OurMath.h"

//·����Ϣ��������·�εı߽���Ϣ
/**
����·�Σ� type=1,z��������type=2,z�Ḻ����type=3,x��������type=4,x�Ḻ����
type=13,��zת��x��type=23,��zת��x��type=14,��zת��x��type=24,��zת��x��
type=31,��xת��z��type=32,��xת��z��type=41,��xת��z��type=42,��xת��z��
**/
class Load
{
public:
	int type;
	float bound_max, bound_min;	//�߽�ֵ����ͬ·�α߽�ֵ���岻һ�����п��ܱ�ʾx�᷶Χ���п��ܱ�z�᷽��Χ
	float before, back;		//��ʼ�ͽ���ֵ
	Load();
	Load(int _type, float _bound_max, float _bound_min, float _before, float _back);
};

//��ͬ·��ƴ��������������·
class Track
{
public:
	Track();
	~Track();
	std::vector<Load> loads;
	void Draw();
};

