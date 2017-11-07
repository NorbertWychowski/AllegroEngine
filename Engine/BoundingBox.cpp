#include "BoundingBox.h"

#include "LineSegment.h"

BoundingBox::BoundingBox(int x, int y, int width, int height) {
	firstCorner.setXY(x, y);
	oppositeCorner.setXY(x + width, y + height);

	this->width = width;
	this->height = height;
}

BoundingBox::BoundingBox(Point2D firstCorner, Point2D oppositeCorner) {
	if (firstCorner.getX() < oppositeCorner.getX()) {
		this->firstCorner.setX(firstCorner.getX());
		this->oppositeCorner.setX(oppositeCorner.getX());
	} else {
		this->firstCorner.setX(oppositeCorner.getX());
		this->oppositeCorner.setX(firstCorner.getX());
	}
	if (firstCorner.getY() < oppositeCorner.getY()) {
		this->firstCorner.setY(firstCorner.getY());
		this->oppositeCorner.setY(oppositeCorner.getY());
	} else {
		this->firstCorner.setY(oppositeCorner.getY());
		this->oppositeCorner.setY(firstCorner.getY());
	}

	width = oppositeCorner.getX() - firstCorner.getX();
	height = oppositeCorner.getY() - firstCorner.getY();
}

bool BoundingBox::isCollision(BoundingBox boundingBox) {
	if ((getX() + width) >= boundingBox.getX() && getX() <= (boundingBox.getX() + boundingBox.getWidth()) &&
		(getY() + height) >= boundingBox.getY() && getY() <= (boundingBox.getY() + boundingBox.getHeight())) {
		return true;
	} else {
		return false;
	}
}

void BoundingBox::drawBoundingBox(BITMAP * bitmap, int color, LineStyle lineStyle) {
	LineSegment::drawLineS(bitmap, Point2D(firstCorner.getX(), firstCorner.getY()),
		Point2D(firstCorner.getX(), oppositeCorner.getY()), color, lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(firstCorner.getX(), firstCorner.getY()),
		Point2D(oppositeCorner.getX(), firstCorner.getY()), color, lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(oppositeCorner.getX(), oppositeCorner.getY()),
		Point2D(firstCorner.getX(), oppositeCorner.getY()), color, lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(oppositeCorner.getX(), oppositeCorner.getY()),
		Point2D(oppositeCorner.getX(), firstCorner.getY()), color, lineStyle);
}

void BoundingBox::drawBoundingBox(BITMAP * bitmap, float r, float g, float b, LineStyle lineStyle) {
	LineSegment::drawLineS(bitmap, Point2D(firstCorner.getX(), firstCorner.getY()),
		Point2D(firstCorner.getX(), oppositeCorner.getY()), makecol(r * 255, g * 255, b * 255), lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(firstCorner.getX(), firstCorner.getY()),
		Point2D(oppositeCorner.getX(), firstCorner.getY()), makecol(r * 255, g * 255, b * 255), lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(oppositeCorner.getX(), oppositeCorner.getY()),
		Point2D(firstCorner.getX(), oppositeCorner.getY()), makecol(r * 255, g * 255, b * 255), lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(oppositeCorner.getX(), oppositeCorner.getY()),
		Point2D(oppositeCorner.getX(), firstCorner.getY()), makecol(r * 255, g * 255, b * 255), lineStyle);
}

void BoundingBox::drawBoundingBox(BITMAP * bitmap, int r, int g, int b, LineStyle lineStyle) {
	LineSegment::drawLineS(bitmap, Point2D(firstCorner.getX(), firstCorner.getY()),
		Point2D(firstCorner.getX(), oppositeCorner.getY()), makecol(r, g, b), lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(firstCorner.getX(), firstCorner.getY()),
		Point2D(oppositeCorner.getX(), firstCorner.getY()), makecol(r, g, b), lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(oppositeCorner.getX(), oppositeCorner.getY()),
		Point2D(firstCorner.getX(), oppositeCorner.getY()), makecol(r, g, b), lineStyle);
	LineSegment::drawLineS(bitmap, Point2D(oppositeCorner.getX(), oppositeCorner.getY()),
		Point2D(oppositeCorner.getX(), firstCorner.getY()), makecol(r, g, b), lineStyle);
}

void BoundingBox::setFirstCorner(Point2D point) {
	if (point.getX() < firstCorner.getX()) {
		this->firstCorner.setX(point.getX());
	} else {
		this->firstCorner.setX(oppositeCorner.getX());
		this->oppositeCorner.setX(point.getX());
	}
	if (point.getY() < firstCorner.getY()) {
		this->firstCorner.setY(point.getY());
	} else {
		this->firstCorner.setY(oppositeCorner.getY());
		this->oppositeCorner.setY(point.getY());
	}
}

void BoundingBox::setOppositeCorner(Point2D point) {
	if (point.getX() > firstCorner.getX()) {
		this->firstCorner.setX(point.getX());
	} else {
		this->firstCorner.setX(oppositeCorner.getX());
		this->oppositeCorner.setX(point.getX());
	}
	if (point.getY() > firstCorner.getY()) {
		this->firstCorner.setY(point.getY());
	} else {
		this->firstCorner.setY(oppositeCorner.getY());
		this->oppositeCorner.setY(point.getY());
	}
}

void BoundingBox::setX(int x) {
	firstCorner.setX(x);
	oppositeCorner.setX(x + width);
}

void BoundingBox::setY(int y) {
	firstCorner.setX(y);
	oppositeCorner.setX(y + height);
}

void BoundingBox::setWidth(int width) {
	oppositeCorner.setX(firstCorner.getX() + abs(width));
	this->width = width;
}

void BoundingBox::setHeight(int height) {
	oppositeCorner.setY(firstCorner.getY() + abs(height));
	this->height = height;
}

Point2D BoundingBox::getFirstCorner() {
	return firstCorner;
}

Point2D BoundingBox::getOppositeCorner() {
	return oppositeCorner;
}

int BoundingBox::getWidth() {
	return width;
}

int BoundingBox::getHeight() {
	return height;
}

int BoundingBox::getX() {
	return firstCorner.getX();
}

int BoundingBox::getY() {
	return firstCorner.getY();
}
