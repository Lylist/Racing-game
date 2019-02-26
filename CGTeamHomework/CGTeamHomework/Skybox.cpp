#include "Skybox.h"

const unsigned int MAP_WIDTH = 1024;
const unsigned int CELL_WIDTH = 16;
const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;

TextureManager * tm2 = TextureManager::GetInstance();

Skybox::Skybox()
{
	
}


Skybox::~Skybox()
{
	/** ɾ�����������ռ�õ��ڴ� */
	for (int i = 0; i< 6; i++)
	{
		//m_texture[i].FreeImage();
		//glDeleteTextures(1, &m_texture[i].ID);
	}
}

/** ������պ� */
void  Skybox::CreateSkyBox(float x, float y, float z,
	float box_width, float box_height,
	float box_length)
{
	/** ��ó����й���״̬ */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);
	/** ������պг� �� �� */
	float width = MAP * box_width / 8;
	float height = MAP * box_height / 8;
	float length = MAP * box_length / 8;

	/** ������պ�����λ�� */
	x = x + MAP / 8 - width / 2;
	y = y + MAP / 24 - height / 2;
	z = z + MAP / 8 - length / 2;

	glDisable(GL_LIGHTING);            /**< �رչ��� */
									   /** ��ʼ���� */
	glPushMatrix();
	glTranslatef(-x, -y, -z);

	/** ���Ʊ��� */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[17].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** ����ǰ�� */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[16].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);

	glEnd();

	/** ���Ƶ��� */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[18].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);

	glEnd();

	/** ���ƶ��� */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[19].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[21].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** �������� */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[20].ID);

	glBegin(GL_QUADS);

	/** ָ����������Ͷ������� */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();                 /** ���ƽ��� */

	if (lp)                         /** �ָ�����״̬ */
		glEnable(GL_LIGHTING);

}
