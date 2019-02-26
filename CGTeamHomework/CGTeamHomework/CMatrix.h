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
	//两个数字中第一个是行，第二个是列，opengl中列优先
	float m00, m10, m20, m30;
	float m01, m11, m21, m31;
	float m02, m12, m22, m32;
	float m03, m13, m23, m33;
	void Set(float *val);

	CMatrix& operator=(const CMatrix& p);//矩阵赋值
	CMatrix operator*(float d);//矩阵数乘
	CMatrix operator*(CMatrix& p);//矩阵相乘
	CVector vecMul(CVector& p); //矩阵与向量相乘
	CVector posMul(CVector& p);//矩阵与点相乘
	void SetRotate(float seta, CVector axis);	//设置为旋转矩阵
	void SetTrans(CVector trans);		//设置为平移矩阵
	void SetScale(CVector p);		//设置为缩放矩阵
	float Inverse();//矩阵求逆,成功返回行列式的值，否则返回0
	CMatrix GetInverse();//返回逆矩阵
	CMatrix Transpose();//返回转置矩阵

						   /*在计算过程中，可以看做float*，作为数组使用
						   for(int i=0;i<16;i++)
						   mymatrix[i] = 0;*/
	operator float*() { return &m00; }

	CEuler ToEuler();
	CQuaternion ToQuaternion();

private:
	float det(float arr[], int dimension);
	float* M(float arr[], int dimension, int r, int c);
};