#include "OurMath.h"


void CMatrix::Set(float * val)
{
	for (int i = 0; i < 16; i++)
		(*this)[i] = val[i];
}

ostream& operator <<(ostream&os, CMatrix&cm)//两个参数的前后顺序不能变
{
	for (int i = 0; i < 16; i++)
	{
		os << fixed << setprecision(2) << cm[i];
		if (i != 15)
			os << ",";
	}
	return os;
}


ostream& operator <<(ostream& os, const CMatrix& p)
{
	CMatrix& cm = const_cast<CMatrix&>(p);
	for (int i = 0; i < 16; i++)
	{
		os << fixed << setprecision(2) << cm[i];
		if (i != 15)
			os << ",";
	}
	return os;
}

CMatrix& CMatrix::operator=(const CMatrix& m)
{
	m00 = m.m00, m10 = m.m10, m20 = m.m20, m30 = m.m30;
	m01 = m.m01, m11 = m.m11, m21 = m.m21, m31 = m.m31;
	m02 = m.m02, m12 = m.m12, m22 = m.m22, m32 = m.m32;
	m03 = m.m03, m13 = m.m13, m23 = m.m23, m33 = m.m33;
	return *this;
}

CMatrix CMatrix::operator*(float d)
{
	CMatrix tmp;
	for (int i = 0; i < 16; i++)
		tmp[i] = (*this)[i] * d;
	return tmp;
}

CMatrix CMatrix::operator*(CMatrix & m)
{
	CMatrix tmp;
	for (int i = 0; i < 16; i += 4)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp[i + j] = (*this)[j] * m[i] + (*this)[j + 4] * m[i + 1] + (*this)[j + 8] * m[i + 2] + (*this)[j + 12] * m[i + 3];
		}
	}
	return tmp;
}

CVector CMatrix::vecMul(CVector & v)//三维矩阵和向量相乘，得三维向量
{
	CVector tmp;
	for (int i = 0; i < 3; i++)
	{
		tmp[i] = (*this)[i] * v.x + (*this)[i + 4] * v.y + (*this)[i + 8] * v.z;
	}
	return tmp;
}

CVector CMatrix::posMul(CVector & p)//三维向量扩成四维，扩展位补1；矩阵和向量乘完后为四维向量，再转为三维返回
{
	CVector tmp;
	for (int i = 0; i < 3; i++)
	{
		tmp[i] = (*this)[i] * p.x + (*this)[i + 4] * p.y + (*this)[i + 8] * p.z + (*this)[i + 12];
	}
	return tmp;
}

void CMatrix::SetRotate(float seta, CVector axis)
{
	seta = seta * 3.1415926 / 180;
	float c = cos(seta);
	float s = sin(seta);
	m00 = axis.x*axis.x*(1 - c) + c; m01 = axis.x*axis.y*(1 - c) - axis.z*s; m02 = axis.x*axis.z*(1 - c) + axis.y*s; m03 = 0;
	m10 = axis.x*axis.y*(1 - c) + axis.z*s; m11 = axis.y*axis.y*(1 - c) + c; m12 = axis.y*axis.z*(1 - c) - axis.x*s; m13 = 0;
	m20 = axis.x*axis.z*(1 - c) - axis.y*s; m21 = axis.y*axis.z*(1 - c) + axis.x*s; m22 = axis.z*axis.z*(1 - c) + c; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

void CMatrix::SetTrans(CVector trans)
{
	m00 = 1; m01 = 0; m02 = 0; m03 = trans.x;
	m10 = 0; m11 = 1; m12 = 0; m13 = trans.y;
	m20 = 0; m21 = 0; m22 = 1; m23 = trans.z;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

void CMatrix::SetScale(CVector p)
{
	m00 = p.x; m01 = 0; m02 = 0; m03 = 0;
	m10 = 0; m11 = p.y; m12 = 0; m13 = 0;
	m20 = 0; m21 = 0; m22 = p.z; m23 = 0;
	m30 = 0; m31 = 0; m32 = 0; m33 = 1;
}

float CMatrix::Inverse()
{
	return det((*this), 4);
}

CMatrix CMatrix::GetInverse()
{
	if (Inverse() == 0)
		return CMatrix();
	CMatrix tmp;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tmp[i * 4 + j] = det(M((*this), 4, i, j), 3);
			if ((i + j) % 2 == 1)
				tmp[i * 4 + j] = -tmp[i * 4 + j];
		}
	}
	float detori = 1 / det((*this), 4);
	tmp = tmp.Transpose();
	tmp = tmp * detori;
	for (int i = 0; i < 16; i++)
		if (tmp[i] == -0)
			tmp[i] = 0;
	return tmp;
}

CMatrix CMatrix::Transpose()
{
	CMatrix tmp;
	int p = 0;
	for (int i = 0; i < 4; i++)
	{
		tmp[p++] = (*this)[i];
		tmp[p++] = (*this)[i + 4];
		tmp[p++] = (*this)[i + 8];
		tmp[p++] = (*this)[i + 12];
	}
	return tmp;
}

CEuler CMatrix::ToEuler()
{
	CEuler res;
	res.p = asin(-m12);
	if (cos(res.p) == 0)
	{
		res.h = atan2(-m20, m00);
		res.b = 0;
	}
	else
	{
		res.h = atan2(m02, m22);
		res.b = atan2(m10, m11);
	}
	res.p = res.p * 180 / PI;
	res.h = res.h * 180 / PI;
	res.b = res.b * 180 / PI;
	return res;
}

CQuaternion CMatrix::ToQuaternion()
{
	CQuaternion res;
	res.w = sqrt(m00 + m11 + m22 + 1) / 2;
	res.x = (m21 - m12) / (4 * res.w);
	res.y = (m02 - m20) / (4 * res.w);
	res.z = (m10 - m01) / (4 * res.w);
	return res;
}

float CMatrix::det(float ori[], int dimension)
{
	int sum = 0;
	if (dimension == 1)
		sum = ori[0];
	else
	{
		for (int i = 0; i < dimension; ++i)
		{
			float *tmp = M(ori, dimension, i, 0);
			int oriij = ori[i*dimension] * det(tmp, dimension - 1);
			if (i % 2 != 0)
				oriij = -oriij;
			sum = sum + oriij;

		}
	}
	return sum;
}

float* CMatrix::M(float ori[], int dimension, int r, int c)
{
	float *ret = (float*)malloc((dimension - 1)*(dimension - 1) * sizeof(float));
	int k = 0;
	for (int k1 = 0; k1 < dimension; ++k1)
	{
		if (k1 != r)
			for (int k2 = 0; k2 < dimension; ++k2)
				if (k2 != c)
					ret[k++] = ori[k1*dimension + k2];
	}
	return ret;
}
