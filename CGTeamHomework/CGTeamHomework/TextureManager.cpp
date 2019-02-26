#include "TextureManager.h"


TextureManager::TextureManager()
{
	ox = 515, oy = 515, oz = 515;
	road_x = 475, road_y = 510, road_z = 473;
}


TextureManager::~TextureManager()
{
	delete instance;
}

TextureManager* TextureManager::instance = new TextureManager();
TextureManager* TextureManager::GetInstance()
{
	if (instance == NULL)
	{
		instance = new TextureManager();
	}
	return instance;
}

bool TextureManager::LoadTexture()
{
	char filename[128];                                         /**< 用来保存文件名 */
	const char *bmpName[] = { "image","timg","road","road_change","begin","car_left","car_front","car_back","car_window","car_top","start",
		"end","car_roof","car_roof_back","car_win_left","car_win_right","back","front","bottom","top","left","right" };

	for (int i = 0; i< 22; i++)
	{
		sprintf(filename, "%s", bmpName[i]);
		strcat(filename, ".bmp");
		if (!m_Texture[i].LoadBitmap(filename))                     /**< 载入位图文件 */
		{
			printf("%s\n", filename);
			//MessageBox(NULL, (LPCWSTR)"装载位图文件失败！", (LPCWSTR)"错误", MB_OK);    /**< 如果载入失败则弹出对话框 */
			exit(0);
		}
		glGenTextures(1, &m_Texture[i].ID);                        /**< 生成一个纹理对象名称 */

		glBindTexture(GL_TEXTURE_2D, m_Texture[i].ID);             /**< 创建纹理对象 */


																   /** 控制滤波: */
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// Linear Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// Linear Filteringd

																			//wrap参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);*/



		/** 创建纹理 */
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, m_Texture[i].imageWidth,
			m_Texture[i].imageHeight, GL_RGB, GL_UNSIGNED_BYTE,
			m_Texture[i].image);
	}
	return true;
}

void TextureManager::DrawGround()
{

	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();
	glTranslatef(ox, oy - 5.01, oz);
	glScalef(50.0f, 0.01f, 50.0f);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D, m_Texture[1].ID);
	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();
}

void TextureManager::SetRoad()
{
	road_x = 475;
	road_y = 510;
	road_z = 473;
	/**DrawRoad(41,1),x负方向到z正方向的拐角**/
	/** 设置材质属性 */
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();
	glTranslatef(road_x, road_y, road_z);
	glScalef(2.0f, 0.01f, 2.0f);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D, m_Texture[10].ID);
	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();

	DrawRoad(1, 19);
	DrawRoad(13, 1);
	DrawRoad(3, 18);
	DrawRoad(32, 1);
	DrawRoad(2, 3);
	DrawRoad(24, 1);
	DrawRoad(4, 16);
	DrawRoad(42, 1);
	DrawRoad(2, 3);
	DrawRoad(23, 1);
	DrawRoad(3, 16);
	DrawRoad(32, 1);
	DrawRoad(2, 3);
	DrawRoad(24, 1);
	DrawRoad(4, 16);
	DrawRoad(42, 1);
	DrawRoad(2, 3);
	DrawRoad(23, 1);
	DrawRoad(3, 17);

	glPushMatrix();
	glTranslatef(road_x + 4, road_y, road_z);
	glScalef(2.0f, 0.01f, 2.0f);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D, m_Texture[11].ID);
	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();
}

void TextureManager::DrawRoad(int dir, int length)
{
	/** 设置材质属性 */
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	/** dir=1,z轴正方向，dir=2,z轴负方向，dir=3,x轴正方向，dir=4,x轴负方向 **/
	/**赛道**/
	for (int i = 1; i <= length; i++)
	{
		glPushMatrix();
		if (dir == 1 || dir == 13 || dir == 14)
			road_z += 4;
		else if (dir == 2 || dir == 23 || dir == 24)
			road_z -= 4;
		else if (dir == 3 || dir == 31 || dir == 32)
			road_x += 4;
		else if (dir == 4 || dir == 41 || dir == 42)
			road_x -= 4;
		glTranslatef(road_x, road_y, road_z);
		if (dir == 3 || dir == 4)
			glRotatef(90, 0, 1, 0);
		if (dir == 14 || dir == 32)
			glRotatef(180, 0, 1, 0);
		if (dir == 13 || dir == 42)
			glRotatef(90, 0, 1, 0);
		if (dir == 41 || dir == 23)
			glRotatef(0, 0, 1, 0);
		if (dir == 31 || dir == 24)
			glRotatef(-90, 0, 1, 0);
		glScalef(2.0f, 0.01f, 2.0f);

		/** 选择纹理 */
		if (dir <= 4)
			glBindTexture(GL_TEXTURE_2D, m_Texture[2].ID);
		else
			glBindTexture(GL_TEXTURE_2D, m_Texture[3].ID);

		/** 开始绘制四边形 */
		glBegin(GL_QUADS);
		/// 顶面
		glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
		glEnd();
		glPopMatrix();
	}
}

void TextureManager::DrawBeginAndEnd()
{
	/** 设置材质属性 */
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	glPushMatrix();
	glTranslatef(475, 521, 477);
	glScalef(8.0f, 3.3f, 0.2f);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D, m_Texture[4].ID);
	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 后侧面
	glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(471, 514, 477);
	glScaled(0.4, 8, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(479, 514, 477);
	glScaled(0.4, 8, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	/*glPushMatrix();
	glTranslatef(475, 518, 477);
	glScaled(8, 4, 0.1);
	glutSolidCube(1);
	glPopMatrix();*/

	glPushMatrix();
	glTranslatef(553, 521, 489);
	glScalef(0.2f, 3.3f, 8.0f);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D, m_Texture[4].ID);
	/** 开始绘制四边形 */
	glBegin(GL_QUADS);
	/// 左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(553, 514, 485);
	glScaled(0.4, 8, 0.4);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(553, 514, 493);
	glScaled(0.4, 8, 0.4);
	glutSolidCube(1);
	glPopMatrix();

}

void TextureManager::DrawSphere()
{
	/** 设置材质属性 */
	GLfloat mat_ambient[] = { 0.9f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.9f, 0.5f, 0.8f, 1.0f };
	GLfloat mat_shininess[] = { 100.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	/** 获得纹理启用状态 */
	GLboolean tp;
	glGetBooleanv(GL_TEXTURE_2D, &tp);
	glDisable(GL_TEXTURE_2D);                   /**< 关闭纹理 */


												/** 绘制过程 */
	glPushMatrix();
	glTranslatef(ox, oy + 50, oz);
	GLUquadricObj * sphere = gluNewQuadric();
	gluQuadricOrientation(sphere, GLU_OUTSIDE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
	gluSphere(sphere, 2.0, 50, 50);
	gluDeleteQuadric(sphere);
	glPopMatrix();

	/** 恢复状态 */
	if (tp)
		glEnable(GL_TEXTURE_2D);
}
