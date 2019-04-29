/*
Name:Zhenjiang Yang
Student Number:001431873
MacID: yangz5
*/
#include <stdio.h>
#include <stdlib.h>
#include "Mesh.h"
#include <windows.h>
#include <iostream>



#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
using namespace std;

//Mesh *myMesh = new Mesh();
Mesh myMesh = Mesh();

#define X 0
#define Y 1
#define Z 2
#define W 3

//Globals
float camPos[] = { 80, 30, 100 };	//where the camera is
float camTarget[] = { 0, 0, 0 };

float angle = 0;
int rotateX = 0;
int rotateY = 0;

float SceneScale = 0.75f;

float EarthSize = 0.5f;

float width = 600;
float height = 600;
int toggle = 1;
int quad = 1;
void initPointsMap(int size)
{
	int number = size / 2.5;
	myMesh.multiplePoints(size);
	myMesh.random(1, size, number);
}


//OpenGL functions
//keyboard stuff
void keyboard(unsigned char key, int xIn, int yIn)
{
	int mod = glutGetModifiers();
	switch (key)
	{
	case 'q':
	case 27:	//27 is the esc key
		exit(0);
		break;
	case 'w':
		toggle = toggle + 1;
		break;
	case 'r':
		initPointsMap(100);
		break;
	case 't':
		quad = quad + 1;
		break;
	case 's':
		camPos[Y] = camPos[Y] + 2;
		break;
	case 'x':
		camPos[Y] = camPos[Y] - 2;
		break;
	case 'z':
		camPos[X] = camPos[X] - 2;
		break;
	case 'c':
		camPos[X] = camPos[X] + 2;
		break;
	}
}

void special(int key, int xIn, int yIn) {
	switch (key) {
	case GLUT_KEY_DOWN:
		rotateX = 1;
		rotateY = 0;
		angle -= 2;
		break;
	case GLUT_KEY_UP:
		rotateX = 1;
		rotateY = 0;
		angle += 2;
		break;
	case GLUT_KEY_LEFT:
		rotateX = 0;
		rotateY = 1;
		angle -= 2;
		break;
	case GLUT_KEY_RIGHT:
		rotateX = 0;
		rotateY = 1;
		angle += 2;
		break;
	}
}


//initialization
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)((width + 0.0f) / height), 1, 50000);

	//Mesh myMesh = Mesh();
	initPointsMap(100);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	float ambient[4] = { 0.1f,0.1f,0.1f,1 };//3 ALL 1111->white
	float diffuse[4] = { 0,1,0,1 };
	float spec[4] = { 0,0,1,1 };//shiny value is between 10 -100;
	float pos[4] = { 0,3,0,3 };
	//ADD color
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);


	float m_amb[] = { 0.33, 0.22, 0.03, 1.0 };
	float m_dif[] = { 0.78, 0.57, 0.11, 1.0 };
	float m_spec[] = { 0.99, 0.91, 0.81, 1.0 };
	float m_em[] = { 0,1,0,1 };
	float shiny = 10; //10, 100


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spec);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);
}

/* display function - GLUT display callback function
*		clears the screen, sets the camera position, draws the ground plane and movable box
*/
void display(void)
{
	//EarthGamma += 2;
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(camPos[0], camPos[1], camPos[2], camTarget[0], camTarget[1], camTarget[2], 0, 1, 0);
	//earth stuff
	glPushMatrix();
	glRotatef(angle, rotateX, rotateY, 1);
	glScalef(EarthSize, EarthSize, EarthSize);
	glColor3f(0, 1, 0);
	if (quad % 2 == 1)
	{
		if (toggle % 3 == 1)
		{
			myMesh.drawPolygon();
		}
		else if (toggle % 3 == 2)
		{
			myMesh.drawLineLoop();
		}
		else
		{
			myMesh.drawPolygon();
			myMesh.drawLineLoop();
		}
	}
	else
	{
		if (toggle % 3 == 1)
		{
			myMesh.drawTri();
		}
		else if (toggle % 3 == 2)
		{
			myMesh.drawTriLine();
		}
		else
		{
			myMesh.drawTri();
			myMesh.drawTriLine();
		}
	}
	glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();;
	gluPerspective(45, (float)((w + 0.0f) / h), 1, 50000);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void FPSTimer(int value) { //60fps
	glutTimerFunc(17, FPSTimer, 0);
	glutPostRedisplay();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(width, height);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Terrain");	//creates the window

												//display callback
	glutDisplayFunc(display);
	//keyboard callback
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	//resize callback
	glutReshapeFunc(reshape);

	//fps timer callback
	glutTimerFunc(17, FPSTimer, 0);

	init();
	cout << "Arrow key to rotate the scene" << endl;
	cout << "W key to switch to wireframe" << endl;
	cout << "s z x c to control the camera" << endl;
	cout << "r key to reset a random terrain" << endl;
	cout << "t key to change polygon to triangle" << endl;


	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
/*call class
1:  Mesh myMesh = Mesh();

	myMesh.multiplePoints(50);
	myMesh.circles();

2:	Mesh *myMesh = new Mesh()
	myMesh->multiplePoints(50);
	myMesh->drawPolygon()
*/