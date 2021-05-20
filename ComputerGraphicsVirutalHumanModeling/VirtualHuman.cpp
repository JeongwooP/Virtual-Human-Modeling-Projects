
#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <glut.h>
#include <math.h>
#include <SOIL2.h>
#include <string>
#include <GL.h>
#include <glaux.h>


using namespace std;

//20102424, 20112478 .pptx ���󿡸� �����ϱ�
//�̰ɷ� �����ϱ�

#define GL_SILENCE_DEPRECATION

#define WIN_WIDTH 800
#define WIN_HEIGHT 800
#define TORSO_HEIGHT 5.0
#define TORSO_RADIUS 1.3
#define UPPER_ARM_HEIGHT 2.5
#define LOWER_ARM_HEIGHT 2.3
#define UPPER_ARM_RADIUS  0.5
#define LOWER_ARM_RADIUS  0.5
#define UPPER_LEG_RADIUS  0.5
#define LOWER_LEG_RADIUS  0.5
#define LOWER_LEG_HEIGHT 3.1
#define UPPER_LEG_HEIGHT 3.3
#define HEAD_HEIGHT 1.2
#define HEAD_RADIUS 1.4
#define HAND_RADIUS 0.6
#define HAND_HEIGHT 0.9
#define FOOT_RADIUS 0.7
#define FOOT_HEIGHT 1.1
#define NECK_RADIUS 0.5
#define NECK_HEIGHT 1.0
#define JOINT_POINT_RADIUS 0.5
#define JOINT_POINT_HEIGHT 0.5


//int image_width = 0;
//int image_height = 0;
//unsigned  char* image = SOIL_load_image("Images/atom.png", &image_width, &image_height, NULL, SOIL_LOAD_RGBA);

//GLuint texture0;


GLUquadricObj *h, *t, *earth;


static float zoom = 5.0; //�� ����
float scale = 1.0;

int cameraLength = 0;
int viewX = 0, viewY = 0;

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

// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = 0.0f;

// XZ position of the camera
static float x = 0.0f, y = 0.0f, z = 0.0f;

float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;

float deltaMove = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

unsigned int MyTextureObject[1];
AUX_RGBImageRec *pTextureImage[1];

GLuint  texture[1];

//ctrl + k + c �ּ�
//ctrl + k + u �ּ�����


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

//void changeSize(int w, int h) {
//
//	if (h == 0)
//		h = 1;
//
//	float ratio = w / h;
//
//	glMatrixMode(GL_PROJECTION);
//
//	glLoadIdentity();
//
//	glViewport(0, 0, w, h);
//
//	// Set the correct perspective.
//	//gluPerspective(45.0f, ratio, 0.1f, 100.0f);
//	glOrtho(-700.0, 700.0, -700.0, 700.0, 0.0, 300.0);
//
//	glMatrixMode(GL_MODELVIEW);
//}

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
	/*glPushMatrix();
	glColor3f(1.0, 0.0, 5.0);
	glRotatef(-90.0, 1.0, 0.0, 0.0);
	glRotatef(15.0, 0.0, 0.0, 1.0);
	glScalef(HEAD_HEIGHT, HEAD_HEIGHT, HEAD_RADIUS);
	gluSphere(h, 1.0, 10, 10);
	glPopMatrix();*/
}

void rightArm()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_LINE);
	gluCylinder(h, 0.7, 0.7, 4.5, 20, 20);
}

void leftArm()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_LINE);
	gluCylinder(h, 20, 20, 330, 20, 20);
}

void rightLeg()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_LINE);
	gluCylinder(h, 20, 20, 330, 20, 20);
}

void leftLeg()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_LINE);
	gluCylinder(h, 20, 20, 330, 20, 20);
}

void leftHand()
{
	glutSolidSphere(30, 1000, 1000);
}

void rightHand()
{
	glutSolidSphere(30, 1000, 1000);
}

void leftFoot()
{
	glutSolidSphere(30, 1000, 1000);
}

void rightFoot()
{
	glutSolidSphere(30, 1000, 1000);
}

void setCamera()
{

}

//void reshape(int w, int h)
//{
//	glLoadIdentity();
//	glViewport(0, 0, w, h);
//}

void display(void) //drawSnowman()�� ����
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
	glTranslated(0, 2, 0);	//x��,y��,z�� ��ġ ����
	glColor3f(1.0, 0.0, 0.0);
	head();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0); //y�� �߽����� 90�� ȸ��
	glColor3f(0.0, 1.0, 0.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	torso();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -0.8, 0);
	glRotatef(90, 0.0, 1.0, 0.0); //y�� �߽����� 90�� ȸ��
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(180, 1.0, 0.0, 0.0);
	rightArm();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, -50, 0);
	glRotatef(90, 0.0, 1.0, 0.0); 
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(360, 1.0, 0.0, 0.0);
	leftArm();
	glPopMatrix();


	glPushMatrix();
	glTranslated(-50, -150, 0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	rightLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, -150, 0);
	glRotatef(90, 0.0, 1.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	glRotatef(90, 0.0, 0.0, 1.0);
	leftLeg();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-350, -50, 0);
	glColor3f(1.0, 1.0, 1.0);
	rightHand();
	glPopMatrix();

	glPushMatrix();
	glTranslated(350, -50, 0);
	glColor3f(1.0, 1.0, 1.0);
	leftHand();
	glPopMatrix();

	glPushMatrix();
	glTranslated(-50, -500, 0);
	glColor3f(1.0, 1.0, 1.0);
	rightFoot();
	glPopMatrix();

	glPushMatrix();
	glTranslated(50, -500, 0);
	glColor3f(1.0, 1.0, 1.0);
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
	//glVertex3f(-1.0f, -1.0f, 1.0f); //�ո� 
	//glTexCoord2f(1.0f, 0.0f); 
	//glVertex3f( 1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 1.0f); 
	//glVertex3f( 1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 1.0f); 
	//glVertex3f(-1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); 
	//glVertex3f(-1.0f, -1.0f, -1.0f); //�޸� 
	//glTexCoord2f(1.0f, 1.0f); 
	//glVertex3f(-1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 1.0f); 
	//glVertex3f( 1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 0.0f); 
	//glVertex3f( 1.0f, -1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 1.0f); 
	//glVertex3f(-1.0f, 1.0f, -1.0f); //���� 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); //�Ʒ��� 
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f); //������ 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, -1.0f); 
	//glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); //������ 
	//glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); 
	//glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f); 
	//glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); 
	//glEnd(); 
	glutSwapBuffers();

	//glFlush();
	//glutSwapBuffers(); //�������� �̰� ����� ��
}

//void mouseMove(GLint X, GLint Y)
//{
//	viewX = X;
//	viewY = Y;
//	glutPostRedisplay();
//}

void computePos(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	y += deltaMove * ly * 0.1f;
	z += deltaMove * lz * 0.1f;
}

//void renderScene(void) {
//
//	if (deltaMove)
//		computePos(deltaMove);
//
//	// Clear Color and Depth Buffers
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	// Reset transformations
//	glLoadIdentity();
//	// Set the camera
//	gluLookAt(x + lx, y + ly, z + lz,
//		0, 0, 0,
//		0.0f, 1.0f, 0.0f);
//	
//	glPushMatrix();
//	glTranslatef(0, 0, 0);
//	display();
//	glPopMatrix();
//
//
//	glutSwapBuffers();
//}


//void look(int camera)
//{
//	gluLookAt(200 + 1 * camera, 200 + 1 * camera, 200 + 1 * camera,
//		0, 0, 0,
//		0, 1, 0);
//}

//void onKeyPress(unsigned char key, int x, int y)
//{
//	if (key == 'z' || key == 'Z') 
//		deltaMove = -0.5f;
//	
//	else if (key == 'a' || key == 'A')
//		deltaMove = 0.5f;
//	else
//		deltaMove = 0;
//
//	//glutPostRedisplay();
//}

//void keyboard(int Key, int x, int y) {
//	switch (Key) {
//
//	case GLUT_KEY_PAGE_DOWN: //�� ���
//		y = y + 1;
//		break;
//
//	case GLUT_KEY_PAGE_UP: //�� Ȯ��
//		y = y - 1;
//		break;
//	}
//	glutPostRedisplay();
//}

//void mouseButton(int button, int state, int x, int y) {
//
//	// only start motion if the left button is pressed
//	if (button == GLUT_LEFT_BUTTON) {
//
//		// when the button is released
//		if (state == GLUT_UP) {
//			angleX += deltaAngleX;
//			angleY += deltaAngleY;
//			xOrigin = -1;
//		}
//		else {// state = GLUT_DOWN
//			xOrigin = x;
//			yOrigin = y;
//		}
//	}
//}

//void mouseMove(int x, int y) {
//
//	// this will only be true when the left button is down
//	if (xOrigin >= 0) {
//
//		// update deltaAngle
//		deltaAngleX = (x - xOrigin) * 0.01f;
//		deltaAngleY = (y - yOrigin) * 0.01f;
//
//		// update camera's direction
//		lx = sin(angleX + deltaAngleX);
//		ly = tan(angleY + deltaAngleY);
//		lz = -cos(angleX + deltaAngleX);
//	}
//}

//void init(void)
//{
//	glEnable(GL_DEPTH_TEST);
//
//	glClearColor(0.0, 0.8, 1.0, 0.0);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-500.0, 700.0, -500.0, 700.0, 0.0, 1000.0);
//
//	gluLookAt(200, 200, 200,
//		0, 0, 0,
//		0, 1, 0);
//}

//���콺 Ŭ�� �Ǵ�
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

//Ű���� ������ �� zoom ó��
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

//�巡�� �Ǵ� ���� �� ó��
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


	//init();
	//glutDisplayFunc(renderScene);
	//glutReshapeFunc(changeSize);
	//glutIdleFunc(renderScene);
	//glutIdleFunc(rotate);

	//glutKeyboardFunc(onKeyPress);

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
