#include "stdafx.h"
#include "model3d.h"

#include <iostream>
#include <fstream>
#include <string>
//#include <vector> // для разбора строки
#include <sstream> // для разбора строки


#ifdef CODEBLOCKS    // WIN32 - 64 ????
#include <GL/glut.h>
#else
#include "glut.h"	// Эта строка только для Visual Studio
#endif   


using namespace std;



model3d::model3d(char* name)
{
	ReadFile(name);
}


void model3d::ReadFile(char* name)
{
	//обьявляем переменную которая будет ссылкой на файл 
	std::fstream FileObj;
	//обьявляем переменную для чтения строк текста из файла
	std::string ReadLine;

	char v1, v2;

	FileObj.open(name, std::ios::in);
	//проверяем открылся ли файл 
	if (FileObj.is_open())
	{
		//Читаем файл пока он не закончился
		// подсчёт количества вершин для создания динамического массива
		nVertex = 0;
		nPoly = 0;

		while (!FileObj.eof())
		{
			std::getline(FileObj, ReadLine, '\n');

			if (ReadLine.length() > 1)
			{
				v1 = ReadLine[0];
				if ('v' == v1)
				{
					v2 = ReadLine[1];
					if (' ' == v2)
					{
						nVertex++;
					}
					/*					if ('t' == v2)
					{
					break;
					}*/
				}
				if ('f' == v1)
				{
					v2 = ReadLine[1];
					if (' ' == v2)
					{
						nPoly++;
					}
					/*					if ('t' == v2)
					{
					break;
					}*/
				}

			}
		}

		FileObj.close();
	}

	// Выделение памяти динамически
	modelPoints1 = new TPoint[nVertex];
	modelPolys1 = new TPoly[nPoly];

	// Загрузка массива вершин
	FileObj.open(name, std::ios::in);
	if (FileObj.is_open())
	{
		iVertex = 0;
		iPoly = 0;
		while (!FileObj.eof())
		{
			std::getline(FileObj, ReadLine, '\n');
			if (ReadLine.length() > 1)
			{
				v1 = ReadLine[0];
				if ('v' == v1)
				{
					if (' ' == ReadLine[1]) {
						string tempStr;
						stringstream ss(ReadLine);
						if (ss >> tempStr)
							if (ss >> tempStr)
							{
								modelPoints1[iVertex].x = stof(tempStr);
							}
						if (ss >> tempStr)
						{
							modelPoints1[iVertex].y = stof(tempStr);
						}
						if (ss >> tempStr)
						{
							modelPoints1[iVertex].z = stof(tempStr);
						}
						iVertex++;
					}
				}
				//Загрузка порядка соединения вершин в массив

				if ('f' == v1)
				{
					string tempStr;
					stringstream ss(ReadLine);
					if (ss >> tempStr)
						if (ss >> tempStr)
						{
							modelPolys1[iPoly].n[0] = stof(tempStr);
						}
					if (ss >> tempStr)
					{
						modelPolys1[iPoly].n[1] = stof(tempStr);
					}
					if (ss >> tempStr)
					{
						modelPolys1[iPoly].n[2] = stof(tempStr);
					}
					if (ss >> tempStr)
					{
						modelPolys1[iPoly].n[3] = stof(tempStr);
					}
					else
					{
						modelPolys1[iPoly].n[3] = modelPolys1[iPoly].n[2];
					}
					iPoly++;
				}
			
			
			
			
			}
		}
		
		FileObj.close();
	}
}

void model3d::objLoadFromFile(char *fname)
{

	ReadFile(fname);
}


void model3d::objDraw(float x, float y, float z)
{
	int i = 0, j;
	glTranslatef(x, y, z);
	glPushMatrix();
	glRotated(rotate_angle, 0, 1,0);
	rotate_angle+=1;
	for(i = 0; i < nPoly; i++)
	{
		glBegin(GL_POLYGON);
		glColor3d(1, 1, 0);
		j = modelPolys1[i].n[0] - 1;
		glVertex3f(modelPoints1[j].x, modelPoints1[j].y, modelPoints1[j].z);
		j = modelPolys1[i].n[1] - 1;
		glVertex3f(modelPoints1[j].x, modelPoints1[j].y, modelPoints1[j].z);
		j = modelPolys1[i].n[2] - 1;
		glVertex3f(modelPoints1[j].x, modelPoints1[j].y, modelPoints1[j].z);
		j = modelPolys1[i].n[3] - 1;
		glVertex3f(modelPoints1[j].x, modelPoints1[j].y, modelPoints1[j].z);
		glEnd();
	}
	glPopMatrix();
	//glutSolidSphere(0.05, 20, 20);
	glTranslatef(-x, -y, -z);
}



model3d::~model3d()
{
	free(modelPoints1);
	free(modelPolys1);
}
