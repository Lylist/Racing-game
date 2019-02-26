#pragma once
#include "OurMath.h"

#include <GL/glut.h>


class Camera
{
public:
	/*static Camera* getInstance()
	{
		if (cameraInstance == NULL)
		{
			cameraInstance = new Camera();
		}
		return cameraInstance;
	}*/
	Camera();
	void SetView();
	void SetDebugView();
	void SetThirdPerson(CVector carpos, CVector cardir);
	void SetFirstPerson(CVector carpos, CVector cardir);
	void SetUpdir(CVector);
	void SetFrontDir(CVector);
	void SetPos(CVector);
	void CameraMove(char dir);
	void CameraRotate(char dir);
private:
	//static Camera * cameraInstance;
	CVector pos;
	CVector upDir;
	CVector frontDir;
	
	float cameraSpeed;
};