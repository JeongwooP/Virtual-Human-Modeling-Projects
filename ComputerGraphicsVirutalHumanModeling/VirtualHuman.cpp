#include <windows.h>
#include <glut.h>
#include <math.h>

//20102424, 20112478 .pptx 도라에몽 참고하기
//이걸로 제출하기

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

GLUquadricObj *h, *t;

int cameraLength = 0;
int viewX = 0, viewY = 0;

float angleX = 0.0f;
float angleY = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, ly = 0.0f, lz = 0.0f;

// XZ position of the camera
float x = 0.0f, y = 0.0f, z = 0.0f;

float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;

float deltaMove = 0.0f;
int xOrigin = -1;
int yOrigin = -1;

//ctrl + k + c 주석
//ctrl + k + u 주석해제

void changeSize(int w, int h) {

	if (h == 0)
		h = 1;

	float ratio = w / h;

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, w, h);

	// Set the correct perspective.
	//gluPerspective(45.0f, ratio, 0.1f, 100.0f);
	glOrtho(-500.0, 700.0, -500.0, 700.0, 0.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
}

void head()
{
	glutSolidSphere(100, 1000, 1000);
}

void torso()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_LINE);
	gluCylinder(h, 100, 100, 300, 20, 20);
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
	gluCylinder(h, 20, 20, 400, 20, 20);
}

void leftArm()
{
	h = gluNewQuadric();
	gluQuadricDrawStyle(h, GLU_LINE);
	gluCylinder(h, 20, 20, 400, 20, 20);
}

void rightLeg()
{

}

void leftLeg()
{
	
}

void leftHand()
{

}

void rightHand()
{

}

void leftFoot()
{

}

void rightFoot()
{

}

void setCamera()
{

}

//void reshape(int w, int h)
//{
//	glLoadIdentity();
//	glViewport(0, 0, w, h);
//}

void display(void) //drawSnowman()과 같음
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glTranslated(0, 250, 0);	//x축,y축,z축 위치 지정
	glColor3f(1.0, 0.0, 1.0);
	head();
	glPopMatrix();

	glPushMatrix();
	glRotatef(90, 0.0, 1.0, 0.0); //y축 중심으로 90도 회전
	glColor3f(1.0, 0.0, 1.0);
	glRotatef(90, 1.0, 0.0, 0.0);
	torso();
	glPopMatrix();

	//glFlush();
	//glutSwapBuffers(); //마지막에 이걸 해줘야 함
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

void renderScene(void) {

	if (deltaMove)
		computePos(deltaMove);

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x + lx, y + ly, z + lz,
		0, 0, 0,
		0.0f, 1.0f, 0.0f);
	
	glPushMatrix();
	glTranslatef(0, 0, 0);
	display();
	glPopMatrix();


	glutSwapBuffers();
}


//void look(int camera)
//{
//	gluLookAt(200 + 1 * camera, 200 + 1 * camera, 200 + 1 * camera,
//		0, 0, 0,
//		0, 1, 0);
//}

void onKeyPress(unsigned char key, int x, int y)
{
	if (key == 'z' || key == 'Z')
		deltaMove = -0.5f;
	else if (key == 'a' || key == 'A')
		deltaMove = 0.5f;
	else
		deltaMove = 0;

	//glutPostRedisplay();
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angleX += deltaAngleX;
			angleY += deltaAngleY;
			xOrigin = -1;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngleX = (x - xOrigin) * 0.01f;
		deltaAngleY = (y - yOrigin) * 0.01f;

		// update camera's direction
		lx = sin(angleX + deltaAngleX);
		ly = tan(angleY + deltaAngleY);
		lz = -cos(angleX + deltaAngleX);
	}
}

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



int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Human");

	//init();
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	//glutIdleFunc(rotate);

	glutKeyboardFunc(onKeyPress);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 0;

}
