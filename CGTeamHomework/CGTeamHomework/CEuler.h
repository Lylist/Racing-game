#pragma once
class CMatrix;
class CVector;
class CEuler;
class CQuaternion;
#include <iostream>
using namespace std;
class CEuler
{
	friend ostream& operator <<(ostream&os, CEuler&);
	friend ostream& operator <<(ostream&os, const CEuler&);
public:
	float h, p, b;//hÆ«º½½Ç£¬p¸©Ñö½Ç£¬b·­¹ö½Ç
	void Set(float h, float p, float b);
	operator float*() { return &h; }
	void Normal();
	CEuler(float hh, float pp, float bb) { h = hh, p = pp, b = bb; }
	CEuler() {}
	CVector ToVector3(CVector*updir = 0);
	CQuaternion ToQuaternion();
	CMatrix ToMatrix();
};
