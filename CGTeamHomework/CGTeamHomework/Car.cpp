#include "Car.h"
TextureManager * tm = TextureManager::GetInstance();

Car::Car(int id)
{
	CarID = id;
	pos = CVector(0, 0, 0);
	dir = CVector(1, 0, 0);
	dir.Normalize();
	speed = 0.000;
	now_load = 0;
	Edir = dir.ToEuler();
	IsEnd = false;
	isLerp = false;
	isFirst = true;
	lerpCnt = 0;
	CEuler temp;
	CVector updir;
	updir.Set(0, 1, 0);
	temp.Set(0.4, 0, 0);
	Car::Edir.h = Car::Edir.h + temp.h;
	Car::dir = Car::Edir.ToVector3(&updir);
	angle = 0;
}
Car::Car(int id,float s)
{
	CarID = id;
	pos = CVector(0, 0, 0);
	dir = CVector(0, 0, 1);
	dir.Normalize();
	max_speed = s;
	speed = s;
	now_load = 0;
	Edir = dir.ToEuler();
	IsEnd = false;
	isLerp = false;
	isFirst = true;
	lerpCnt = 0;
	angle = 0;
}
void Car::DrawPlayerCar()
{
	float size = 0.3;
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	//glRotatef(180, 0, 1, 0);
	glRotated(Edir.h, 0, 1, 0);
	glTranslatef(-pos.x, -pos.y, -pos.z);
	glEnable(GL_COLOR_MATERIAL);
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(pos.x, pos.y + 0.6*size, pos.z - 1.03*size);
	
	glRotatef(30, 1, 0, 0);
	glScaled(1.99, 1, 0.5);
	glutSolidCube(size);
	glPopMatrix();
	//轮子
	for (int i = 0; i<180; i++)
	{
		//glEnable( GL_COLOR_MATERIAL );
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(0, 0, 0);

		glPushMatrix();
		glTranslatef(pos.x - size, pos.y - 0.4*size, pos.z + 1.5*size);
		glRotatef(i, 1, 0, 0);
		glRotated(speed * angle * 100, 1, 0, 0);
		glScaled(0.2, 0.8, 0.01);
		glutSolidCube(size);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(pos.x + size, pos.y - 0.4*size, pos.z + 1.5*size);
		glRotatef(i, 1, 0, 0);
		glRotated(speed * angle * 100, 1, 0, 0);
		glScaled(0.2, 0.8, 0.01);
		glutSolidCube(size);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(pos.x - size, pos.y - 0.4*size, pos.z - 1.5*size);
		glRotatef(i, 1, 0, 0);
		glRotated(speed * angle * 100, 1, 0, 0);
		glScaled(0.2, 0.8, 0.01);
		glutSolidCube(size);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(pos.x + size, pos.y - 0.4*size, pos.z - 1.5*size);
		glRotatef(i, 1, 0, 0);
		glRotated(speed * angle * 100, 1, 0, 0);
		glScaled(0.2, 0.8, 0.01);
		glutSolidCube(size);
		glPopMatrix();
	}
	angle++;
	glColor3f(1.0, 1.0, 1.0);
	glDisable(GL_COLOR_MATERIAL);

	/** 设置材质属性 */
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//车身
	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	//glRotated(Edir.h, 0, 1, 0);
	glScalef(size, 0.4*size, 2.5*size);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D, tm->m_Texture[5].ID);
	/** 开始绘制车身 */
	glBegin(GL_QUADS);
	/// 左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	/// 右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tm->m_Texture[7].ID);

	glBegin(GL_QUADS);
	/// 后面
	glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tm->m_Texture[6].ID);

	glBegin(GL_QUADS);
	/// 前面
	glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, tm->m_Texture[9].ID);

	glBegin(GL_QUADS);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();
	glPopMatrix();


	//车顶
	glPushMatrix();
	glTranslatef(pos.x, pos.y + 0.8*size, pos.z);
	//glRotated(Edir.h, 0, 1, 0);
	glScalef(size, 0.4*size, size);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D,tm-> m_Texture[14].ID);
	/** 开始绘制车身 */
	glBegin(GL_QUADS);
	/// 左侧面
	glNormal3f(-1.0f, 0.0f, 0.0f);                              /**< 指定法线朝左 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	/// 右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tm-> m_Texture[15].ID);

	glBegin(GL_QUADS);
	/// 右侧面
	glNormal3f(1.0f, 0.0f, 0.0f);                               /**< 指定法线朝右 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tm-> m_Texture[12].ID);

	glBegin(GL_QUADS);
	/// 顶面
	glNormal3f(0.0f, 1.0f, 0.0f);                               /**< 指定法线向上 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tm-> m_Texture[13].ID);

	glBegin(GL_QUADS);
	/// 前侧面
	glNormal3f(0.0f, 0.0f, 1.0f);                               /**< 指定法线指向观察者 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();
	glPopMatrix();

	/**玻璃**/
	glPushMatrix();
	glTranslatef(pos.x, pos.y + 0.6*size, pos.z - 1.1*size);
	glRotatef(30, 1, 0, 0);
	//glRotated(Edir.h, 0, 1, 0);
	glScaled(1.7 / 2 * size, 0.9 / 2 * size, 0.2*size);
	/** 选择纹理 */
	glBindTexture(GL_TEXTURE_2D,tm-> m_Texture[8].ID);
	/** 开始绘制车身 */
	glBegin(GL_QUADS);
	/// 前面
	glNormal3f(0.0f, 0.0f, -1.0f);                              /**< 指定法线背向观察者 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	/**启用颜色**/
	//glEnable( GL_COLOR_MATERIAL );
	//glColor3f(1, 0, 0);

	//前车窗
	/*for (float i = 0; i < 10; i ++)
	{
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(x, y+(0.4+0.4/20+0.8/10*i)*size, z-size);
	glScaled(2, 0.08, 0.1*(10-i));
	glutSolidCube(size);
	glPopMatrix();
	}*/



	/*if (tp)
	glEnable(GL_TEXTURE_2D);*/
	glPopMatrix();
}

void Car::DrawNPCCar()
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


	float size = 0.6;

	float x, y, z;
	x = pos.x;
	y = pos.y + 0.5*size;
	z = pos.z;

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotated(Edir.h, 0, 1, 0);
	glTranslatef(-x, -y, -z);

	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//车身
	glColor3f(1, 0, 0);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(2, 0.4, 1);
	glutSolidCube(size);
	glPopMatrix();

	//车顶
	for (float i = 0; i < 0.9; i += 0.05)
	{
		glColor3f(1, 0, 0);
		glPushMatrix();
		glTranslatef(x, y + 0.54*size - i * size, z);
		glScaled(1.1 + i / 3, 0.05, 0.69);
		glutSolidCube(size);
		glPopMatrix();
	}

	//侧边车窗1
	for (float i = 0; i < 0.5; i += 0.03)
	{
		glColor3f(0.8, 0.8, 1);
		glPushMatrix();
		glTranslatef(x, y + 0.5*size - i * size, z + 0.402*size);
		glScaled(0.6 + i / 3, 0.05, 0);
		glutSolidCube(size);
		glPopMatrix();
	}
	glColor3f(0.98, 0.27, 0.27);
	glPushMatrix();
	glTranslatef(x, y + 0.37*size, z + 0.404*size);
	glScaled(0.1, 0.32, 0);
	glutSolidCube(size);
	glPopMatrix();

	//侧边车窗2
	for (float i = 0; i < 0.5; i += 0.03)
	{
		glColor3f(0.8, 0.8, 1);
		glPushMatrix();
		glTranslatef(x, y + 0.5*size - i * size, z - 0.402*size);
		glScaled(0.6 + i / 3, 0.05, 0);
		glutSolidCube(size);
		glPopMatrix();
	}
	glColor3f(0.98, 0.27, 0.27);
	glPushMatrix();
	glTranslatef(x, y + 0.37*size, z - 0.404*size);
	glScaled(0.1, 0.32, 0);
	glutSolidCube(size);
	glPopMatrix();

	//前车窗
	for (float i = 0; i < 0.75; i += 0.05)
	{
		glColor3f(0.8, 0.8, 1);
		glPushMatrix();
		glTranslatef(x - 0.48*size - i * 0.35*size, y + 0.5*size - i, z);
		glScaled(0.25, 0.05, 0.6);
		glutSolidCube(size);
		glPopMatrix();
	}


	//前右轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x - 0.53*size, y - 0.24*size, z - 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	//后右轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x + 0.53*size, y - 0.24*size, z - 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	//前左轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x - 0.53*size, y - 0.24*size, z + 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	//后左轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x + 0.53*size, y - 0.24*size, z + 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	angle++;
	glPopMatrix();
	/** 恢复状态 */
	if (tp)
		glEnable(GL_TEXTURE_2D);
}
void Car::DrawNPCCar2()
{
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


	float size = 0.6;

	float x, y, z;
	x = pos.x;
	y = pos.y + 0.5*size;
	z = pos.z;

	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(Edir.h, 0, 1, 0);
	glTranslatef(-x, -y, -z);

	glEnable(GL_COLOR_MATERIAL);
	glLightModeli(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//车身
	glColor3f(1, 1, 0);
	glPushMatrix();
	glTranslatef(x, y, z);
	glScalef(2, 0.4, 1);
	glutSolidCube(size);
	glPopMatrix();

	//车顶
	for (float i = 0; i < 0.9; i += 0.05)
	{
		glColor3f(1, 1, 0);
		glPushMatrix();
		glTranslatef(x, y + 0.54*size - i * size, z);
		glScaled(1.1 + i / 3, 0.05, 0.69);
		glutSolidCube(size);
		glPopMatrix();
	}

	//侧边车窗1
	for (float i = 0; i < 0.5; i += 0.03)
	{
		glColor3f(0.8, 0.8, 1);
		glPushMatrix();
		glTranslatef(x, y + 0.5*size - i * size, z + 0.402*size);
		glScaled(0.6 + i / 3, 0.05, 0);
		glutSolidCube(size);
		glPopMatrix();
	}
	glColor3f(0.98, 0.98, 0.27);
	glPushMatrix();
	glTranslatef(x, y + 0.37*size, z + 0.404*size);
	glScaled(0.1, 0.32, 0);
	glutSolidCube(size);
	glPopMatrix();

	//侧边车窗2
	for (float i = 0; i < 0.5; i += 0.03)
	{
		glColor3f(0.8, 0.8, 1);
		glPushMatrix();
		glTranslatef(x, y + 0.5*size - i * size, z - 0.402*size);
		glScaled(0.6 + i / 3, 0.05, 0);
		glutSolidCube(size);
		glPopMatrix();
	}
	glColor3f(0.98, 0.98, 0.27);
	glPushMatrix();
	glTranslatef(x, y + 0.37*size, z - 0.404*size);
	glScaled(0.1, 0.32, 0);
	glutSolidCube(size);
	glPopMatrix();

	//前车窗
	for (float i = 0; i < 0.75; i += 0.05)
	{
		glColor3f(0.8, 0.8, 1);
		glPushMatrix();
		glTranslatef(x - 0.48*size - i * 0.35*size, y + 0.5*size - i, z);
		glScaled(0.25, 0.05, 0.6);
		glutSolidCube(size);
		glPopMatrix();
	}


	//前右轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x - 0.53*size, y - 0.24*size, z - 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	//后右轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x + 0.53*size, y - 0.24*size, z - 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	//前左轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x - 0.53*size, y - 0.24*size, z + 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	//后左轮
	for (int i = 0; i<180; i++)
	{
		if (i / 20 % 2 == 0)
			glColor3f(0.5, 0.5, 0.5);
		else glColor3f(1, 1, 1);
		glPushMatrix();
		glTranslatef(x + 0.53*size, y - 0.24*size, z + 0.43*size);
		glRotatef(i, 0, 0, 1);
		glRotated(-speed * angle * 360, 0, 0, 1);
		glScaled(0.01, 0.48, 0.2);
		glutSolidCube(size);
		glPopMatrix();
	}
	angle++;
	glPopMatrix();
	/** 恢复状态 */
	if (tp)
		glEnable(GL_TEXTURE_2D);
}



void Car::intialRoad()
{
	Road temp;
	/*temp.target.Set(475, 510, 473);
	temp.last.Set(-1, -1, -1);
	temp.next.Set(-1, -1, -1);
	Car::myroad.push_back(temp);*/

	temp.target.Set(475, 510, 553);
	temp.last.Set(475, 510, 549);
	temp.next.Set(479, 510, 553);
	Car::myroad.push_back(temp);

	temp.last.Set(547, 510, 553);
	temp.target.Set(551, 510, 553);
	temp.next.Set(551, 510, 549);
	Car::myroad.push_back(temp);

	temp.last.Set(551, 510, 541);
	temp.target.Set(551, 510, 537);
	temp.next.Set(547, 510, 537);
	Car::myroad.push_back(temp);

	temp.last.Set(487, 510, 537);
	temp.target.Set(483, 510, 537);
	temp.next.Set(483, 510, 553);
	Car::myroad.push_back(temp);

	temp.last.Set(483, 510, 525);
	temp.target.Set(483, 510, 521);
	temp.next.Set(487, 510, 521);
	Car::myroad.push_back(temp);

	temp.last.Set(547, 510, 521);
	temp.target.Set(551, 510, 521);
	temp.next.Set(551, 510, 517);
	Car::myroad.push_back(temp);

	temp.last.Set(551, 510, 509);
	temp.target.Set(551, 510, 505);
	temp.next.Set(547, 510, 505);
	Car::myroad.push_back(temp);

	temp.last.Set(487, 510, 505);
	temp.target.Set(483, 510, 505);
	temp.next.Set(483, 510, 501);
	Car::myroad.push_back(temp);

	temp.last.Set(483, 510, 493);
	temp.target.Set(483, 510, 489);
	temp.next.Set(487, 510, 489);
	Car::myroad.push_back(temp);

	temp.target.Set(556, 510, 489);
	temp.last.Set(-1, -1, -1);
	temp.next.Set(-1, -1, -1);
	Car::myroad.push_back(temp);
}

int Car::Run()
{
	float length = fabs(speed);
	int mdir = 1;
	if (speed > 0)
	{
		mdir = 1;
	}
	else
	{
		mdir = -1;
	}
	
	if (mdir == 1)
		pos = pos + dir * length;
	else
		pos = pos + dir * (-length);
	dir.Normalize();
	
	car_CBV.setpos(pos, dir);
	
	return 1;
}


void Car::AutoRun()
{
	if (isLerp)
	{
		if (isFirst)
		{
			CQuaternion QNow, QNext;
			float lerpPara[105];
			float para = 0;
			for (int p = 0; p <= 50; p++)
			{
				lerpPara[p] = para;
				para += 0.02;
			}
			QNow = dir.ToEuler().ToQuaternion();
			QNext = nextdir.ToEuler().ToQuaternion();
			QNow.Slerp(QNext, 51, lerpPara, turnLerp);
			isFirst = false;
			/*	cout << "nowcardir:" << nowcardir << endl;
			cout << "nextcardir:" << nextcardir << endl;
			cout << "QNow:" << QNow.ToEuler().ToVector3() << endl;
			cout << "QNext:" << QNext.ToEuler().ToVector3() << endl;*/
		}

		if (lerpCnt == 50)
		{
			isLerp = false;
			isFirst = true;
			lerpCnt = 0;
			
		}
		Edir.h = -turnLerp[lerpCnt].ToEuler().h;
		lerpCnt++;
	}
	else
	{
		dir = myroad[0].target - pos;
		if ((myroad[0].target - pos).len() <= 1)
		{
			if (myroad.size() > 1)
				myroad.erase(myroad.begin());
			nextdir = myroad[0].target - pos;
			nextdir.Normalize();
			dir.Normalize();
			isLerp = true;
		}
			//Car::slerp(Car::dir, nextdir);
		dir.Normalize();
		Edir = dir.ToEuler();
		Run();
	}
	if (fabs(speed) < EPS) speed = max_speed;
	else if (speed - max_speed < EPS) speed += 0.0001;
	else if (speed - max_speed > EPS) speed -= 0.0001;
}

void Car::ReachEnd()
{
	GameManager * gm = GameManager::GetInstance();
	//CVector end(475, 510, 553);
	CVector end(556, 510, 489);
	if ((pos - end).len() < 3)
	{
		IsEnd = true;
		gm->gamecount++;
		if (CarID == 1)
		{
			gm->GameStatus = 2;
		}
	}
}


int Car::TurnLeft()
{
	CEuler temp;
	CVector updir;
	updir.Set(0, 1, 0);
	temp.Set(0.8, 0, 0);
	Car::Edir.h = Car::Edir.h + temp.h;
	Car::dir = Car::Edir.ToVector3(&updir);
	return 1;
}

int Car::TurnRight()
{
	CEuler temp;
	CVector updir;
	updir.Set(0, 1, 0);
	temp.Set(-0.8, 0, 0);
	Car::Edir.h = Car::Edir.h + temp.h;
	Car::dir = Car::Edir.ToVector3(&updir);
	return 1;
}