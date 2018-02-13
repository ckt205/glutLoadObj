/*
������ ������	 ��������
#	 ��� ������ �������� ������������
mtllib	 ������ �� ���� � ��������� ��������� ��� ������� �������
o	 �������� �������
v	 ���������� ����� �������
vn	 ���������� ������� ��� ����� �������
vt	  � ��� ��� �� ������ ���������� �������� �������
f	 �������� ������ ��������

*/
#include "stdafx.h"
#include "objLoad.h"

#include <iostream>
#include <fstream>
#include <string>
//#include <vector> // ��� ������� ������
#include <sstream> // ��� ������� ������


#ifdef CODEBLOCKS    // WIN32 - 64 ????
#include <GL/glut.h>
#else
#include "glut.h"	// ��� ������ ������ ��� Visual Studio
#endif   


using namespace std;


typedef struct
{
	float x, y, z;
} TPoint;

typedef struct
{
	int n[4];
} TPoly;

TPoint *modelPoints1 = NULL;
TPoly *modelPolys1 = NULL;

int nVertex = 0, iVertex = 0;
int nPoly = 0, iPoly = 0;


void ReadFile(char* name)
{
	//��������� ���������� ������� ����� ������� �� ���� 
	std::fstream FileObj;
	//��������� ���������� ��� ������ ����� ������ �� �����
	std::string ReadLine;
		
	char v1, v2;

	FileObj.open(name, std::ios::in);
	//��������� �������� �� ���� 
	if (FileObj.is_open())
	{
		//������ ���� ���� �� �� ����������
		// ������� ���������� ������ ��� �������� ������������� �������
		nVertex = 0;
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
				}
			}
		}

		nPoly = 0;
		while (!FileObj.eof())
		{
			std::getline(FileObj, ReadLine, '\n');

			if (ReadLine.length() > 1)
			{
				v1 = ReadLine[0];
				if ('f' == v1)
				{
					v2 = ReadLine[1];
					if (' ' == v2)
					{
						nPoly++;
					}
				}
			}
		}
		FileObj.close();
	}

	// ��������� ������ �����������
	modelPoints1 = new TPoint[nVertex];
	modelPolys1 = new TPoint[nVertex];
	
	// �������� ������� ������
	FileObj.open(name, std::ios::in);
	if (FileObj.is_open())
	{
		iVertex = 0;
		while ((!FileObj.eof()) && (iVertex < nVertex))
		{
			std::getline(FileObj, ReadLine, '\n');
			if (ReadLine.length() > 1)
			{
				v1 = ReadLine[0];
				if ('v' == v1)
				{
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
				}
			}
		}

		while ((!FileObj.eof()) && (iVertex < nVertex))
		{
			std::getline(FileObj, ReadLine, '\n');
			if (ReadLine.length() > 1)
			{
				v1 = ReadLine[0];
				if ('f' == v1)
				{
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
				}
			}
		}
		
		FileObj.close();
	}
}

void objLoadFromFile(char *fname)
{
	ReadFile(fname);
}


void objDraw(float x, float y, float z)
{
	glTranslatef(x, y, z);
	glutSolidSphere(3.0, 20, 20);
	glTranslatef(-x, -y, -z);
}