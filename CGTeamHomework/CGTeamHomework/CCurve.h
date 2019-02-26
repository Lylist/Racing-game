#pragma once
class CVector;
#include <vector>
using namespace std;
class CCurve
{
public:
	CCurve();
	CCurve(vector<CVector>);
	vector<CVector>GetCurve() const;
	bool curveIntersect(const CCurve& q, int type, vector<CVector>&res);
	float pointCurveDis(CVector p, CVector&res, int type);
	bool isPointInCurve(CVector p);
	bool pointMoveOnCurve(float movedis, int nowindex, float nowdis, CVector&res, int &resindex, float &resdis);
private:
	vector<CVector>pointv;
	int pvlen;

};