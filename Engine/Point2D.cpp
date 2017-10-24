#include "Point2D.h"

Point2D::Point2D() {
}

Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
}

Point2D::~Point2D() {
}

float Point2D::getX() {
	return x;
}

float Point2D::getY() {
	return y;
}

void Point2D::setX(float x) {
	this->x = x;
}

void Point2D::setY(float y) {
	this->y = y;
}

void Point2D::setXY(float x, float y) {
	this->x = x;
	this->y = y;
}
