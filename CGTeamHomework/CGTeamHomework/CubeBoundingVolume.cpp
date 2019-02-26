#include "CubeBoundingVolume.h"

CubeBoundingVolume::CubeBoundingVolume()
{
}

CubeBoundingVolume::CubeBoundingVolume(CVector pos, float length, float width, float heigth, CVector dir)
{
	this->pos = pos;
	this->length = length;
	this->width = width;
	this->heigth = heigth;

	CVector tmp(0, 1, 0);
	CVector cross_dir = dir.crossMul(tmp);

	cross_dir.Normalize();

	this->point_pos[0] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[1] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[2] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (-heigth / 2.0);
	this->point_pos[3] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (-heigth / 2.0);
	this->point_pos[4] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[5] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[6] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (-heigth / 2.0);
	this->point_pos[7] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (-heigth / 2.0);

	/*
	this->point_pos[0]=pos+CVector(-length/2.0, width/2.0, heigth/2.0);
	this->point_pos[1]=pos+CVector(length/2.0, width/2.0, heigth/2.0);
	this->point_pos[2]=pos+CVector(-length/2.0, width/2.0, -heigth/2.0);
	this->point_pos[3]=pos+CVector(length/2.0, width/2.0, -heigth/2.0);
	this->point_pos[4]=pos+CVector(-length/2.0, -width/2.0, heigth/2.0);
	this->point_pos[5]=pos+CVector(length/2.0, -width/2.0, heigth/2.0);
	this->point_pos[6]=pos+CVector(-length/2.0, -width/2.0, -heigth/2.0);
	this->point_pos[7]=pos+CVector(length/2.0, -width/2.0, -heigth/2.0);
	*/
	this->dir = dir;
}


void CubeBoundingVolume::setpos(CVector pos, CVector dir)
{
	this->pos = pos;
	dir.Normalize();
	CVector tmp(0.0, 1.0, 0.0);
	CVector cross_dir = dir.crossMul(tmp);

	cross_dir.Normalize();
	//printf("%.4f %.4f %.4f %.4f\n",cross_dir.len(),dir.len(),dir.dotMul(cross_dir),cross_dir.dotMul(CVector(0,1,0)));
	this->point_pos[0] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[1] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[2] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (-heigth / 2.0);
	this->point_pos[3] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(width / 2.0) + cross_dir * (-heigth / 2.0);
	this->point_pos[4] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[5] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (heigth / 2.0);
	this->point_pos[6] = pos + dir * (-length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (-heigth / 2.0);
	this->point_pos[7] = pos + dir * (length / 2.0) + CVector(0, 1, 0)*(-width / 2.0) + cross_dir * (-heigth / 2.0);

	float max_x = -1e12, max_y = -1e8, max_z = -1e8, min_x = 1e8, min_y = 1e8, min_z = 1e8;
	for (int i = 0; i<8; i++)
	{
		max_x = max(max_x, this->point_pos[i].x);
		min_x = min(min_x, this->point_pos[i].x);

		max_y = max(max_y, this->point_pos[i].y);
		min_y = min(min_y, this->point_pos[i].y);

		max_z = max(max_z, this->point_pos[i].z);
		min_z = min(min_z, this->point_pos[i].z);
	}
	if (fabs(max_x - min_x - length)>EPS)
	{
		//cout << this->pos;
		//printf("")
	}
	this->dir = dir;
}


//重叠检测,重叠返回True，否则返回False
//参数：另一个方形包围盒
bool CubeBoundingVolume::OverlapTest(CubeBoundingVolume CBV)
{
	//第一遍检查
	float max_x = -1e12, max_y = -1e8, max_z = -1e8, min_x = 1e8, min_y = 1e8, min_z = 1e8;
	for (int i = 0; i<8; i++)
	{
		max_x = max(max_x, CBV.point_pos[i].x);
		min_x = min(min_x, CBV.point_pos[i].x);

		max_y = max(max_y, CBV.point_pos[i].y);
		min_y = min(min_y, CBV.point_pos[i].y);

		max_z = max(max_z, CBV.point_pos[i].z);
		min_z = min(min_z, CBV.point_pos[i].z);
	}
	for (int i = 0; i<8; i++)
	{
		if ((max_x - this->point_pos[i].x) >= EPS && (min_x - this->point_pos[i].x) <= EPS &&
			(max_y - this->point_pos[i].y) >= EPS && (min_y - this->point_pos[i].y) <= EPS &&
			(max_z - this->point_pos[i].z) >= EPS && (min_z - this->point_pos[i].z) <= EPS) return true;
	}
	//printf("%f %f %f %f %f %f\nCBV:%f %f %f\n",max_x,max_y,max_z,min_x,min_y,min_z,CBV.length,CBV.width,CBV.heigth);

	//第二遍检查
	max_x = -1e8, max_y = -1e8, max_z = -1e8, min_x = 1e8, min_y = 1e8, min_z = 1e8;
	for (int i = 0; i<8; i++)
	{
		max_x = max(max_x, this->point_pos[i].x);
		min_x = min(min_x, this->point_pos[i].x);

		max_y = max(max_y, this->point_pos[i].y);
		min_y = min(min_y, this->point_pos[i].y);

		max_z = max(max_z, this->point_pos[i].z);
		min_z = min(min_z, this->point_pos[i].z);
	}
	//printf("%f %f %f %f %f %f\nMY:%f %f %f\n",max_x,max_y,max_z,min_x,min_y,min_z,this->length,this->width,this->heigth);
	for (int i = 0; i<8; i++)
	{
		if ((max_x - CBV.point_pos[i].x) >= EPS && (min_x - CBV.point_pos[i].x) <= EPS &&
			(max_y - CBV.point_pos[i].y) >= EPS && (min_y - CBV.point_pos[i].y) <= EPS &&
			(max_z - CBV.point_pos[i].z) >= EPS && (min_z - CBV.point_pos[i].z) <= EPS) return true;
	}

	return false;
}