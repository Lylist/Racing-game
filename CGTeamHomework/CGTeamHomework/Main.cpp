#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "string.h"
#include "iostream"
#include "vector"
#include "OurMath.h"
#include "GameObject.h"
#include "GameManager.h"
#include "SphereBoundingVolume.h"
#include "CubeBoundingVolume.h"
#include "TextureManager.h"

#include <gl/glut.h>


//CVector945 VZERO=CVector945(0,0,0);
void myDisplay(void);
int g_mode = 0;
float g_angle = 0 ;
#define POINTNUM 502
#define CIRCLENUM 20
int g_ballindex;//当前球所在的曲线节点位置。

Car mycar(1);
Car npc1(2,0.1),npc2(3,0.05);
vector<Car> Rank;
Track mytrack;
Camera TPPCamera;
Skybox skybox;
TextureManager *textureManager=TextureManager::GetInstance();
GameManager *gameManager = GameManager::GetInstance();

bool IsDebug = false;

std::vector<Car> autocar;

/** 定义光源的属性值 */
GLfloat LightAmbient[] = { 1.0f, 1.0f, 1.0f, 1.0f };    /**< 环境光参数 */
GLfloat LightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };    /**< 漫射光参数 */
GLfloat LightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };   /**< 镜面光参数 */
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 0.0f };   /**< 光源位置 */

int timecount=0,timec2=0;

int look = 1, looklock = 0, dis = 10;/*control*/
//////////////////////////////////////////////////////////////////////////
//视点位置和方向
float mx = 0, my = 0, mz = 0, rx = 0, ry = 0, rz = 0;//平移和旋转 //camera
float sx = 1, sy = 1, sz = 1;//缩放
float mspeed = 0.5, rspeed = 0.1; //control
float g_IEyeMat[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 }, g_EyeMat[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 }; //camera
float  cg_EyeMat[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1 };
int mode = 0;//camera，control
//////////////////////////////////////////////////////////
//状态变量
bool q = 0, w = 0, e = 0, a = 0, s = 0, d = 0, u = 0, i = 0, o = 0, j = 0, k = 0, l = 0;
bool up,down,k_left,k_right;
bool m_up = 0, m_down = 0, r_up = 0, r_down = 0;
bool f_1 = 0, f_2 = 0;
bool bChange = false; //control
int count = 0;
bool sl = 0;
int slt = 0;
float t = 0;
CEuler edir, eold, etmp;
CVector NowLookAt;
float NowCarSpeed;
float ox = 515;
float oy = 515;
float oz = 515;

double mytime = -9999999999999;
int flag = 2;
void Write()
{
	glDisable(GL_TEXTURE_2D);
	//设置投影方式：平行投影
	glMatrixMode(GL_PROJECTION);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	
	if (mytime < -1)
	{
		//输出字符串
		char str[64] = "Welcome to our game! ";
		char str2[128] = "Use 'W''A''S''D' or 'up''down''left''right' to control the black car.";
		char str3[64] = "Use 'F12' to change the view.";
		char str4[64] = "Please press SPACE to start.";
		int len = strlen(str);
		int len2 = strlen(str2);
		int len3 = strlen(str3);
		int len4 = strlen(str4);
		glRasterPos2f(-0.15f, 0.1f);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		glRasterPos2f(-0.5f, -0.1f);
		for (int i = 0; i < len2; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str2[i]);
		glRasterPos2f(-0.2f, -0.3f);
		for (int i = 0; i < len3; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str3[i]);
		glColor3f(1, 0, 0);
		glRasterPos2f(-0.2f, -0.5f);
		for (int i = 0; i < len4; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str4[i]);
		glColor3f(1, 1, 1);
	}
	else if (mytime >= 0 && mytime <10)
	{
		glRasterPos2f(0.0f, 0.0f);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '3');
	}
	else if (mytime >= 10 && mytime <20)
	{
		glRasterPos2f(0.0f, 0.0f);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '2');
	}
	else if (mytime >= 20 && mytime <30)
	{
		glRasterPos2f(0.0f, 0.0f);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, '1');
	}
	else if (mytime >= 30 && mytime <40)
	{
		char str[128] = "Start!";
		int len = strlen(str);
		glColor3f(1, 0, 0);
		glRasterPos2f(-0.0f, 0.0f);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
		gameManager->GameStatus = 1;
		glColor3f(1, 1, 1);
	}

	//恢复投影方式
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
void WriteEnd()
{
	glDisable(GL_TEXTURE_2D);
	//设置投影方式：平行投影
	glMatrixMode(GL_PROJECTION);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//输出字符串
	char str[64] = "Finish!";
	char str2[64] = "Your Rank:RANK ";
	int len = strlen(str);
	int len2 = strlen(str2);
	str2[len2] = gameManager->gamecount + '0';
	glColor3f(1, 0, 0);
	glRasterPos2f(0.0f, 0.1f);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	glColor3f(1, 1, 1);
	glRasterPos2f(0.0f, -0.1f);
	for (int i = 0; i < len2 + 1; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str2[i]);
	//恢复投影方式
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
void WriteRank()
{
	glDisable(GL_TEXTURE_2D);
	//设置投影方式：平行投影
	glMatrixMode(GL_PROJECTION);
	glColor3f(1, 1, 1);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(-1.0f, 1.0f, -1.0f, 1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	//输出字符串
	char str[64] = "Now Rank:RANK ";
	int len = strlen(str);
	for (int i = 0; i < 3; i++)
	{
		if(Rank[i].CarID==1)
			str[len] = i+1 + '0';
	}
	glColor3f(1, 0, 0);
	glRasterPos2f(0.0f, 0.5f);
	for (int i = 0; i < len+1; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	//恢复投影方式
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
}
//小车与小车之间的碰撞
int ImpactCheck(Car *npc)
{
	//printf("\n%f ", mycar.speed);
	if (mycar.car_CBV.OverlapTest(npc->car_CBV) == true)
	{
		std::swap(mycar.speed, npc->speed);
		//如果角度太大就不交换运动方向了，如果角度小就是完全弹性碰撞
		float delta = (mycar.Edir.h - npc->Edir.h);
		while (delta > 360) delta -= 360;
		while (delta < 0) delta += 360;
		if (delta > 180) delta = 180 - delta;
		delta = fabs(delta);
		bool flag = 0;        //表示是否交换方向了
		if (delta < 75)
		{
			std::swap(mycar.dir, npc->dir);
			std::swap(mycar.Edir, npc->Edir);

			flag = 1;
		}
		//npc->AutoRun();
		if (mycar.speed - npc->speed >= EPS)
		{
			if (flag == 1)mycar.pos = mycar.pos + mycar.dir*0.05;
			else mycar.pos = mycar.pos + npc->dir*(0.05);
			npc->pos = npc->pos + npc->dir*(-0.05);
			npc->speed -= min(npc->speed, 0.01);
		}
		else
		{
			mycar.pos = mycar.pos + mycar.dir*(-0.05);
			if (flag == 1) npc->pos = npc->pos + npc->dir*0.05;
			else npc->pos = npc->pos + mycar.dir*0.05;
			mycar.speed -= min(mycar.speed, 0.01);
		}
		//mycar.speed -= min(mycar.speed, 0.01);
		npc->car_CBV.setpos(npc->pos, npc->dir);
		mycar.car_CBV.setpos(mycar.pos, mycar.dir);
		//printf("YES\n");
		return 1;
	}
	//printf("NO\n");
	return 0;
}

//每台小车的检测
int ACarLoadImpactCheck(Car *nowcar)
{
	if (nowcar->now_load >= 20) return 0;

	Load nowload = mytrack.loads[nowcar->now_load];
	//printf("%d %d %f %f\n", mytrack.loads[nowcar->now_load].type, nowcar->now_load, nowcar->pos.x, nowcar->pos.z);
	//判断路段是否要移动到下一个
	if (nowload.type == 1)
	{
		if (nowcar->pos.z >= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.z <= nowload.back&&nowcar->now_load != 0)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 2)
	{
		if (nowcar->pos.z <= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.z >= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 3)
	{
		if (nowcar->pos.x >= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.x <= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 4)
	{
		if (nowcar->pos.x <= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.x >= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 13)
	{
		if (nowcar->pos.x >= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.z <= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 23)
	{
		if (nowcar->pos.x >= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.z >= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 24)
	{
		if (nowcar->pos.x <= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.z >= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 32)
	{
		if (nowcar->pos.z <= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.x <= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else if (nowload.type == 42)
	{
		if (nowcar->pos.z <= nowload.before)
		{
			nowcar->now_load++;
		}
		else if (nowcar->pos.x >= nowload.back)
		{
			nowcar->now_load--;
		}
	}
	else;

	//判断是否碰撞
	if (nowload.type == 1 || nowload.type == 2)
	{
		if (nowcar->pos.x + 0.4 - nowload.bound_max >= EPS)
		{
			nowcar->pos.x = nowload.bound_max - 0.5;
		}
		if (nowcar->pos.x - 0.4 - nowload.bound_min <= EPS)
		{
			nowcar->pos.x = nowload.bound_min + 0.5;
		}
	}
	else if (nowload.type == 3 || nowload.type == 4)
	{
		if (nowcar->pos.z + 0.4 - nowload.bound_max >= EPS)
		{
			nowcar->pos.z = nowload.bound_max - 0.5;
		}
		if (nowcar->pos.z - 0.4 - nowload.bound_min <= EPS)
		{
			nowcar->pos.z = nowload.bound_min + 0.5;
		}
	}
	else if (nowload.type == 13)
	{
		if (nowcar->pos.z + 0.4 - nowload.bound_max >= EPS)
		{
			nowcar->pos.z = nowload.bound_max - 0.5;
		}
		if (nowcar->pos.x - 0.4 - nowload.bound_min <= EPS)
		{
			nowcar->pos.x = nowload.bound_min + 0.5;
		}
	}
	else if (nowload.type == 23)
	{
		if (nowcar->pos.z + 0.4 - nowload.bound_max <= EPS)
		{
			nowcar->pos.z = nowload.bound_max - 0.5;
		}
		if (nowcar->pos.x - 0.4 - nowload.bound_min <= EPS)
		{
			nowcar->pos.x = nowload.bound_min + 0.5;
		}
	}
	else if (nowload.type == 32)
	{
		if (nowcar->pos.x + 0.4 - nowload.bound_max >= EPS)
		{
			nowcar->pos.x = nowload.bound_max - 0.5;
		}
		if (nowcar->pos.z - 0.4 - nowload.bound_min >= EPS)
		{
			nowcar->pos.z = nowload.bound_min + 0.5;
		}
	}
	else if (nowload.type == 24)
	{
		if (nowcar->pos.z - nowload.bound_max <= EPS)
		{
			nowcar->pos.z = nowload.bound_max;
		}
		if (nowcar->pos.x - nowload.bound_min >= EPS)
		{
			nowcar->pos.x = nowload.bound_min;
		}
	}
	else if (nowload.type == 42)
	{
		if (nowcar->pos.x - nowload.bound_max <= EPS)
		{
			nowcar->pos.x = nowload.bound_max;
		}
		if (nowcar->pos.z - nowload.bound_min >= EPS)
		{
			nowcar->pos.z = nowload.bound_min;
		}
	}
	else;

	if (nowcar->pos.z - 471 < EPS) nowcar->pos.z = 471 + 0.1;
	return 0;
}

//道路边界检测
int LoadImpactCheck()
{
	ACarLoadImpactCheck(&mycar);
	return 0;
}

//场景转换
void update()//场景更新。
{
	CVector oldpos=mycar.pos;
	if (gameManager->GameStatus == 1)
	{
		if (w == 1 || up == 1)
		{
			if (IsDebug)
				TPPCamera.CameraMove('w');
			else
			{
				if (mycar.speed < 0.1)
					mycar.speed += 0.0002;
			}
		}
		else if (s == 1 || down == 1)
		{
			if (IsDebug)
				TPPCamera.CameraMove('s');
			else
			{
				if (mycar.speed > -0.1)
					mycar.speed -= 0.0002;
			}
		}
		else
		{
			if (mycar.speed > 0)
				mycar.speed -= 0.0001;
			else if (mycar.speed < 0)
				mycar.speed += 0.0001;
		}

		if (k_left == 1 || a == 1)
		{
			if (IsDebug)
				TPPCamera.CameraMove('a');
			else
				mycar.TurnLeft();
			//printf("L:%f\n",mycar.Edir.h);
		}
		else if (k_right == 1 || d == 1)
		{
			if (IsDebug)
				TPPCamera.CameraMove('d');
			else
				mycar.TurnRight();
			//printf("R:%f\n",mycar.Edir.h);
		}
		else if (j == 1)
		{
			if (IsDebug)
				TPPCamera.CameraRotate('j');
		}
		else if (l == 1)
		{
			if (IsDebug)
				TPPCamera.CameraRotate('l');
		}
		else if (i == 1)
		{
			if (IsDebug)
				TPPCamera.CameraRotate('i');
		}
		else if (k == 1)
		{
			if (IsDebug)
				TPPCamera.CameraRotate('k');
		}
		if (e == 1)
		{
			if (IsDebug)
				TPPCamera.CameraMove('e');
		}
		if (q == 1)
		{
			if (IsDebug)
				TPPCamera.CameraMove('q');
		}
		if (!mycar.IsEnd)
		{
			mycar.Run();
			mycar.ReachEnd();
		}
		if (!npc1.IsEnd)
		{
			npc1.AutoRun();
			npc1.ReachEnd();
		}
		if (!npc2.IsEnd)
		{
			npc2.AutoRun();
			npc2.ReachEnd();
		}
		if (ImpactCheck(&npc1) == 1 || ImpactCheck(&npc2) == 1)
		{
			//mycar.pos=oldpos;
			return;
		}
		LoadImpactCheck();
		//gameManager->GetRank(Rank, mytrack.loads);
	}
}


void myTimerFunc(int val)
{
	gameManager = GameManager::GetInstance();
	g_angle+=0.1;
	update();
	myDisplay();
	mytime+=0.1;
	if (mytime>100)
		mytime = 50;
	glutTimerFunc(1,myTimerFunc,1);
}

//键盘响应
void myKeyboardFunc(unsigned char key,int x, int y)
{
	switch(key)
	{
	case ' ':
	{
		if (flag == 2)
		{
			flag--;
			mytime = -0.1;
		}
	}
	break;
	case 'w':
		w = 1;
		break;
	case 'a':
		a = 1;
		break;
	case 's':
		s = 1;
		break;
	case 'd':
		d = 1;
		break;
	case 'q':
		q = 1;
		break;
	case 'e':
		e = 1;
		break;
	case 'j':
		j = 1;
		break;
	case 'l':
		l = 1;
		break;
	case 'i':
		i = 1;
		break;
	case 'k':
		k = 1;
		break;
	}
}

//多键盘响应
void myKeyboardupFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		w = 0;
		break;
	case 'a':
		a = 0;
		break;
	case 's':
		s = 0;
		break;
	case 'd':
		d = 0;
		break;
	case 'q':
		q = 0;
		break;
	case 'e':
		e = 0;
		break;
	case 'j':
		j = 0;
		break;
	case 'l':
		l = 0;
		break;
	case 'i':
		i = 0;
		break;
	case 'k':
		k = 0;
		break;
	}
}

//四个方向按键
void mySpecialFunc(GLint key,GLint x,GLint y)
{
	if(key==GLUT_KEY_UP)
	{
		up=1;
	}	
	if(key==GLUT_KEY_LEFT)
	{
		k_left=1;
	}
	if(key==GLUT_KEY_DOWN)
	{
		down=1;
	}
	if(key==GLUT_KEY_RIGHT)
	{
		k_right=1;
	}
	if (key == GLUT_KEY_F12)
	{
		IsDebug = !IsDebug;
	}
}

void mySpecialUpFunc(GLint key,GLint x,GLint y)
{
	if(key==GLUT_KEY_UP)
	{
		up=0;
	}	
	if(key==GLUT_KEY_LEFT)
	{
		k_left=0;
	}
	if(key==GLUT_KEY_DOWN)
	{
		down=0;
	}
	if(key==GLUT_KEY_RIGHT)
	{
		k_right=0;
	}
}

void SetGameObject()
{
	mycar.pos.Set(475,510.3,472);
	npc1.intialRoad();
	npc1.pos.Set(474, 510, 473);
	npc2.intialRoad();
	npc2.pos.Set(476, 510, 471);
	npc1.car_CBV = CubeBoundingVolume(npc1.pos, 1, 5.0, 0.8, npc1.dir);
	npc2.car_CBV = CubeBoundingVolume(npc2.pos, 1, 5.0, 0.8, npc2.dir);
	mycar.car_CBV = CubeBoundingVolume(mycar.pos, 1, 5.0, 0.8, mycar.dir);
	mytrack = Track();
	Rank.push_back(mycar);
	Rank.push_back(npc1);
	Rank.push_back(npc2);
	//mycar.car_CBV.point_pos[0].print();
	//npc.car_CBV.point_pos[0].print();
}

//绘画
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if (flag)
		Write();
	if (gameManager->GameStatus == 2)
		WriteEnd();
	/*if (gameManager->GameStatus == 1)
		WriteRank();*/
	glPushMatrix();
	//glTranslatef(0,0,-25);
	//glRotatef(g_angle,0,1,0);
	/*glEnable (GL_LINE_SMOOTH);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);*/
	
	//gluLookAt(0.0,100.0,0.0,5,0,0,0.0,1.0,0.0);
	if (IsDebug)
		TPPCamera.SetDebugView();
	else if(gameManager->GameStatus!=0)
	{
		TPPCamera.SetThirdPerson(mycar.pos, mycar.dir);
		TPPCamera.SetView();
	}
	else
	{
		CVector tmp(0, 0, 1);
		TPPCamera.SetFrontDir(tmp);
		tmp.Set(475, 516, 458);
		TPPCamera.SetPos(tmp);
		TPPCamera.SetView();
	}
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);

	mycar.DrawPlayerCar();
	npc1.DrawNPCCar();
	npc2.DrawNPCCar2();
	//textureManager->DrawCar();
	textureManager->DrawSphere();
	textureManager->DrawGround();
	textureManager->SetRoad();
	textureManager->DrawBeginAndEnd();
	skybox.CreateSkyBox(0, 0, 0, 1, 1, 1);
	glPopMatrix();
	glutSwapBuffers();
}

void myReshape(int w,int h)
{	
	GLfloat nRange = 100.0f;
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60,GLfloat(w)/h,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void SetOpenGL()
{
	/** 用户自定义的初始化过程 */
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_FLAT);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	//glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	/** 设置光源的属性值 */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightAmbient);
	//glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);     /**< 设置环境光 */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);     /**< 设置漫射光 */
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);   /**< 设置漫射光 */

														/** 启用纹理 */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE_2D);
	textureManager->LoadTexture();
	//skybox.Init();
	//textureManager.LoadTexture();
	/*if (!textureManager.LoadTexture())
		printf("%d", 1);*/
	//if (!textureManager.t_skybox.Init())
	//{
	//	//MessageBox(NULL, (LPCWSTR)"初始化天空失败!", (LPCWSTR)"错误", MB_OK);
	//	exit(0);
	//}
}
int main(int argc, char *argv[])
{
	
	//srand((unsigned int) time(0));
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1400, 700);
    glutCreateWindow("赛车游戏");
	SetOpenGL();
    glutDisplayFunc(&myDisplay);
	glutTimerFunc(1,myTimerFunc,1);
	glutReshapeFunc(&myReshape);
	glutKeyboardFunc(&myKeyboardFunc);
	glutKeyboardUpFunc(&myKeyboardupFunc);
	glutSpecialFunc(&mySpecialFunc);
	glutSpecialUpFunc(&mySpecialUpFunc);
	SetGameObject();
    glutMainLoop();
    return 0;
}