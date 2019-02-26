#pragma once
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>

using namespace std;
class CMatrix;
class CVector;
class CEuler;
class CQuaternion;
class CVector
{
	friend ostream& operator <<(ostream&os, CVector&cv);//重载输出流
	friend ostream& operator <<(ostream&os, const CVector&cv);//重载输出流
	friend CVector operator - (const CVector&cv);//重载负号
	friend CVector operator - (CVector&cv);//重载负号
public:
	CVector() {  }
	CVector(float xx, float yy, float zz) { x = xx, y = yy, z = zz; }
	float x;
	float y;
	float z;
	void Set(float, float, float);
	CVector operator +(CVector &p);
	CVector operator +(const CVector&p);
	CVector operator -(CVector &p);
	CVector operator *(float);
	void operator =(const CVector &p);
	bool operator ==(CVector &p);
	bool operator !=(CVector &p);
	float dotMul(CVector &n);
	CVector crossMul(CVector &n);
	void Normalize();
	CVector getNormolization();
	float len();
	CVector project(CVector &n);
	operator float*() { return &x; }
	CEuler ToEuler();
};