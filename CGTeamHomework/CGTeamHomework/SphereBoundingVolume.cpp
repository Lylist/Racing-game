#include "SphereBoundingVolume.h"


SphereBoundingVolume::SphereBoundingVolume()
{
}

SphereBoundingVolume::SphereBoundingVolume(CVector pos, float r)
{
	this->pos = pos;
	this->radius = r;
}

//重叠检测,重叠返回True，否则返回False
//参数：另一个球形包围盒
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
