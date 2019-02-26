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
	friend ostream& operator <<(ostream&os, CQuaternion&cq);//���������
	friend ostream& operator <<(ostream&os, const CQuaternion&cq);//���������
public:
	float x, y, z, w;
	CVector GetAxis();
	void Set(float x, float y, float z, float w);
	void SetAngle(float angle, CVector axis);
	CQuaternion& operator=(const CQuaternion& p); //���ظ�ֵ
	CQuaternion operator+(const CQuaternion& p);//���ء�+��
	CQuaternion operator*(float data);//��������
	CQuaternion operator*(const CQuaternion&p); //��Ԫ���˷�(�¶�����)
	float dotMul(const CQuaternion&p); //���
	float len(); //��ģ
	void Normalize();	//���׼��
	void Conjugated();
	CQuaternion& Inverse();//������Ԫ��,��ı�����
	CQuaternion GetInverse();//������Ԫ��,���ı����������µ���Ԫ��
	CQuaternion Div(const CQuaternion&b); //��� ��ǰΪa,��c=a-b
	void GetAngle(float& angle, CVector& axis); //����ת��ͽǶ�
	CQuaternion Slerp(const CQuaternion& Vend, float t); //��ֵ���ӵ�ǰ��Ԫ����ֵ��Vend��Ԫ��,t�ǲ���[0,1]
	void Slerp(const CQuaternion& Vend, int n, float *t, CQuaternion *Result);//��ֵ��һ�β�ֵ��n�����ݡ���ֵ��������������t�У�������ص�����Result�С�

	operator float*() { return &x; }

	CMatrix ToMatrix();
	CEuler ToEuler();
};