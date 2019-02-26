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
	/** 删除纹理对象及其占用的内存 */
	for (int i = 0; i< 6; i++)
	{
		//m_texture[i].FreeImage();
		//glDeleteTextures(1, &m_texture[i].ID);
	}
}

/** 构造天空盒 */
void  Skybox::CreateSkyBox(float x, float y, float z,
	float box_width, float box_height,
	float box_length)
{
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);
	/** 计算天空盒长 宽 高 */
	float width = MAP * box_width / 8;
	float height = MAP * box_height / 8;
	float length = MAP * box_length / 8;

	/** 计算天空盒中心位置 */
	x = x + MAP / 8 - width / 2;
	y = y + MAP / 24 - height / 2;
	z = z + MAP / 8 - length / 2;

	glDisable(GL_LIGHTING);            /**< 关闭光照 */
									   /** 开始绘制 */
	glPushMatrix();
	glTranslatef(-x, -y, -z);

	/** 绘制背面 */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[17].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** 绘制前面 */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[16].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);

	glEnd();

	/** 绘制底面 */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[18].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);

	glEnd();

	/** 绘制顶面 */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[19].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);

	glEnd();

	/** 绘制左面 */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[21].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);

	glEnd();

	/** 绘制右面 */
	glBindTexture(GL_TEXTURE_2D, tm2->m_Texture[20].ID);

	glBegin(GL_QUADS);

	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	glPopMatrix();                 /** 绘制结束 */

	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);

}
