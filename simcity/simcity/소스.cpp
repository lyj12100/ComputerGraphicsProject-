#include<gl/freeglut.h>

void DrawScene();
void Reshape(int, int);
void Keyboard(unsigned char, int, int);


float rotateX, rotateY, rotateZ = 0;
int moveR, moveL, moveU, moveD, moveFront, moveBack = 0;

//객체함수

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

void BaseGround()
{
	float gray[] = { 0.3,0.3,0.3,1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, gray);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, gray);

	glBegin(GL_POLYGON);
	glVertex3f(-500, -200, -500);
	glVertex3f(500, -200, -500);
	glVertex3f(500, -200, 500);
	glVertex3f(-500, -200, 500);
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
		glVertex3f(-500, -199.9, i + 10);
		glVertex3f(500, -199.9, i + 10);
		glVertex3f(500, -199.9, i - 10);
		glVertex3f(-500, -199.9, i - 10);
		glEnd();
	}
	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_POLYGON);
		glVertex3f(i - 10, -199.9, 500);
		glVertex3f(i + 10, -199.9, 500);
		glVertex3f(i + 10, -199.9, -500);
		glVertex3f(i - 10, -199.9, -500);
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
		glVertex3f(-500, -199.8, i);
		glVertex3f(500, -199.8, i);
		glEnd();
	}
	for (int i = -270; i < 280; i += 270) {
		glBegin(GL_LINES);
		glVertex3f(i, -199.8, -500);
		glVertex3f(i, -199.8, 500);
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

	glPushMatrix();
	glTranslatef(80, -50, 80);
	glScalef(100, 300, 100);

	glutSolidCube(1);
	glPopMatrix();

	glPushMatrix();
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
	float green[] = { 0,1,0,1 };


	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, green);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	glMaterialfv(GL_FRONT, GL_SPECULAR, green);

	glBegin(GL_POLYGON);

	glVertex3f(-185, -199.7, 160);
	glVertex3f(-65, -199.7, 160);
	glVertex3f(-185, -199.7, 340);
	glVertex3f(-65, -199.7, 340);
	glEnd();
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
	case 'w':
		moveU += 10;
		break;
	case 's':
		moveD -= 10;
		break;
	case'd':
		moveR += 10;
		break;
	case'a':
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
	}

	glutPostRedisplay();
}