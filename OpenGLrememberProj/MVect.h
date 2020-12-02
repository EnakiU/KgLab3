#ifndef  MVECT_H
#define  MVECT_H

//а кто найдет этот фйлик тот молодец.
//тут как раз описывается тип вектор, которые можно сказдывать, умножать
// искать... ВЕКТОРНОЕ произведение итд)

#include <math.h>
#include "angle.h"
#include <string>
#include <cstdlib>
#include <stdlib.h> 

//Обычковенный 3хкомпонентный вектор
class MVect
{
	double coords[3];

public:

	inline double X()
	{
		return coords[0];
	}
	inline double Y()
	{
		return coords[1];
	}
	inline double Z()
	{
		return coords[2];
	}

	//перевод из сферических координат
	
	inline void setCoords(double x, double y, double z)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
	}

	inline MVect(double x, double y, double z)
	{
		coords[0] = x;
		coords[1] = y;
		coords[2] = z;
	}
	inline MVect()
	{
		coords[0] = 0;
		coords[1] = 0;
		coords[2] = 0;
	}

	inline MVect operator + (MVect& vec)
	{
		MVect newV;
		newV.coords[0] = coords[0] + vec.coords[0];
		newV.coords[1] = coords[1] + vec.coords[1];
		newV.coords[2] = coords[2] + vec.coords[2];
		return newV;
	}

	inline MVect operator - (MVect& vec)
	{
		MVect newV;
		newV.coords[0] = coords[0] - vec.coords[0];
		newV.coords[1] = coords[1] - vec.coords[1];
		newV.coords[2] = coords[2] - vec.coords[2];
		return newV;
	}

	inline MVect operator * (double k)
	{
		MVect newV;
		newV.coords[0] = coords[0] * k;
		newV.coords[1] = coords[1] * k;
		newV.coords[2] = coords[2] * k;
		return newV;
	}

	inline void operator = (MVect vec)
	{
		coords[0] = vec.coords[0];
		coords[1] = vec.coords[1];
		coords[2] = vec.coords[2];
	}

	MVect operator += (const MVect& a) {
		return { this->coords[0] += a.coords[0], this->coords[1] += a.coords[1], this->coords[2] += a.coords[2] };
	}

	inline double length()
	{
		return (sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]));
	}

	inline MVect normalize()
	{
		MVect newV;
		double l = length();
		newV.setCoords(coords[0] / l, coords[1] / l, coords[2] / l);
		return newV;
	}

	inline double scalarProizv(const MVect& vec)
	{
		return this->coords[0] * vec.coords[0] + this->coords[1] * vec.coords[1] + this->coords[2] * vec.coords[2];
	}

	inline MVect vectProisvedenie(MVect& v)
	{
		MVect V;
		V.setCoords(coords[1] * v.coords[2] - coords[2] * v.coords[1],
			coords[2] * v.coords[0] - coords[0] * v.coords[2],
			coords[0] * v.coords[1] - coords[1] * v.coords[0]);
		return V;
	}

	inline const double* toArray(void)
	{
		return (coords);
	}

	inline void SetCoordX(double a)
	{
		this->coords[0] = a;
	}
	inline void SetCoordY(double a)
	{
		this->coords[1] = a;
	}
	inline void SetCoordZ(double a)
	{
		this->coords[2] = a;
	}

};

#endif
