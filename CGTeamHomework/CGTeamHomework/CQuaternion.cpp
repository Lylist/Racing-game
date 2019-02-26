#include "OurMath.h"
ostream& operator <<(ostream&os, CQuaternion&cq)
{
	os << fixed << setprecision(2) << cq.x << "," << fixed << setprecision(2) << cq.y << "," << fixed << setprecision(2) << cq.z << "," << fixed << setprecision(2) << cq.w;
	return os;
}
ostream& operator <<(ostream&os, const CQuaternion&cq)
{
	os << fixed << setprecision(2) << cq.x << "," << fixed << setprecision(2) << cq.y << "," << fixed << setprecision(2) << cq.z << "," << fixed << setprecision(2) << cq.w;
	return os;
}

CVector CQuaternion::GetAxis()
{
	CVector res(x, y, z);
	return res;
}
void CQuaternion::Set(float xx, float yy, float zz, float ww)
{
	x = xx;
	y = yy;
	z = zz;
	w = ww;
}

void CQuaternion::SetAngle(float angle, CVector axis)
{
	w = cos(angle / 2);
	x = axis.x*sin(angle / 2);
	y = axis.y*sin(angle / 2);
	z = axis.z*sin(angle / 2);
}

CQuaternion & CQuaternion::operator=(const CQuaternion & p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	w = p.w;
	return (*this);
}

CQuaternion CQuaternion::operator+(const CQuaternion & p)
{
	CQuaternion res;
	res.x = x + p.x;
	res.y = y + p.y;
	res.z = z + p.z;
	res.w = w + p.w;
	return res;
}

CQuaternion CQuaternion::operator*(float data)
{
	CQuaternion res;
	res.x = x * data;
	res.y = y * data;
	res.z = z * data;
	res.w = w * data;
	return res;
}

CQuaternion CQuaternion::operator*(const CQuaternion & p)
{
	CQuaternion res;
	CVector v1, v2, resv;
	v1 = this->GetAxis();
	v2.Set(p.x, p.y, p.z);
	v2 = const_cast<CQuaternion&>(p).GetAxis();
	res.w = w * p.w - v1.dotMul(v2);
	resv = v2 * w + v1 * p.w + v2.crossMul(v1);
	res.Set(resv.x, resv.y, resv.z, res.w);
	return res;
}

float CQuaternion::dotMul(const CQuaternion & p)
{
	float res;
	CVector v1, v2;
	v1 = this->GetAxis();
	v2 = const_cast<CQuaternion&>(p).GetAxis();
	res = w * p.w + v1.dotMul(v2);
	return res;
}

float CQuaternion::len()
{
	float res = sqrt(pow(w, 2) + pow(x, 2) + pow(y, 2) + pow(z, 2));
	return res;
}

void CQuaternion::Normalize()
{
	float ratio = 1 / this->len();
	x *= ratio;
	y *= ratio;
	z *= ratio;
	w *= ratio;
}

void CQuaternion::Conjugated()
{
	x = -x;
	y = -y;
	z = -z;
}

CQuaternion & CQuaternion::Inverse()
{
	CQuaternion conjugated;
	conjugated.Set(-x, -y, -z, w);
	float ratio = 1 / (this->len()*this->len());
	(*this) = conjugated * ratio;
	return (*this);
}

CQuaternion CQuaternion::GetInverse()
{
	CQuaternion conjugated, res;
	conjugated.Set(-x, -y, -z, w);
	float ratio = 1 / (this->len()*this->len());
	conjugated = conjugated * ratio;
	return conjugated;
}

CQuaternion CQuaternion::Div(const CQuaternion & b)
{
	CQuaternion inv, res;
	inv = GetInverse();
	res = inv * b;
	return res;
}

void CQuaternion::GetAngle(float & angle, CVector & axis)
{
	(*this).Normalize();
	float realangle = 2 * acos(w);
	float axisratio = 1 / sin(realangle / 2);
	angle = realangle * 180 / 3.14159;
	axis.x = x * axisratio;
	axis.y = y * axisratio;
	axis.z = z * axisratio;
}

//可用点乘计算两个四元数的角度
CQuaternion CQuaternion::Slerp(const CQuaternion & Vend, float t)
{
	(*this).Normalize();
	const_cast<CQuaternion&>(Vend).Normalize();
	float angle = dotMul(Vend);
	CQuaternion res;
	float ratios, ratioe;
	ratios = sin((1 - t)*angle) / sin(angle);
	ratioe = sin(t*angle) / sin(angle);
	//const_cast<CQuaternion&>(Vend).Conjugated();
	res = (*this)*ratios + const_cast<CQuaternion&>(Vend) * ratioe;
	res.Normalize();
	return res;
}

void CQuaternion::Slerp(const CQuaternion & Vend, int n, float * t, CQuaternion * Result)
{
	for (int i = 0; i < n; i++)
	{
		Result[i] = Slerp(Vend, t[i]);
	}
}

CMatrix CQuaternion::ToMatrix()
{
	CMatrix res;
	res[0] = 1 - 2 * y*y - 2 * z*z, res[4] = 2 * x*y - 2 * w*z, res[8] = 2 * x*z + 2 * w*y, res[12] = 0;
	res[1] = 2 * x*y + 2 * w*z, res[5] = 1 - 2 * x*x - 2 * z*z, res[9] = 2 * z*y - 2 * w*x, res[13] = 0;
	res[2] = 2 * x*z - 2 * w*y, res[6] = 2 * z*y + 2 * w*x, res[10] = 1 - 2 * x*x - 2 * y*y, res[14] = 0;
	res[3] = 0, res[7] = 0, res[11] = 0, res[15] = 1;
	return res;
}

CEuler CQuaternion::ToEuler()
{
	CEuler res;
	res.p = asin(2 * w*x - 2 * y*z);
	if (cos(res.p) == 0)
	{
		res.h = atan2(2 * w*y - 2 * x*z, 1 - 2 * y*y - 2 * z*z);
		res.b = 0;
	}
	else
	{
		res.h = atan2(2 * z*x + 2 * w*y, 1 - 2 * x*x - 2 * y*y);
		res.b = atan2(2 * x*y + 2 * w*z, 1 - 2 * z*z - 2 * x*x);
	}
	res.p = res.p * 180 / PI;
	res.h = res.h * 180 / PI;
	res.b = res.b * 180 / PI;
	return res;
}
