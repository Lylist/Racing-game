#include "SphereBoundingVolume.h"


SphereBoundingVolume::SphereBoundingVolume()
{
}

SphereBoundingVolume::SphereBoundingVolume(CVector pos, float r)
{
	this->pos = pos;
	this->radius = r;
}

//�ص����,�ص�����True�����򷵻�False
//��������һ�����ΰ�Χ��
bool SphereBoundingVolume::OverlapTest(SphereBoundingVolume SBV)
{
	float PosDis = (SBV.pos - this->pos).len();
	float RDis = SBV.radius + this->radius;
	if ((PosDis - RDis) <= EPS) return true;
	return false;
}

void SphereBoundingVolume::setpos(CVector pos)
{
	this->pos = pos;
}
