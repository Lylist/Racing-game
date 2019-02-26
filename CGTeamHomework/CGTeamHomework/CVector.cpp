#include "OurMath.h"
void CVector::Set(float xx, float yy, float zz)
{
	x = xx, y = yy, z = zz;
}
CVector CVector::operator +(CVector &p)
{
	CVector tar;
	tar.x = x + p.x;
	tar.y = y + p.y;
	tar.z = z + p.z;
	return tar;
}
CVector CVector::operator +(const CVector &p)
{
	CVector tar;
	tar.x = x + p.x;
	tar.y = y + p.y;
	tar.z = z + p.z;
	return tar;
}
CVector CVector::operator -(CVector &p)
{
	CVector tar;
	tar.x = x - p.x;
	tar.y = y - p.y;
	tar.z = z - p.z;
	return tar;
}
CVector CVector::operator*(float radio)
{
	CVector tar;
	tar.x = x * radio;
	tar.y = y * radio;
	tar.z = z * radio;
	return tar;
}
void CVector::operator=(const CVector &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}
bool CVector::operator==(CVector &p)
{
	if (x == p.x&&y == p.y&&z == p.z)
		return true;
	else
		return false;
}
bool CVector::operator!=(CVector &p)
{
	if (x == p.x&&y == p.y&&z == p.z)
		return false;
	else
		return true;
}
float CVector::dotMul(CVector & n)
{
	float res = 0;
	res += (n.x*x);
	res += (n.y*y);
	res += (n.z*z);
	return res;
}
CVector CVector::crossMul(CVector & n)
{
	CVector tar;
	tar.x = y * n.z - z * n.y;
	tar.y = z * n.x - x * n.z;
	tar.z = x * n.y - y * n.x;
	return tar;
}
void CVector::Normalize()
{
	float mod = len();
	x /= mod, y /= mod, z /= mod;
	return;
}
CVector CVector::getNormolization()
{
	CVector res;
	float mod = len();
	res.Set(x / mod, y / mod, z / mod);
	return res;
}
float CVector::len()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
CVector CVector::project(CVector & n)
{
	n.Normalize();
	CVector tar = n * (dotMul(n) / n.len());//?
	return tar;
}
CEuler CVector::ToEuler()
{
	CEuler res;
	res.Set(0, 0, 0);
	if (len() == 0) return res;
	else
	{
		res.b = 0;
		res.h = atan2(z, x) * 180 / PI;
		if (res.h >= 0) res.h -= 180;
		else res.h += 180;
		res.p = asin(y / len()) * 180 / PI;
	}
	return res;
}
//重载输出流
ostream& operator <<(ostream&os, CVector &cv)
{
	os << fixed << setprecision(2) << cv.x << "," << fixed << setprecision(2) << cv.y << "," << fixed << setprecision(2) << cv.z;
	return os;
}//重载输出流
ostream& operator <<(ostream&os, const CVector &constcv)
{
	CVector cv = const_cast<CVector&>(constcv);
	os << fixed << setprecision(2) << cv.x << "," << fixed << setprecision(2) << cv.y << "," << fixed << setprecision(2) << cv.z;
	return os;
}
CVector operator-(CVector & cv)
{
	return CVector(-cv.x, -cv.y, -cv.z);
}
CVector operator-(const CVector& cv)
{
	return CVector(-cv.x, -cv.y, -cv.z);
}