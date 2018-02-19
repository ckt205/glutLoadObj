#pragma once


typedef struct
{
	float x, y, z;
} TPoint;

typedef struct
{
	int n[4];
} TPoly;



class model3d
{
public:

	int nVertex = 0, iVertex = 0;
	int nPoly, iPoly = 0;

	double rotate_angle = 0;

	TPoint *modelPoints1 = NULL;
	TPoly *modelPolys1 = NULL;


	model3d(char* name);
	
	void ReadFile(char* name);

	void objLoadFromFile(char *fname);

	void objDraw(float x, float y, float z);

	~model3d();
};

