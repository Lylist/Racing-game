#pragma once
#include "OurMath.h"

class CubeBoundingVolume
{
public:
	CVector pos;	//����������
	CVector dir;	//��Χ�з���ָ��length���򣬲�������ά������heigth�����ָ��y�᷽��
	float length, width, heigth; //�����
	CVector point_pos[8];		//�˸�����λ�ã������Զ��������
	CubeBoundingVolume();
	CubeBoundingVolume(CVector pos, float length, float width, float heigth, CVector dir);  //����߷ֱ��Ӧx��z��y���ϵı�

	void setpos(CVector pos, CVector dir);
	bool OverlapTest(CubeBoundingVolume CBV);   //�ص����
};

