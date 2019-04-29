/*
Name:Zhenjiang Yang
Student Number:001431873
MacID: yangz5
*/


#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif


#include "Mesh.h"
#include <cmath>
#include<stdlib.h>
#include<time.h>
#include<iostream>
using namespace std;

void Mesh::random(int a,int b,int number)
{
	srand((int)time(NULL));
	for (int i = 0; i<number; i++)
	{
		int centerx = (rand() % (b - a + 1)) + a;
		int centerz = (rand() % (b - a + 1)) + a;
		int circleSize = (rand() % (b - (a+1) + 1)) + (a+1);
		int height = (rand() % (15 - 1 + 1)) + 1;
		circles(centerx,centerz,circleSize,height);
	}
}

Mesh::Mesh() {}

void Mesh::multiplePoints(int size)
{
	this->size = size;
	pointsMap = new float*[size*size];
	for (int i = 0; i < (size*size); ++i)
	{
		pointsMap[i] = new float[3];
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			pointsMap[i*size + j][0] = i;
			pointsMap[i*size + j][1] = 0;
			pointsMap[i*size + j][2] = j;
		}
	}
}

void Mesh::drawPolygon()
{
	for (int i = 0; i < size-1; ++i)
	{
		for (int j = 0; j < size-1; ++j)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_QUADS);
			glVertex3fv(pointsMap[i*size + j]);
			glVertex3fv(pointsMap[i*size + (j + 1)]);
			glVertex3fv(pointsMap[(i + 1)*size + (j + 1)]);
			glVertex3fv(pointsMap[(i + 1)*size + j]);
			glEnd();
		}
	}
}

void Mesh::drawLineLoop()
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			glColor3f(0.0f, 1.0f, 0.0f);
			glBegin(GL_LINE_LOOP);
			glVertex3fv(pointsMap[i*size + j]);
			glVertex3fv(pointsMap[i*size + (j + 1)]);
			glVertex3fv(pointsMap[(i + 1)*size + (j + 1)]);
			glVertex3fv(pointsMap[(i + 1)*size + j]);
			glEnd();
		}
	}
}
void Mesh::drawTri()
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			glBegin(GL_TRIANGLES);
			glVertex3fv(pointsMap[size * i + j]);
			glVertex3fv(pointsMap[size * i + (j + 1)]);
			glVertex3fv(pointsMap[size * (i + 1) + j]);
			glEnd();

			glBegin(GL_TRIANGLES);
			glVertex3fv(pointsMap[size * i + (j + 1)]);
			glVertex3fv(pointsMap[size * (i + 1) + j]);
			glVertex3fv(pointsMap[size * (i + 1) + (j + 1)]);
			glEnd();
		}
	}
}

void Mesh::drawTriLine()
{
	for (int i = 0; i < size - 1; ++i)
	{
		for (int j = 0; j < size - 1; ++j)
		{
			glBegin(GL_LINE_LOOP);
			glVertex3fv(pointsMap[size * i + j]);
			glVertex3fv(pointsMap[size * i + (j + 1)]);
			glVertex3fv(pointsMap[size * (i + 1) + j]);
			glEnd();

			glBegin(GL_LINE_LOOP);
			glVertex3fv(pointsMap[size * i + (j + 1)]);
			glVertex3fv(pointsMap[size * (i + 1) + j]);
			glVertex3fv(pointsMap[size * (i + 1) + (j + 1)]);
			glEnd();
		}
	}
}
void Mesh::circles(int centerx, int centerz, int circleSize, int height)
{
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			float isInside = (sqrt(powf((pointsMap[i*size + j][0]-centerx),2)+ powf((pointsMap[i*size + j][2] - centerz),2)))*2/circleSize;
			if (isInside < 1.0) 
			{
				pointsMap[i*size + j][1] += height / 2 + cos(isInside*3.14)*height / 2;
			}
		}
	
}

}
