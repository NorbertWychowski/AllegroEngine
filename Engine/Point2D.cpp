#include "Point2D.h"

Point2D::Point2D() {
}

Point2D::Point2D(int x, int y) {
	this->x = x;
	this->y = y;
}

Point2D::~Point2D() {
}

int Point2D::getX() {
	return x;
}

int Point2D::getY() {
	return y;
}
