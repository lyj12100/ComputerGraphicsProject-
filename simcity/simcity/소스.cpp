#include<gl/freeglut.h>
#include<stdio.h>

void DrawScene();
void Reshape(int, int);
void Keyboard(unsigned char, int, int);

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
void setTexture(int);

//좌표변수
float rotateX, rotateY, rotateZ = 0;
int moveR, moveL, moveU, moveD, moveFront, moveBack = 0;
float standardY = -200;

GLUquadricObj *p = gluNewQuadric();

GLuint textureObject[3];
GLubyte *pBytes;
BITMAPINFO *info;

//일반변수
int craneMove;

//객체함수

//조명
void initLight()
{
	GLfloat ambientLight[] = { 0.6,0.6,0.6,1.0 };
	GLfloat diffuseLight[] = { 0.5,0.5,1,0.5,1.0 };
	GLfloat specularLight[] = { 0.3,0.3,0.3,1.0 };
	GLfloat lightPos[] = { -200.0,400.0,300.0,1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

//텍스처 기본
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	if ((*info = (BITMAPINFO*)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0*abs((*info)->bmiHeader.biHeight);
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

void BaseGround()
{
	float gray[] = { 0.3,0.3,0.3,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	glBegin(GL_POLYGON);
	glVertex3f(-500, standardY, -500);
	glVertex3f(500, standardY, -500);
	glVertex3f(500, standardY, 500);
	glVertex3f(-500, standardY, 500);
	glEnd();
}

void Road()
{
	//아스팔트
	glPushMatrix();
	float black[] = { 0.1,0.1,0.1,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_POLYGON);
		glVertex3f(-500, standardY + 0.2, i + 10);
		glVertex3f(500, standardY + 0.2, i + 10);
		glVertex3f(500, standardY + 0.2, i - 10);
		glVertex3f(-500, standardY + 0.2, i - 10);
		glEnd();
	}
	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_POLYGON);
		glVertex3f(i - 10, standardY + 0.2, 500);
		glVertex3f(i + 10, standardY + 0.2, 500);
		glVertex3f(i + 10, standardY + 0.2, -500);
		glVertex3f(i - 10, standardY + 0.2, -500);
		glEnd();
	}
	glPopMatrix();

	//중앙선
	glPushMatrix();
	float yellow[] = { 1.0,1.0,0,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);
	glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);

	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_LINES);
		glVertex3f(-500, standardY + 0.3, i);
		glVertex3f(500, standardY + 0.3, i);
		glEnd();
	}
	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_LINES);
		glVertex3f(i, standardY + 0.3, -500);
		glVertex3f(i, standardY + 0.3, 500);
		glEnd();
	}
}

void block11()
{

	float blue[] = { 0.4,0.4,0.8,1.0 };
	float white[] = { 1,1,1,1 };
	float red[] = { 0.8,0.3,0.3,1.0 };

	glEnable(GL_NORMALIZE);
	glNormal3f(0, 1, 0);

	//제일 작은 건물

	glMaterialfv(GL_FRONT, GL_AMBIENT, red);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);

	//glPushMatrix();
	//glTranslatef(80, -50, 80);
	//glScalef(100, 300, 100);

	//glutSolidCube(1);
	//glPopMatrix();

	glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, textureObject[0]);
	glBegin(GL_QUADS);
	//glNormal3f(1, 0, 0);
	//glTexCoord2f(0, 0);
	glVertex3f(30, standardY, 30);
	//glTexCoord2f(0, 1);
	glVertex3f(30, standardY + 300, 30);
	//glTexCoord2f(1, 1);
	glVertex3f(130, standardY + 300, 30);
	//glTexCoord2f(1, 0);
	glVertex3f(130, standardY, 30);

	//glTexCoord2f(0, 0);
	glVertex3f(130, standardY, 30);
	//glTexCoord2f(0, 1);
	glVertex3f(130, standardY + 300, 30);
	//glTexCoord2f(1, 1);
	glVertex3f(130, standardY + 300, 130);
	//glTexCoord2f(1, 0);
	glVertex3f(130, standardY, 130);

	//glTexCoord2f(0, 0);
	glVertex3f(130, standardY, 130);
	//glTexCoord2f(0, 1);
	glVertex3f(130, standardY + 300, 130);
	//glTexCoord2f(1, 1);
	glVertex3f(30, standardY + 300, 130);
	//glTexCoord2f(1, 0);
	glVertex3f(30, standardY, 130);

	//glTexCoord2f(0, 0);
	glVertex3f(30, standardY, 130);
	//glTexCoord2f(0, 1);
	glVertex3f(30, standardY + 300, 130);
	//glTexCoord2f(1, 1);
	glVertex3f(30, standardY + 300, 30);
	//glTexCoord2f(1, 0);
	glVertex3f(30, standardY, 30);

	glEnd();

	glBegin(GL_QUAD_STRIP);
	//glNormal3f(0, 1, 0);
	glVertex3f(30, 100, 30);
	glVertex3f(130, 100, 30);
	glVertex3f(30, 150, 130);
	glVertex3f(130, 150, 130);
	glVertex3f(30, 100, 130);
	glVertex3f(130, 100, 130);
	glEnd();

	glPopMatrix();
	//glPopMatrix();

	//------------------------------
	//중간건물--------------
	glPushMatrix();

	glMaterialfv(GL_FRONT, GL_AMBIENT, blue);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);

	//glColor3f(0.5, 0.5, 0.8);
	glTranslatef(80, -50, 200);
	glScalef(100, 400, 100);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	//glColor3f(1, 1, 0);
	glVertex3f(30, 150, 150);
	glVertex3f(30, 150, 250);
	glVertex3f(130, 200, 150);
	glVertex3f(130, 200, 250);
	glVertex3f(130, 150, 150);
	glVertex3f(130, 150, 250);
	glEnd();
	glPopMatrix();

	//큰건물--------------------
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0.8);
	glTranslatef(200, -50, 200);
	glScalef(100, 500, 100);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	//glColor3f(1, 1, 0);
	glVertex3f(150, 200, 250);
	glVertex3f(250, 200, 250);
	glVertex3f(150, 250, 150);
	glVertex3f(250, 250, 150);
	glVertex3f(150, 200, 150);
	glVertex3f(250, 200, 150);
	glEnd();
	glPopMatrix();

	//제일 큰건물--------------
	glPushMatrix();
	//glColor3f(0.5, 0.5, 0.8);
	glTranslatef(200, -50, 80);
	glScalef(100, 600, 100);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glBegin(GL_QUAD_STRIP);
	//glColor3f(1, 1, 0);
	glVertex3f(250, 250, 30);
	glVertex3f(250, 250, 130);
	glVertex3f(150, 300, 30);
	glVertex3f(150, 300, 130);
	glVertex3f(150, 250, 30);
	glVertex3f(150, 250, 130);
	glEnd();
	glPopMatrix();

}

void block10()
{
	/*-----공원-----*/
	//잔디
	float grass[] = { 0.1,1,0.1,1,1 };
	float treeBody[] = { 0.3,0.2,0.2,1 };
	float treeLeaf[] = { 0,0.2,0 ,1 };
	float crane[] = { 0.8,0.8,0,1 };
	float black[] = { 0.3,0.3,0.3,1 };

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, grass);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grass);
	glMaterialfv(GL_FRONT, GL_SPECULAR, grass);

	glBegin(GL_POLYGON);
	glVertex3f(-190, standardY + 0.1, 160);
	glVertex3f(-70, standardY + 0.1, 160);
	glVertex3f(-70, standardY + 0.1, 370);
	glVertex3f(-190, standardY + 0.1, 370);
	glEnd();
	glPopMatrix();

	//나무
	for (int i = 0; i < 100; i += 10) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185, standardY, 162 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185, standardY + 13, 162 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 100; i += 10) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75, standardY, 162 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75, standardY + 13, 162 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 90; i += 9) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75, standardY, 285 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75, standardY + 13, 285 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 90; i += 9) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185, standardY, 285 + i);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185, standardY + 13, 285 + i);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 40; i += 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185 + i, standardY, 162);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185 + i, standardY + 13, 162);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i > -40; i -= 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75 + i, standardY, 162);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75 + i, standardY + 13, 162);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i > -40; i -= 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-75 + i, standardY, 365);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-75 + i, standardY + 13, 365);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}
	for (int i = 0; i < 40; i += 8) {
		glPushMatrix();

		glMaterialfv(GL_FRONT, GL_AMBIENT, treeBody);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeBody);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeBody);

		glTranslatef(-185 + i, standardY, 365);
		glScalef(3, 30, 3);
		glutSolidCube(1);
		glPopMatrix();

		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, treeLeaf);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, treeLeaf);
		glMaterialfv(GL_FRONT, GL_SPECULAR, treeLeaf);
		glTranslatef(-185 + i, standardY + 13, 365);
		glutSolidSphere(5, 10, 10);
		glPopMatrix();
	}

	//크레인
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, crane);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, crane);
	glMaterialfv(GL_FRONT, GL_SPECULAR, crane);

	glPushMatrix();
	glPushMatrix();
	glTranslatef(-220 - 10, standardY + 100, 70);
	glScalef(10, 200, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-220 - 10, standardY + 180, 70);
	glRotatef(craneMove, 0, 1, 0);
	glPushMatrix();
	glTranslatef(30 - 10, 0, 0);
	glScalef(100, 7, 7);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPushMatrix();
	glPushMatrix();
	glTranslatef(-70 + 10, standardY + 50, 80 + 10);
	glScalef(10, 170, 10);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-70 + 10, standardY + 120, 90);
	glRotatef(craneMove, 0, 1, 0);
	glPushMatrix();
	glTranslatef(0, 0, 20);
	glScalef(7, 7, 100);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();

	//펜스
	float fence[] = { 0.8,0.8,0.8,1 };
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, fence);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, fence);
	glMaterialfv(GL_FRONT, GL_SPECULAR, fence);

	glBegin(GL_POLYGON);
	glVertex3f(-250, standardY, 20);
	glVertex3f(-250, standardY + 50, 20);
	glVertex3f(-20, standardY + 50, 20);
	glVertex3f(-20, standardY, 20);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-20, standardY, 20);
	glVertex3f(-20, standardY + 50, 20);
	glVertex3f(-20, standardY + 50, 130);
	glVertex3f(-20, standardY, 130);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-20, standardY, 130);
	glVertex3f(-20, standardY + 50, 130);
	glVertex3f(-250, standardY + 50, 130);
	glVertex3f(-250, standardY, 130);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(-250, standardY, 130);
	glVertex3f(-250, standardY + 50, 130);
	glVertex3f(-250, standardY + 50, 20);
	glVertex3f(-250, standardY, 20);
	glEnd();
	glPopMatrix();

	//지어지고 있는 건물
	float gray[] = { 0.6,0.6,0.6,1 };

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	glPushMatrix();  //건물1

	glTranslatef(-190, standardY + 50, 80);
	glScalef(60, 80, 60);
	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, black);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);
	for (int i = 0; i < 50; i += 10) {
		glPushMatrix();
		glTranslatef(-215 + i, standardY + 50, 60);
		glScalef(2, 100, 2);
		glutSolidCube(1);
		glPopMatrix();
	}glPopMatrix();
	for (int i = 0; i < 60; i += 12) {
		glPushMatrix();
		glTranslatef(-215 + i, standardY + 50, 60 + 10);
		glScalef(2, 100, 2);
		glutSolidCube(1);
		glPopMatrix();

		for (int i = 0; i < 60; i += 12) {
			glPushMatrix();
			glTranslatef(-216 + i, standardY + 50, 60 + 20);
			glScalef(2, 100, 2);
			glutSolidCube(1);
			glPopMatrix();
		}
		for (int i = 0; i < 60; i += 12) {
			glPushMatrix();
			glTranslatef(-215 + i, standardY + 50, 60 + 30);
			glScalef(2, 100, 2);
			glutSolidCube(1);
			glPopMatrix();
		}
		for (int i = 0; i < 60; i += 12) {
			glPushMatrix();
			glTranslatef(-215 + i, standardY + 50, 60 + 40);
			glScalef(2, 100, 2);
			glutSolidCube(1);
			glPopMatrix();
		}

		glPushMatrix();
		glTranslatef(-100, standardY + 30, 90);
		glScalef(60, 80, 60);
		glutSolidCube(1);
		glPopMatrix();

		//육교
		float bridge[] = { 0.8,0.8,0.4,1 };
		glPushMatrix();
		glMaterialfv(GL_FRONT, GL_AMBIENT, bridge);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bridge);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bridge);
		glTranslatef(-130, standardY + 1, 270);
		glScalef(3, 0.7, 3);
		glRotatef(90, 0, 1, 0);
		glutSolidTorus(3, 11, 10, 10);
		glPopMatrix();

		//주유소
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-230, standardY + 13, 190);
		glScalef(30, 6, 60);
		glutSolidCube(1);
		glPopMatrix();
		for (int i = 0; i < 21; i += 20) {
			glPushMatrix();
			glTranslatef(-240 + i, standardY + 5, 170);
			glScalef(4, 10, 4);
			glutSolidCube(1);
			glPopMatrix();
		}
		for (int i = 0; i < 21; i += 20) {
			glPushMatrix();
			glTranslatef(-240 + i, standardY + 5, 210);
			glScalef(4, 10, 4);
			glutSolidCube(1);
			glPopMatrix();
		}
		//glPushMatrix();
		glPushMatrix();
		glTranslatef(-230, standardY + 10, 235);
		glScalef(40, 30, 20);
		glutSolidCube(1);
		glPopMatrix();

		//glPopMatrix();

	}
}

void block14()
{
	//구멍난 건물(좌)
	glPushMatrix();
	glTranslatef(-225, standardY + 15, 295);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-225, standardY + 15, 370);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-210, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-240, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();
	//구멍난 건물(우)
	glPushMatrix();
	glTranslatef(-40, standardY + 15, 295);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-40, standardY + 15, 370);
	glScalef(35, 40, 15);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-25, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-55, standardY + 15, 333);
	glScalef(15, 40, 90);
	glutSolidCube(1);
	glPopMatrix();
}

void main(int argc, char** argv) // 윈도우 출력하고 출력함수 설정  
{
	glutInit(&argc, argv); // glut 초기화  
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정  
	//glutInitWindowPosition(100, 100); // 윈도우의 위치 지정  
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정  

	glutCreateWindow("Tiles"); // 윈도우 생성 (윈도우 이름)  
	glutDisplayFunc(DrawScene); // 출력 함6수의 지정  
	glutReshapeFunc(Reshape); // 다시 그리기 함수 지정  
	//glutTimerFunc(100, Timerfunction, 1);
	glutKeyboardFunc(Keyboard);	// 키보드 입력 받기 
	glutMainLoop(); // 이벤트 처리 시작  
}

void DrawScene()
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.5, 0.5, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	initLight();

	glLoadIdentity();

	/*
	//조명---------------------------------------
	float ambientLight[] = { 1.0,1.0,1.0,1.0 };
	float diffuseLight[] = { 1.0,1.0,1.0,1.0 };
	float specularLight[] = { 1.0,1.0,1.0,1.0 };
	float lightPos[] = { 0.0,100.0,0.0,1.0 };

	glEnable(GL_LIGHTING);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
	//-----------------------------------
	*/

	//좌표변환------------------
	glTranslatef(moveR, 0, 0);
	glTranslatef(moveL, 0, 0);
	glTranslatef(0, moveU, 0);
	glTranslatef(0, moveD, 0);
	glTranslatef(0, 0, moveFront);
	glTranslatef(0, 0, moveBack);

	//전체회전
	glRotatef(rotateX, 1, 0, 0.0);
	glRotatef(rotateY, 0, 1, 0);
	glRotatef(rotateZ, 0, 0, 1);
	//------------------------------


	BaseGround();
	Road();

	block11();

	block10();
	block14();


	glutSwapBuffers();
}

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	gluPerspective(80.0, w / h, 1.0, 5000.0);
	glTranslatef(0.0, 0.0, -100.0);

	//glOrtho(0, 500.0, -0.0, 500.0, -1.00,1.00);

	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'x':
		rotateX += 10;
		break;
	case 'y':
		rotateY += 10;
		break;
	case 'z':
		rotateZ += 10;
		break;
	case 's':
		moveU += 10;
		break;
	case 'w':
		moveD -= 10;
		break;
	case'a':
		moveR += 10;
		break;
	case'd':
		moveL -= 10;
		break;
	case'+':
		moveFront += 10;
		break;
	case'-':
		moveBack -= 10;
		break;

	case 'i':
		rotateX = 0;
		rotateY = 0;
		rotateZ = 0;
		moveR = 0;
		moveL = 0;
		moveU = 0;
		moveD = 0;
		moveFront = 0;
		moveBack = 0;
		break;

	case'q':	//프로그램 종료
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
		break;
	case'l':
		craneMove++;
		break;
	}

	glutPostRedisplay();
}