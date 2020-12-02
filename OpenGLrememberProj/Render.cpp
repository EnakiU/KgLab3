

#include "Render.h"

#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include "MVect.h"
#include <future>
#include <iostream>



std::vector<std::vector<MVect>> points(
	{
		{
			{0, 0, 6},
			{0, -2, 2},
			{0, -4, 2},
			{0, -6, 6}
		},
		{
			{2, 0, 1},
			{2, -2, 2},
			{2, -4, 0},
			{2, -6, 0}
		},
		{
			{4, 0, 3},
			{4, -2, 2},
			{4, -4, 12},
			{4, -6, 2}
		},
		{
			{6, 0, 6},
			{6, -2, 2},
			{6, -4, 2},
			{6, -6, 6}
		}
	});
double f(double p1, double p2, double p3, double p4, double t)
{
	return p1 * (1 - t) * (1 - t) * (1 - t) + 3 * p2 * t * (1 - t) * (1 - t) + 3 * p3 * t * t * (1 - t) + p4 * t * t * t; //посчитанная формула
}
unsigned long int Factorial(int i)
{
	if (i == 0) return 1;
	else return i * Factorial(i - 1);
}
double Bernstein(double u, double n, int index) {
	return (Factorial(n) / (Factorial(index) * Factorial(n - index))) * pow(u, index) * pow(1 - u, n - index);
}

void BezePointsSurf(double u, double v) {
	MVect new_v;
	int n = 3, m = 3;
	for (size_t i = 0; i < points.size(); ++i) {
		for (size_t j = 0; j < points[i].size(); ++j)
		{
			new_v += points[i][j] * Bernstein(u, n, i) * Bernstein(v, m, j);
		}
	}
	//glPointSize(3);
	//glBegin(GL_POINTS);
	glVertex3dv(new_v.toArray());
	//glEnd();
}
void Beze(double P1[3], double P2[3], double P3[3], double P4[3])
{

	glLineWidth(3); //ширина линии
	glBegin(GL_LINE_STRIP);
	for (double t = 0; t <= 1.0001; t += 0.01)
	{
		double P[3];
		P[0] = f(P1[0], P2[0], P3[0], P4[0], t);
		P[1] = f(P1[1], P2[1], P3[1], P4[1], t);
		P[2] = f(P1[2], P2[2], P3[2], P4[2], t);
		glVertex3dv(P); //Рисуем точку P
	}
	glEnd();
	glLineWidth(1); //возвращаем ширину линии = 1

	glBegin(GL_LINES);
	glVertex3dv(P1);
	glVertex3dv(P2);
	glVertex3dv(P2);
	glVertex3dv(P3);
	glVertex3dv(P3);
	glVertex3dv(P4);
	glEnd();
}
MVect BezeWithoutDraw(double P1[3], double P2[3], double P3[3], double P4[3], double t)
{
	MVect Vec;
	Vec.setCoords(f(P1[0], P2[0], P3[0], P4[0], t), f(P1[1], P2[1], P3[1], P4[1], t), f(P1[2], P2[2], P3[2], P4[2], t));
	return Vec;
}
void DrawFig(double P1[3])
{
	glBegin(GL_TRIANGLES);

	glColor3d(0.7, 0.7, 0.7);

	glVertex3d(1,0,0);
	glVertex3d(-0.66, -0.66, 0);
	glVertex3d(-0.66, 0, 0.16);

	glColor3d(0.6, 0.6, 0.6);
	glVertex3d(1, 0, 0);
	glVertex3d(-0.66, 0.66, 0);
	glVertex3d(-0.66, 0, 0.16);

	glColor3d(0.6, 0.6, 0.6);
	glVertex3d(-0.66, 0.66, 0);
	glVertex3d(-0.66, 0, 0.16);
	glVertex3d(-0.9, 0, 0.16);


	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(-0.66, -0.66, 0);
	glVertex3d(-0.66, 0, 0.16);
	glVertex3d(-0.9, 0, 0.16);

	glColor3d(0.5, 0.5, 0.5);

	glVertex3d(1, 0, 0);
	glVertex3d(-0.66, -0.66, 0);
	glVertex3d(-0.66, 0, -0.16);

	glColor3d(0.55, 0.55, 0.55);
	glVertex3d(1, 0, 0);
	glVertex3d(-0.66, 0.66, 0);
	glVertex3d(-0.66, 0, -0.16);

	

	glVertex3d(-0.66, 0.66, 0);
	glVertex3d(-0.66, 0, -0.16);
	glVertex3d(-0.9, 0, -0.16);

	glColor3d(0.5, 0.5, 0.5);
	
	glVertex3d(-0.66, -0.66, 0);
	glVertex3d(-0.66, 0, -0.16);
	glVertex3d(-0.9, 0, -0.16);

	glColor3d(0.3, 0.3, 0.3);

	glVertex3d(-0.9, 0, -0.16);
	glVertex3d(-0.9, 0, 0.16);
	glVertex3d(-0.66, -0.66, 0);

	glVertex3d(-0.9, 0, -0.16);
	glVertex3d(-0.9, 0, 0.16);
	glVertex3d(-0.66, 0.66, 0);

	glColor3d(0.3, 0.3, 0.3);

	glVertex3d(0, 0, 0.1);
	glVertex3d(0, 0, 0.20);
	glVertex3d(-0.16, -0.2, 0);

	glVertex3d(0, 0, 0.2);
	glVertex3d(-0.16, -0.2, 0.20);
	glVertex3d(-0.16, -0.2, 0);

	glVertex3d(-0.16, -0.2, 0.20);
	glVertex3d(-0.16, -0.2, 0);
	glVertex3d(-0.66, -0.2, 0);

	glVertex3d(-0.16, -0.2, 0.20);
	glVertex3d(-0.66, -0.2, 0);
	glVertex3d(-0.66, -0.2, 0.20);

	glColor3d(0.5, 0.5, 0.5);

	glVertex3d(0, 0, 0.1);
	glVertex3d(0, 0, 0.20);
	glVertex3d(-0.16, 0.2, 0);

	glVertex3d(0, 0, 0.2);
	glVertex3d(-0.16, 0.2, 0.20);
	glVertex3d(-0.16, 0.2, 0);

	glVertex3d(-0.16, 0.2, 0.20);
	glVertex3d(-0.16, 0.2, 0);
	glVertex3d(-0.66, 0.2, 0);

	glVertex3d(-0.16, 0.2, 0.20);
	glVertex3d(-0.66, 0.2, 0);
	glVertex3d(-0.66, 0.2, 0.20);

	glVertex3d(-0.66, -0.2, 0);
	glVertex3d(-0.66, -0.2, 0.20);
	glVertex3d(-0.78, 0, 0);

	glVertex3d(-0.78, 0, 0);
	glVertex3d(-0.78, 0, 0.20);
	glVertex3d(-0.66, -0.2, 0.20);

	glVertex3d(-0.66, 0.2, 0);
	glVertex3d(-0.66, 0.2, 0.20);
	glVertex3d(-0.78, 0, 0);

	glVertex3d(-0.78, 0, 0);
	glVertex3d(-0.78, 0, 0.20);
	glVertex3d(-0.66, 0.2, 0.20);

	glVertex3d(0, 0, 0.2);
	glVertex3d(-0.16, -0.2, 0.20);
	glVertex3d(-0.16, 0.2, 0.20);

	glVertex3d(-0.16, -0.2, 0.20);
	glVertex3d(-0.16, 0.2, 0.20);
	glVertex3d(-0.66, 0.2, 0.20);

	glVertex3d(-0.66, 0.2, 0.20);
	glVertex3d(-0.66, -0.2, 0.20);
	glVertex3d(-0.16, -0.2, 0.20);

	glVertex3d(-0.66, 0.2, 0.20);
	glVertex3d(-0.66, -0.2, 0.20);
	glVertex3d(-0.78, 0, 0.20);

	glColor3d(0.4, 0.4, 0.4);

	glVertex3d(-0.42, 0, 0.20);
	glVertex3d(-0.58, 0, 0.20);
	glVertex3d(-0.42, -0.16, 0.3);

	glVertex3d(-0.42, -0.16, 0.3);
	glVertex3d(-0.58, -0.16, 0.3);
	glVertex3d(-0.58, 0, 0.20);

	glVertex3d(-0.42, 0, 0.20);
	glVertex3d(-0.58, 0, 0.20);
	glVertex3d(-0.42, 0.16, 0.3);

	glVertex3d(-0.42, 0.16, 0.3);
	glVertex3d(-0.58, 0.16, 0.3);
	glVertex3d(-0.58, 0, 0.20);

	glVertex3d(-0.42, -0.16, 0.3);
	glVertex3d(-0.58, -0.16, 0.3);
	glVertex3d(-0.58, 0, 0.33);

	glVertex3d(-0.58, 0, 0.33);
	glVertex3d(-0.42, 0, 0.33);
	glVertex3d(-0.42, -0.16, 0.3);

	glVertex3d(-0.42, 0.16, 0.3);
	glVertex3d(-0.58, 0.16, 0.3);
	glVertex3d(-0.58, 0, 0.33);

	glVertex3d(-0.58, 0, 0.33);
	glVertex3d(-0.42, 0, 0.33);
	glVertex3d(-0.42, 0.16, 0.3);


	glColor3d(0.55, 0.55, 0.55);
	glVertex3d(-0.42, 0, 0.20);
	glVertex3d(-0.42, -0.16, 0.3);
	glVertex3d(-0.42, 0.16, 0.3);

	glVertex3d(-0.58, 0, 0.20);
	glVertex3d(-0.58, -0.16, 0.3);
	glVertex3d(-0.58, 0.16, 0.3);

	glVertex3d(-0.58, -0.16, 0.3);
	glVertex3d(-0.58, 0.16, 0.3);
	glVertex3d(-0.58, 0, 0.33);

	glVertex3d(-0.42, 0, 0.33);
	glVertex3d(-0.42, -0.16, 0.3);
	glVertex3d(-0.42, 0.16, 0.3);


	glEnd();
	//glBegin(GL_QUADS);

	////низ
	//glColor3d(0.7, 0.7, 0.7);
	//glVertex3d(P1[0], P1[1], P1[2]);
	//glVertex3d(P1[0], P1[1] + 1, P1[2]);
	//glVertex3d(P1[0], P1[1] + 1, P1[2] + 1);
	//glVertex3d(P1[0], P1[1], P1[2] + 1);


	//glEnd();
	////треуг
	//glBegin(GL_TRIANGLES);
	//glColor3d(0.1, 0.1, 0.1);
	//glVertex3d(P1[0], P1[1], P1[2]);
	//glVertex3d(P1[0], P1[1] + 1, P1[2]);
	//glVertex3d(0.5, 0, 0);


	//glColor3d(0.2, 0.2, 0.2);
	//glVertex3d(P1[0], P1[1] + 1, P1[2]);
	//glVertex3d(P1[0], P1[1] + 1, P1[2] + 1);
	//glVertex3d(0.5, 0, 0);

	//glColor3d(0.3, 0.3, 0.3);
	//glVertex3d(P1[0], P1[1] + 1, P1[2] + 1);
	//glVertex3d(P1[0], P1[1], P1[2] + 1);
	//glVertex3d(0.5, 0, 0);

	//glColor3d(0.9, 0.9, 0.9);
	//glVertex3d(P1[0], P1[1], P1[2] + 1);
	//glVertex3d(P1[0], P1[1], P1[2]);
	//glVertex3d(0.5, 0, 0);
	//glEnd();

	//
	//glBegin(GL_LINES);
	//glColor3d(1, 0, 0);
	//glVertex3d(0, 0, 0);
	//glVertex3d(1, 0, 0);

	//glColor3d(0, 1, 0);
	//glVertex3d(0, 0, 0);
	//glVertex3d(0, 1, 0);

	//glColor3d(0, 0, 1);
	//glVertex3d(0, 0, 0);
	//glVertex3d(0, 0, 1);
	//glEnd();
}


void BezeWithFigure(double P1[3], double P2[3], double P3[3], double P4[3], double delta_time)
{
	static double t_max = 0;
	static bool flagReverse = false;

	if (!flagReverse)
	{
		t_max += delta_time / 5; //t_max становится = 1 за 5 секунд
		if (t_max > 1)
		{
			t_max = 1; //после обнуляется
			flagReverse = !flagReverse;
		}
	}
	else
	{
		t_max -= delta_time / 5; //t_max становится = 1 за 5 секунд
		if (t_max < 0)
		{
			t_max = 0; //после обнуляется
			flagReverse = !flagReverse;
		}
	}

	Beze(P1, P2, P3, P4);

	
	MVect P_old = BezeWithoutDraw(P1, P2, P3, P4, !flagReverse ? t_max - delta_time : t_max + delta_time);
	MVect P = BezeWithoutDraw(P1, P2, P3, P4, t_max);
	MVect VecP_P_old = (P - P_old).normalize();

	MVect rotateX(VecP_P_old.X(), VecP_P_old.Y(), 0);
	rotateX = rotateX.normalize();

	MVect VecPrX = MVect(1, 0, 0).vectProisvedenie(rotateX);
	double CosX = MVect(1, 0, 0).scalarProizv(rotateX);
	double SinAngleZ = VecPrX.Z() / abs(VecPrX.Z());
	double AngleOZ = acos(CosX) * 180 / PI * SinAngleZ;

	double AngleOY = acos(VecP_P_old.Z()) * 180 / PI - 90;

	double A[] = { -0.5,-0.5,-0.5 };
	glPushMatrix();
	glTranslated(P.X(), P.Y(), P.Z());
	glRotated(AngleOZ, 0, 0, 1);
	glRotated(AngleOY, 0, 1, 0);
	DrawFig(A);
	glPopMatrix();

	glColor3d(0, 0, 0);

}

void Render(double delta_time)
{
	double P1[] = { 0,0,0 }; //точки
	double P2[] = { 4,4,3 };
	double P3[] = { 0,8,2 };
	double P4[] = { -2,2,6 };

	BezeWithFigure(P1, P2, P3, P4, delta_time);
	
	double h = 0.05;
	for (double u = 0; u < 1.01 - h; u += h)
	{
		glBegin(GL_LINE_STRIP);
		for (double v = 0; v < 1.01 - h; v += h)
		{
			BezePointsSurf(u, v);
		}
		glEnd();
	}
	glPointSize(5);
	glColor3d(1, 0, 0);
	glBegin(GL_POINTS);
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			glVertex3dv(points[i][j].toArray());
		}
	}
	glEnd();
}

