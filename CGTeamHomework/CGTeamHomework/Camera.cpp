#include "Camera.h"

Camera::Camera()
{
	upDir.Set(0, 1, 0);
	cameraSpeed = 0.1;
}

void Camera::SetView()
{
	gluLookAt(pos.x, pos.y, pos.z, pos.x + frontDir.x, pos.y + frontDir.y, pos.z + frontDir.z, upDir.x, upDir.y, upDir.z);
}

void Camera::SetDebugView()
{
	frontDir.Set(0, 0, -1);
	upDir.Set(0, 1, 0);
	gluLookAt(pos.x, pos.y, pos.z, pos.x + frontDir.x, pos.y + frontDir.y, pos.z + frontDir.z, upDir.x, upDir.y, upDir.z);
}

void Camera::SetThirdPerson(CVector carpos,CVector cardir)
{
	carpos.Set(carpos.x, carpos.y + 2, carpos.z);
	frontDir = cardir;
	pos = carpos + (frontDir*-7);
}

void Camera::SetFirstPerson(CVector carpos, CVector cardir)
{
	pos = carpos;
	frontDir = cardir;
}

void Camera::SetUpdir(CVector dir)
{
	upDir = dir;
}

void Camera::SetFrontDir(CVector dir)
{
	frontDir = dir;
}

void Camera::SetPos(CVector p)
{
	pos = p;
}

void Camera::CameraMove(char dir)
{
	switch (dir)
	{
	case 'w':
		pos = pos + frontDir * cameraSpeed;
		break;
	case 's':
		pos = pos + frontDir * -cameraSpeed;
		break;
	case 'a':
		pos = pos + frontDir.crossMul(upDir)*-cameraSpeed;
		break;
	case 'd':
		pos = pos + frontDir.crossMul(upDir)*cameraSpeed;
		break;
	case 'q':
		pos = pos + upDir * cameraSpeed;
		break;
	case 'e':
		pos = pos + upDir * -cameraSpeed;
		break;
	default:
		break;
	}
}


void Camera::CameraRotate(char dir)
{
	CVector vec1;
	vec1 = frontDir.crossMul(upDir);
	vec1.Normalize();
	//vec1 = vec1 * 0.01;
	CVector vec2;
	vec2 = upDir.getNormolization();
	vec2.Normalize();
	//vec2 = vec2 * 0.01;
	switch (dir)
	{
	case 'j':
		frontDir = frontDir + vec1;
		break;
	case 'l':
		frontDir = frontDir - vec1;
		break;
	case 'i':
		frontDir = frontDir + vec2;
		break;
	case 'k':
		frontDir = frontDir + vec2;
		break;
	default:
		break;
	}
}
