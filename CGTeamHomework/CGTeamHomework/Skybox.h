#pragma once
#include "OurMath.h"
#include "TextureManager.h"
#include <gl/glut.h>

#define GL_CLAMP_TO_EDGE    0x812F
class Skybox
{
public:
	Skybox();
	~Skybox();

	/** äÖÈ¾Ìì¿Õ */
	void  CreateSkyBox(float x, float y, float z,
		float width, float height,
		float length);

private:

	//CBMPLoader  m_texture[6];   /**< Ìì¿ÕºÐÎÆÀí */
};

