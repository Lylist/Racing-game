#pragma once
class CMatrix;
class CVector;
class CEuler;
class CQuaternion;
#include <iostream>
using namespace std;
class CMatrix
{
	friend ostream& operator <<(ostream& os, CMatrix&);
	friend ostream& operator <<(ostream& os, const CMatrix&);
public:
	//���������е�һ�����У��ڶ������У�opengl��������
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;
	void Set(float *val);

	CMatrix& operator=(const CMatrix& p);//����ֵ
	CMatrix operator*(float d);//��������
	CMatrix operator*(CMatrix& p);//�������
	CVector vecMul(CVector& p); //�������������
	CVector posMul(CVector& p);//����������
	void SetRotate(float seta, CVector axis);	//����Ϊ��ת����
	void SetTrans(CVector trans);		//����Ϊƽ�ƾ���
	void SetScale(CVector p);		//����Ϊ���ž���
	float Inverse();//��������,�ɹ���������ʽ��ֵ�����򷵻�0
	CMatrix GetInverse();//���������
	CMatrix Transpose();//����ת�þ���

						   /*�ڼ�������У����Կ���float*����Ϊ����ʹ��
						   for(int i=0;i<16;i++)
						   mymatrix[i] = 0;*/
	operator float*() { return &m00; }

	CEuler ToEuler();
	CQuaternion ToQuaternion();

private:
	float det(float arr[], int dimension);
	float* M(float arr[], int dimension, int r, int c);
};