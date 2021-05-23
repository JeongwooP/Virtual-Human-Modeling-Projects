
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <glut.h>
#include <math.h>
#include <SOIL2.h>
#include <string>
#include <GL.h>
#include <glaux.h>


using namespace std;

//20102424, 20112478 .pptx 도라에몽 참고하기
//이걸로 제출하기

#define GL_SILENCE_DEPRECATION


//int image_width = 0;
//int image_height = 0;
//unsigned  char* image = SOIL_load_image("Images/atom.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

//GLuint texture0;


GLUquadricObj *h, *t, *earth;


static float zoom = 5.0; //줌 변수
float scale = 1.0;

float angleX = 30.0f;
float angleY = 30.0f;
float angleZ = 30.0f;

int mouse_state = 0;
int mouse_button = 0;
int mouse_X = 0;
int mouse_Y = 0;

int projection = 1;
int size_ = 10;
int windowWidth;
int windowHeight;


unsigned int MyTextureObject[1];
AUX_RGBImageRec *pTextureImage[1];

GLuint  texture[1];

//ctrl + k + c 주석
//ctrl + k + u 주석해제


AUX_RGBImageRec *LoadBMP(char *szFilename) {
	FILE * pFile = NULL;
	if (!szFilename) {
		return NULL;
	}
	pFile = fopen(szFilename, "r");
	if (pFile) {
		fclose(pFile);
		return auxDIBImageLoad(szFilename);
	}
	return NULL;
}

int LoadGLTextures(char * szFilePath) {
	earth = gluNewQuadric();

	gluQuadricDrawStyle(earth, GLU_FILL);
	gluQuadricTexture(earth, GL_TRUE);

	int Status = FALSE;
	glClearColor(0.0, 0.0, 0.0, 0.5);
	memset(pTextureImage, 0, sizeof(void *) * 1);

	if (pTextureImage[0] = LoadBMP(szFilePath)) {
		Status = TRUE;
		glGenTextures(1, &MyTextureObject[0]);
		glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, pTextureImage[0]->sizeX, pTextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, pTextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glEnable(GL_TEXTURE_2D);
	}
	if (pTextureImage[0]) {
		if (pTextureImage[0]->data) {
			free(pTextureImage[0]->data);
		}
		free(pTextureImage[0]);
	}
	return Status;
}


void resize(int width, int height) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (projection)
		glOrtho(-size_, size_, -size_, size_, -size_, size_);
	else
		gluPerspective(60.0, (float)width / height, 0.1, 100.);

	glEnable(GL_DEPTH_TEST);
	windowWidth = width;
	windowHeight = height;
}

void head()
{
	glutSolidSphere(2, 1000, 1000);
}

void torso()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	gluCylinder(h, 1, 2, 4, 120, 100);
	
}

void rightArm()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	gluCylinder(h, 0.7, 0.7, 4.5, 20, 20);
}

void leftArm()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	gluCylinder(h, 0.7, 0.7, 4.5, 20, 20);
}

void rightLeg()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	gluCylinder(h, 0.7, 0.7, 4.5, 20, 20);
}

void leftLeg()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_FILL);
	gluCylinder(h, 0.7, 0.7, 4.5, 20, 20);
}

void rightHand()
{
	glutSolidSphere(0.8, 1000, 1000);
}

void leftHand()
{
	glutSolidSphere(0.8, 1000, 1000);
}

void rightFoot()
{
	glutSolidSphere(0.8, 1000, 1000);
}

void leftFoot()
{
	glutSolidSphere(0.8, 1000, 1000);
}

void closeTop() {
	glutSolidSphere(1.0, 1000, 1000);
}

void closeBottom() {
	glutSolidSphere(1.6, 1000, 1000);
}


void display(void) //draw
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5, 0.5, 0.5, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, 0.0, -5.0, 0.0, 0.0, 0.0, 0, 1, 0);

	
	glRotatef(angleX, 1.0f, 0.0f, 0.0f);
	glRotatef(angleY, 0.0f, 1.0f, 0.0f);
	glRotatef(angleZ, 0.0f, 0.0f, 1.0f);
	glScalef(scale, scale, scale);

	glPushMatrix();
	glTranslated(0, 2, 0);	//x축,y축,z축 위치 지정
	glColor3f(1.0, 0.0, 0.0);
	head();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.2, 0);	//x축,y축,z축 위치 지정
	glColor3f(1.0, 1.0, 0.0);
	closeTop();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0); //y축 중심으로 90도 회전
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	torso();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -2.7, 0);	//x축,y축,z축 위치 지정
	glColor3f(0.0, 1.0, 0.0);
	closeBottom();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -1, 0);
	glRotatef(90, 0.0, 1.0, 0.0); //y축 중심으로 90도 회전
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	rightArm();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -1, 0);
	glRotatef(90, 0.0, 1.0, 0.0); 
	glColor3f(1.0, 1.0, 0.0);
	glRotatef(360, 1.0, 0.0, 0.0);
	leftArm();
	glPopMatrix();


	glPushMatrix();
	glTranslated(-0.8, -3, 0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	rightLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.8, -3, 0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(0.0, 1.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	leftLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-5, -1, 0);
	glColor3f(1.0, 0.5, 0.0);
	rightHand();
	glPopMatrix();

	glPushMatrix();
	glTranslated(5, -1, 0);
	glColor3f(1.0, 0.5, 0.0);
	leftHand();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-0.8, -7.3, 0);
	glColor3f(0.5, 0.0, 1.0);
	rightFoot();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.8, -7.3, 0);
	glColor3f(0.5, 0.0, 1.0);
	leftFoot();
	glPopMatrix();

	/*glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(-1.0, 1.0);
	glTexCoord2f(1.0, 1.0); glVertex2f(1.0, 1.0);
	glTexCoord2f(1.0, 0.0); glVertex2f(1.0, -1.0);
	glTexCoord2f(0.0, 0.0); glVertex2f(-1.0, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();*/


	//glBindTexture(GL_TEXTURE_2D, MyTextureObject[0]); 
	//glBegin(GL_QUADS); 
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-1.0f, -1.0f, 1.0f); //앞면 
	//glTexCoord2f(1.0f, 0.0f); 
	//glVertex3f( 1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 1.0f); 
	//glVertex3f( 1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 1.0f); 
	//glVertex3f(-1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); 
	//glVertex3f(-1.0f, -1.0f, -1.0f); //뒷면 
	//glTexCoord2f(1.0f, 1.0f); 
	//glVertex3f(-1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 1.0f); 
	//glVertex3f( 1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 0.0f); 
	//glVertex3f( 1.0f, -1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 1.0f); 
	//glVertex3f(-1.0f, 1.0f, -1.0f); //윗면 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); //아랫면 
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); //우측면 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); //좌측면 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); 
	//glEnd(); 
	glutSwapBuffers();

	//glFlush();
	//glutSwapBuffers(); //마지막에 이걸 해줘야 함
}


//마우스 클릭했는지 판단함
void myMouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			mouse_state = state;
			mouse_button = button;
			mouse_X = x;
			mouse_Y = y;
		}
		else if (state == GLUT_UP) {
			mouse_state = -1;
		}
		else return;
	}
	else return;
	glutPostRedisplay();
}

//키보드를 눌렀을 때 확대 축소 처리함
void myKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
	case 'A':
		scale *= zoom;
		break;

	case 'z':
	case 'Z':
		scale /= zoom;
		break;
	}

	glutPostRedisplay();
}

//드래그 판단 처리
void myMotion(int x, int y) {
	if (mouse_button == GLUT_LEFT_BUTTON && mouse_state == GLUT_DOWN) {
		angleY -= (mouse_X - x) / 5.0;
		angleX -= (mouse_Y - y) / 5.0;
		glutPostRedisplay();
		mouse_X = x;
		mouse_Y = y;
	}
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Human");

	glutReshapeFunc(resize);

	glutDisplayFunc(display);


	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);

	glEnable(GL_DEPTH_TEST);

	LoadGLTextures("C:/Users/Peter/Pictures/CG/marbles.BMP");

	glutKeyboardFunc(myKeyboard);

	glutMainLoop();

	return 0;

}
