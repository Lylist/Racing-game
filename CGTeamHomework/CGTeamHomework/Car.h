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

	CVector pos, dir;	//λ�úͷ���
	CEuler Edir;
	float max_speed, speed;		//�ٶ�
	CubeBoundingVolume car_CBV;	//��Χ��
	vector<Road> myroad;
	int now_load;	//��ǰ����·��
	int CarID;
	bool IsEnd;

	void intialRoad();
	//�˶�����
	int Run();		//�˶�������δ��,����ֵΪ�������(�ܷ�ɹ��˶�)
	int TurnLeft();		//��ת������δ��������ֵ�ǲ������
	int TurnRight();	//��ת������δ��������ֵ�ǲ������
	int AddSpeed();		//���٣�����δ��������ֵ�ǲ������
	void DrawPlayerCar();	//�滭���С��
	void DrawNPCCar();
	void DrawNPCCar2();
	void AutoRun();
	int StatusChange();		//С��״̬�ı䣬������١�ת�壬�Ƿ��һ�����빦�ܻ����ö�̬��Ҫ����
	void ReachEnd();
private:
	CQuaternion turnLerp[105];
	bool isLerp,isFirst;
	int lerpCnt;
	CVector nextdir;
	float angle;
};