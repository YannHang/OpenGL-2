/*The second OpenGL programming work
Yuan Hang F1324002 5130729035
mail:yuanhang_yh@sjtu.edu.cn
*/

#include"stdlib.h"
#include"stdio.h"
#include"glut.h"
#include"DrawingFunc.h"

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	/*GLfloat sizes[2];
	GLfloat step;
	glGetFloatv(GL_POINT_SIZE_RANGE, sizes);
	glGetFloatv(GL_POINT_SIZE_GRANULARITY, &step);
	GLfloat fPointSize;*/

	//glLineStipple(1, 34952);
	//glEnable(GL_LINE_STIPPLE);
	
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT, GL_LINE);
	glPolygonMode(GL_BACK, GL_LINE);

	//DrawCircRing(0, 0, 1, 100);
	//DrawCircTrunCone(0, 0, 0.5, 1, 0.6, 30);
	DrawSphere(0, 0, 0, 0.8, 0,  Pi, 20, 30);
	//DrawCircRing3D(0, 0, 0, 0.7, 0.3, 0, 2 * Pi, 50, 36);
	//DrawSpring3D(0, 0, -0.5, 0.3, 0.8, 3.2, 0.05, 72, 10);
	glFlush();
}

void key(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void Idle()
{
	display();
}

void menu(int value)
{
	printf("%d", value);
	glutPostRedisplay();
}

void main()
{
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Basic Drawing Operations");
	glutKeyboardFunc(key);
	glutIdleFunc(Idle);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	//int w = glutCreateMenu(menu);
	//glutAddMenuEntry("Item1", 1);
	//glutAddMenuEntry("Item2", 2);
	//glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}