// ConsoleApplication7.cpp: определяет точку входа для консольного приложения.
//


#include "stdafx.h"

//int _tmain(int argc, _TCHAR* argv[])
//{
//	
//}

// НЕ обязательно, просто для переносимости и для своего опыта можно сделать
// 2. Найти способ подстраивать проект макросами (или иначе) под рабочее место 


#define CODEBLOCKS__

#ifdef CODEBLOCKS    // WIN32 - 64 ????
#include <GL/glut.h>
#else
//#include <GL/free_glut.h>
#include "glut.h"	// Эта строка только для Visual Studio
#define _CRT_SECURE_NO_WARNINGS   // Эта строка только для Visual Studio
#endif   


#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

//#include "objLoad.h"
#include "model3d.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
//#pragma comment(lib, ".lib")



int RRR = 200;
float stepZ = 0.0;

model3d bird("bird.obj");

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// glOrtho(-20.0, 20.0, -20.0, 20.0, -20.0, 20.0);

	gluPerspective(90.0, (double)h / (double)w, 1.0, 30.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char c, int x, int y) 
{ 
	if (c == 27) 
	{
		exit(0);
	}
}

void keyboard_s(int c, int x, int y)
{
	if (c == GLUT_KEY_LEFT)         glRotatef(5.0, 0.0, 1.0, 0.0);
	if (c == GLUT_KEY_RIGHT)        glRotatef(5.0, 1.0, 0.0, 0.0);

	if (c == GLUT_KEY_UP) stepZ += 0.5;
	if (c == GLUT_KEY_DOWN) stepZ -= 0.5;

}




void initLight()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glEnable(GL_LIGHT0);

	float light0_direction[] = { 0.0, 0.0, 20.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_direction);
}

void renderBitmapString(float x, float y, float z, void *font, char *string)
{
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void DrawTeapot(float x, float y, float z)
{
	glTranslatef(x, y, z);
	glutSolidTeapot(4.0);
	glTranslatef(-x, -y, -z);
}

void DrawSphere(float x, float y, float z)
{
	glTranslatef(x, y, z);
	glutSolidSphere(2.0, 20, 20);
	glTranslatef(-x, -y, -z);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 1.0, 0.0);

	glPushMatrix();  // Запомнить состояние системы координат в стек

	glColor3f(0.4, 0.7, 0.9);
	DrawTeapot(0.0, 7.0, 22.0);

	glTranslatef(0.0, stepZ / 10.0, stepZ);

	glColor3f(0.9, 0.8, 0.7);
	DrawSphere(0.0, -7.0, -22.0);

	glColor3f(1.0, 0.0, 0.0);
	bird.objDraw(0.0, -2.0, -15.0);
	//Sleep(1);
	//RRR++;
	glColor3f(0.4, 0.5, 0.2);
	DrawSphere(0.3, -5.0, -4.0);


	char str2[64];
	sprintf_s(str2, "test: %d", 123);
	renderBitmapString(-18, 18, 0, GLUT_BITMAP_TIMES_ROMAN_24, str2);


	glPopMatrix();  // "Вынуть" состояние системы координат

	glFlush();
	glFinish();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(640, 640);
	glutInitWindowPosition(400, 200);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutCreateWindow("3D TEST");

	glutSpecialFunc(keyboard_s);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	initLight();
	//bird.objLoadFromFile("bird.obj");

	glutMainLoop();

	return 0;
}
