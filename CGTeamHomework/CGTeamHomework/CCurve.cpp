#include "OurMath.h"
CCurve::CCurve()
{
}
CCurve::CCurve(vector<CVector>p)
{
	pointv = p;
	pvlen = pointv.size();
}

vector<CVector> CCurve::GetCurve() const
{
	return pointv;
}

bool CCurve::curveIntersect(const CCurve & q, int type, vector<CVector>&res)
{
	bool IsIntersect = false;
	vector<CVector>curve2 = q.GetCurve();
	int n1 = pointv.size();
	int n2 = curve2.size();
	for (int i = 0; i < n1 - 1; i++)
	{
		CVector s1 = pointv[i];
		CVector e1 = pointv[i + 1];
		CVector oriv1 = e1 - s1;
		oriv1.Normalize();
		switch (type)
		{
		case 0:
		{
			s1.x = 0;
			e1.x = 0;
			break;
		}
		case 1:
		{
			s1.y = 0;
			e1.y = 0;
			break;
		}
		case 2:
		{
			s1.z = 0;
			e1.z = 0;
			break;
		}
		default:
			break;
		}
		CVector v1 = e1 - s1;
		v1.Normalize();
		for (int j = 0; j < n2 - 1; j++)
		{
			CVector s2 = curve2[j];
			CVector e2 = curve2[j + 1];
			switch (type)
			{
			case 0:
			{
				s2.x = 0;
				e2.x = 0;
				break;
			}
			case 1:
			{
				s2.y = 0;
				e2.y = 0;
				break;
			}
			case 2:
			{
				s2.z = 0;
				e2.z = 0;
				break;
			}
			default:
				break;
			}
			CVector v2 = e2 - s2;
			v2.Normalize();


			CVector s2s1 = s1 - s2;
			CVector normal = v1.crossMul(v2);
			float normalLen = normal.len();
			if (normalLen < EPS)
			{
				if (s2s1.crossMul(v1).len() < EPS)
				{
					res.push_back(pointv[i]);
					IsIntersect = true;
				}
				continue;
			}
			if (s2s1.crossMul(v1).dotMul(v2) > EPS)
				continue;
			else
			{
				float len1 = (s2s1.crossMul(v2).len()) / (v2.crossMul(v1).len());
				float len2 = ((s2 - s1).crossMul(v1).len()) / (v1.crossMul(v2).len());
				CVector tmp1 = v2.crossMul(v1);
				if (s2s1.crossMul(v2).dotMul(tmp1) < 0)
					len1 = -len1;
				CVector tmp2 = v1.crossMul(v2);
				if ((s2 - s1).crossMul(v1).dotMul(tmp2) < 0)
					len2 = -len2;
				if (len1 >= 0 && len1 <= (pointv[i + 1] - pointv[i]).len() && len2 >= 0 && len2 <= (curve2[j + 1] - curve2[j]).len())
				{
					switch (type)
					{
					case 0:
					{
						if (oriv1.y == 0)
						{
							v1.x = oriv1.x*v1.z / oriv1.z;
						}
						else
						{
							v1.x = oriv1.x*v1.y / oriv1.y;
						}
						break;
					}
					case 1:
					{
						if (oriv1.x == 0)
						{
							v1.y = oriv1.y*v1.z / oriv1.z;
						}
						else
						{
							v1.y = oriv1.y*v1.x / oriv1.x;
						}
						break;
					}
					case 2:
					{
						if (oriv1.x == 0)
						{
							v1.z = oriv1.z* v1.y / oriv1.y;
						}
						else
						{
							v1.z = oriv1.z*v1.x / oriv1.x;
						}
						break;
					}
					}
					res.push_back(pointv[i] + v1 * len1);
					IsIntersect = true;
				}
				continue;
			}
		}
	}
	if (IsIntersect)
		return true;
	else
		return false;
}

float CCurve::pointCurveDis(CVector p, CVector&res, int type)
{
	float minn = 0x7fffffff;
	for (int i = 0; i < pvlen - 1; i++)
	{
		float dis;
		float dirdis;
		CVector s = pointv[i];
		CVector e = pointv[i + 1];
		switch (type)
		{
		case 0:
		{
			s.x = 0;
			e.x = 0;
			break;
		}
		case 1:
		{
			s.y = 0;
			e.y = 0;
			break;
		}
		case 2:
		{
			s.z = 0;
			e.z = 0;
			break;
		}
		default:
			break;
		}
		CVector se = e - s;
		CVector es = s - e;
		CVector sp = p - s;
		CVector ep = p - e;
		if (sp.dotMul(se) < 0)
		{
			dis = sp.len();
			dirdis = 0;
		}
		else if (ep.dotMul(es) < 0)
		{
			dis = ep.len();
			dirdis = se.len();
		}
		else
		{
			dirdis = sp.dotMul(se) / se.len();
			dis = sqrt(pow(sp.len(), 2) - pow(dirdis, 2));
		}
		if (dis >= minn)
			continue;
		else
		{
			minn = dis;
			CVector dirv = se.getNormolization() * dirdis;
			if (type != -1)
			{
				CVector oriv1 = pointv[i + 1] - pointv[i];
				switch (type)
				{
				case 0:
				{
					if (oriv1.y == 0)
					{
						dirv.x = oriv1.x*dirv.z / oriv1.z;
					}
					else
					{
						dirv.x = oriv1.x*dirv.y / oriv1.y;
					}
					break;
				}
				case 1:
				{
					if (oriv1.x == 0)
					{
						dirv.y = oriv1.y*dirv.z / oriv1.z;
					}
					else
					{
						dirv.y = oriv1.y*dirv.x / oriv1.x;
					}
					break;
				}
				case 2:
				{
					if (oriv1.x == 0)
					{
						dirv.z = oriv1.z* dirv.y / oriv1.y;
					}
					else
					{
						dirv.z = oriv1.z*dirv.x / oriv1.x;
					}
					break;
				}
				}
			}
			res = s + dirv;
		}
	}
	return minn;
}

bool CCurve::isPointInCurve(CVector p)
{
	return false;
}

bool CCurve::pointMoveOnCurve(float movedis, int nowindex, float nowdis, CVector&res, int &resindex, float &resdis)
{
	float remaindis = movedis;
	if (nowindex >= pvlen - 1)
	{
		cout << "数据输入有误" << endl;
		return false;
	}
	float nowlen = (pointv[nowindex + 1] - pointv[nowindex]).len();
	if (nowdis > nowlen)
	{
		cout << "数据输入有误" << endl;
		return false;
	}
	else
	{
		if (nowlen - nowdis > remaindis)
		{
			resindex = nowindex;
			resdis = nowdis + remaindis;
			res = pointv[nowindex] + (pointv[nowindex + 1] - pointv[nowindex]).getNormolization()*resdis;
			return true;
		}
		else
			remaindis -= (nowlen - nowdis);
	}
	for (int i = nowindex + 1; i < pvlen - 1; i++)
	{
		nowlen = (pointv[i + 1] - pointv[i]).len();
		if (nowlen > remaindis)
		{
			resindex = i;
			resdis = remaindis;
			res = pointv[i] + (pointv[i + 1] - pointv[i]).getNormolization()*resdis;
			return true;
		}
		else
			remaindis -= nowlen;
	}
	resindex = pvlen - 1;
	resdis = 0;
	res = pointv[pvlen - 1];
	cout << "输出的移动长度大于折线剩余长度" << endl;
	return true;
}
