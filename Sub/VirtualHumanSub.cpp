#include <windows.h>
#include <glut.h>
//20102424, 20112478 .pptx 도라에몽 참고하기
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
double verticalAngle = 0.0;
double horizonalAngle = 0.0;

int oldX = 0;
int oldY = 0;

int width = 1;
int height = 1;

//ctrl + k + c 주석
//ctrl + k + u 주석해제
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
}
void leftArm()
{
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
	gluLookAt(0, 0, 1 * cameraLength, 0, 0, 0, 0, 1, 0);

	glRotated(verticalAngle, 0, 1, 0);
	glRotated(horizonalAngle, 1, 0, 0);
}
//void reshape(int w, int h)
//{
//	glLoadIdentity();
//	glViewport(0, 0, w, h);
//}

void display(void)
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
	
	setCamera();

	glFlush();
	glutSwapBuffers(); //마지막에 이걸 해줘야 함
}

void mouseMove(GLint x, GLint y)
{
	y = height - y - 1;

	verticalAngle += (double)(x - oldX) / width * 90 * 2;
	horizonalAngle += (double)(oldY - y) / height * 90 * 2;
	glutPostRedisplay();
}

//void look(int camera)
//{
//	gluLookAt(200 + 1 * camera, 200 + 1 * camera, 200 + 1 * camera,
//			0, 0, 0,
//			0, 1, 0);
//}
void onKeyPress(unsigned char key, int x, int y)
{
	if (key == 'z' || key == 'Z')
	{
		cameraLength++;
	}
	else if (key == 'a' || key == 'A')
	{
		cameraLength--;
	}

	glutPostRedisplay();
}
void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.8, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500.0, 700.0, -500.0, 700.0, 0.0, 1000.0);
	gluLookAt(200, 200, 200,
		0, 0, 0,
		0, 1, 0);
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Human");
	init();
	glutDisplayFunc(display);
	//glutIdleFunc(rotate);

	glutKeyboardFunc(onKeyPress);
	glutMotionFunc(mouseMove);

	glutMainLoop();

	return 0;
}