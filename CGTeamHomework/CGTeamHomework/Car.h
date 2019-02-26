#pragma once
#include "OurMath.h"
#include "CubeBoundingVolume.h"
#include "SphereBoundingVolume.h"
#include "TextureManager.h"
#include "GameManager.h"
#include <GL/glut.h>
struct Road {
	CVector target;
	CVector last;
	CVector next;
};
class Car
{
public:
	Car(int id);
	Car(int id,float s);

	CVector pos, dir;	//位置和方向
	CEuler Edir;
	float max_speed, speed;		//速度
	CubeBoundingVolume car_CBV;	//包围盒
	vector<Road> myroad;
	int now_load;	//当前所在路段
	int CarID;
	bool IsEnd;

	void intialRoad();
	//运动控制
	int Run();		//运动，参数未定,返回值为操作结果(能否成功运动)
	int TurnLeft();		//左转，参数未定，返回值是操作结果
	int TurnRight();	//右转，参数未定，返回值是操作结果
	int AddSpeed();		//加速，参数未定，返回值是操作结果
	void DrawPlayerCar();	//绘画玩家小车
	void DrawNPCCar();
	void DrawNPCCar2();
	void AutoRun();
	int StatusChange();		//小车状态改变，比如加速、转湾，是否进一步分离功能还是用多态需要商量
	void ReachEnd();
private:
	CQuaternion turnLerp[105];
	bool isLerp,isFirst;
	int lerpCnt;
	CVector nextdir;
	float angle;
};