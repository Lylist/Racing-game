#pragma once
#include <cmath>
class CMatrix;
class CVector;
class CEuler;
class CQuaternion;
#include <iostream>
using namespace std;
class CQuaternion
{
	friend ostream& operator <<(ostream&os, CQuaternion&cq);//重载输出流
	friend ostream& operator <<(ostream&os, const CQuaternion&cq);//重载输出流
public:
	float x, y, z, w;
	CVector GetAxis();
	void Set(float x, float y, float z, float w);
	void SetAngle(float angle, CVector axis);
	CQuaternion& operator=(const CQuaternion& p); //重载赋值
	CQuaternion operator+(const CQuaternion& p);//重载‘+’
	CQuaternion operator*(float data);//重载数乘
	CQuaternion operator*(const CQuaternion&p); //四元数乘法(新定义下)
	float dotMul(const CQuaternion&p); //点乘
	float len(); //求模
	void Normalize();	//求标准化
	void Conjugated();
	CQuaternion& Inverse();//求逆四元数,会改变自身。
	CQuaternion GetInverse();//求逆四元数,不改变自身，生成新的四元数
	CQuaternion Div(const CQuaternion&b); //求差 当前为a,求c=a-b
	void GetAngle(float& angle, CVector& axis); //求旋转轴和角度
	CQuaternion Slerp(const CQuaternion& Vend, float t); //插值。从当前四元数插值到Vend四元数,t是参数[0,1]
	void Slerp(const CQuaternion& Vend, int n, float *t, CQuaternion *Result);//插值。一次插值出n个数据。插值参数保存在数组t中，结果返回到数组Result中。

	operator float*() { return &x; }

	CMatrix ToMatrix();
	CEuler ToEuler();
};