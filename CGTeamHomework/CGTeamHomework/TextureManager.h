#pragma once
#include "CBMPLoader.h"
#include <cstdio>
#include <gl/glut.h>
#include <gl/GLAux.h>

class TextureManager
{
public:
	static TextureManager * GetInstance();
	bool LoadTexture();
	void DrawGround();
	void DrawBeginAndEnd();
	void SetRoad();
	void DrawSphere();
	void DrawRoad(int dir, int length);
	CBMPLoader m_Texture[30];
private:
	TextureManager();
	~TextureManager();
	float ox, oy, oz;
	int road_x, road_y, road_z;
	static TextureManager * instance;
};

