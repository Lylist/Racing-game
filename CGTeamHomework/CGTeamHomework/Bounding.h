#include "OurMath.h"
#include <math.h>
#include <iostream>
#include <GL/glut.h>
#include <algorithm>
#include <cstdlib>
//���ΰ�Χ��
class SphereBoundingVolume1
{
public:
	CVector pos;	//����
	float radius;   //�뾶
	SphereBoundingVolume();
	SphereBoundingVolume(CVector pos,float r);

	void setpos(CVector pos);
	bool OverlapTest(SphereBoundingVolume SBV);   //�ص����,�ص�����True�����򷵻�False
};


//���ΰ�Χ��
class CubeBoundingVolume1
{
public:
	CVector pos;	//����������
	CVector dir;	//��Χ�з���ָ��length���򣬲�������ά������heigth�����ָ��y�᷽��
	float length,width,heigth; //�����
	CVector point_pos[8];		//�˸�����λ�ã������Զ��������
	CubeBoundingVolume();
	CubeBoundingVolume(CVector pos,float length,float width,float heigth,CVector dir);  //����߷ֱ��Ӧx��z��y���ϵı�

	void setpos(CVector pos,CVector dir);
	bool OverlapTest(CubeBoundingVolume CBV);   //�ص����
};


