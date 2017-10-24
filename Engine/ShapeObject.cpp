#if _MSC_VER && !__INTEL_COMPILER
#define _USE_MATH_DEFINES
#endif

#include "ShapeObject.h"

void ShapeObject::translate(int tx, int ty) {
	int x, y;
	for (Point2D &p : points) {
		//jesli metody get, set sa duzo razy wywolywane to czasem jakiejs nie zdazy wywolac 
		//(czy cos takiego, nie wiem po prostu moze nie dzialac), dlatego uzywam zmiennych x y
		x = p.getX();
		y = p.getY();
		p.setXY(x + tx, y - ty);
	}
}

void ShapeObject::rotate(float alpha) {
	float x, y;
	float a = alpha * M_PI / 180.0;
	for (Point2D &p : points) {
		x = p.getX() * cosf(a) - p.getY() * sinf(a);
		y = p.getX() * sinf(a) + p.getY() * cosf(a);
		p.setXY(x, y);
	}
}

void ShapeObject::rotate(float alpha, int x0, int y0) {
	float x, y;
	float a = alpha * M_PI / 180.0;
	for (Point2D &p : points) {
		x = x0 + (p.getX() - x0)*cosf(a) - (p.getY() - y0)*sinf(a);
		y = y0 + (p.getX() - x0)*sinf(a) + (p.getY() - y0)*cosf(a);
		p.setXY(x, y);
	}
}

void ShapeObject::scale(float k) {
	float x, y;
	for (Point2D &p : points) {
		x = p.getX()*k;
		y = p.getY()*k;
		p.setXY(x, y);
	}
}

void ShapeObject::scale(float k, int x0, int y0) {
	float x, y;
	for (Point2D &p : points) {
		x = p.getX()*k + (1.0 - k)*x0;
		y = p.getY()*k + (1.0 - k)*y0;
		p.setXY(x, y);
	}
}

ShapeObject::~ShapeObject() {
}
