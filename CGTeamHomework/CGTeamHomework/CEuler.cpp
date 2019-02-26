#include "OurMath.h"
ostream& operator <<(ostream&os, CEuler&ce)
{
	os << fixed << setprecision(2) << ce.h << "," << fixed << setprecision(2) << ce.p << "," << fixed << setprecision(2) << ce.b;
	return os;
}
ostream& operator <<(ostream&os, const CEuler&ce)
{
	os << fixed << setprecision(2) << ce.h << "," << fixed << setprecision(2) << ce.p << "," << fixed << setprecision(2) << ce.b;
	return os;
}
void CEuler::Set(float hh, float pp, float bb)
{
	h = hh;
	p = pp;
	b = bb;
}
// 如果传入updir指针不为0，则输出向量同时输出上方向量到updir中。
CVector CEuler::ToVector3(CVector * updir)
{
	CVector res;
	double angleh = (h + 180)*PI / 180;
	double anglep = p * PI / 180;
	res.y = sin(anglep);
	res.x = cos(anglep)*sin(angleh);
	res.z = cos(anglep)*cos(angleh);
	if (updir != nullptr)
	{
		CMatrix mat = ToMatrix();
		CVector cv(0, 1, 0);
		(*updir) = mat.vecMul(cv);
	}
	return res;
}
// h, r角度在 - 180~180，p角度在 - 90~90。万向锁时, h代替所有r的度数。
void CEuler::Normal()
{
	int cnt;
	bool isgimblelock = false;
	if (p > 90)
	{
		cnt = (p - 90) / 360 + 1;
		p -= cnt * 360;
	}
	else if (p < -90)
	{
		cnt = (-90 - p) / 360 + 1;
		p += cnt * 360;
	}
	if (p == -90 || p == 90) isgimblelock = true;
	if (h > 180)
	{
		cnt = (h - 180) / 360 + 1;
		h -= cnt * 360;
	}
	else if (h < -180)
	{
		cnt = (-180 - h) / 360 + 1;
		h += cnt * 360;
	}
	if (isgimblelock) b = h;
	else
	{
		if (b > 180)
		{
			cnt = (b - 180) / 360 + 1;
			b -= cnt * 360;
		}
		else if (b < -180)
		{
			cnt = (-180 - b) / 360 + 1;
			b += cnt * 360;
		}
	}
}

CQuaternion CEuler::ToQuaternion()
{
	p = p * PI / 180;
	h = h * PI / 180;
	b = b * PI / 180;
	CQuaternion res;
	res.w = cos(h / 2)*cos(p / 2)*cos(b / 2) + sin(h / 2)*sin(p / 2)*sin(b / 2);
	res.x = cos(h / 2)*sin(p / 2)*cos(b / 2) + sin(h / 2)*cos(p / 2)*sin(b / 2);
	res.y = sin(h / 2)*cos(p / 2)*cos(b / 2) - cos(h / 2)*sin(p / 2)*sin(b / 2);
	res.z = cos(h / 2)*cos(p / 2)*sin(b / 2) - sin(h / 2)*sin(p / 2)*cos(b / 2);
	return res;
}

CMatrix CEuler::ToMatrix()
{
	CMatrix res;
	CMatrix cmtmp;
	CVector cvtmp(0, 1, 0);
	cmtmp.SetRotate(h, cvtmp);
	res = cmtmp;
	cvtmp.Set(1, 0, 0);
	cmtmp.SetRotate(p, cvtmp);
	res = res * cmtmp;
	cvtmp.Set(0, 0, 1);
	cmtmp.SetRotate(b, cvtmp);
	res = res * cmtmp;
	return res;
}

