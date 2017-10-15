#include "Viewport.h"

Viewport::Viewport(Point2D firstCorner, Point2D oppositeCorner) {
	setViewport(firstCorner, oppositeCorner);
}

Viewport::~Viewport() {
}

void Viewport::drawViewport(BITMAP * bitmap, int color) {
	line(bitmap, firstCorner.getX(), firstCorner.getY(), firstCorner.getX(), oppositeCorner.getY(), color);
	line(bitmap, firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), firstCorner.getY(), color);
	line(bitmap, oppositeCorner.getX(), oppositeCorner.getY(), firstCorner.getX(), oppositeCorner.getY(), color);
	line(bitmap, oppositeCorner.getX(), oppositeCorner.getY(), oppositeCorner.getX(), firstCorner.getY(), color);
}

void Viewport::drawViewport(BITMAP * bitmap, float r, float g, float b) {
	line(bitmap, firstCorner.getX(), firstCorner.getY(), firstCorner.getX(), oppositeCorner.getY(), makecol(r * 255, g * 255, b * 255));
	line(bitmap, firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), firstCorner.getY(), makecol(r * 255, g * 255, b * 255));
	line(bitmap, oppositeCorner.getX(), oppositeCorner.getY(), firstCorner.getX(), oppositeCorner.getY(), makecol(r * 255, g * 255, b * 255));
	line(bitmap, oppositeCorner.getX(), oppositeCorner.getY(), oppositeCorner.getX(), firstCorner.getY(), makecol(r * 255, g * 255, b * 255));
}

void Viewport::setViewport(Point2D firstCorner, Point2D oppositeCorner) {
	int x1, x2, y1, y2;

	if (firstCorner.getX() < oppositeCorner.getX()) {
		x1 = firstCorner.getX();
		x2 = oppositeCorner.getX();
	}
	else {
		x2 = firstCorner.getX();
		x1 = oppositeCorner.getX();
	}

	if (firstCorner.getY() < oppositeCorner.getY()) {
		y1 = firstCorner.getY();
		y2 = oppositeCorner.getY();
	}
	else {
		y2 = firstCorner.getY();
		y1 = oppositeCorner.getY();
	}
	this->firstCorner = Point2D(x1, y1);
	this->oppositeCorner = Point2D(x2, y2);
}

std::vector<LineSegment> Viewport::cutLine(LineSegment line) {
	std::vector<LineSegment> tmp;
	int x1 = line.getP1().getX();
	int x2 = line.getP2().getX();
	int y1 = line.getP1().getY();
	int y2 = line.getP2().getY();
	char codeP1 = 0;
	char codeP2 = 0;

	//hehe
step1:
	if (x1 < firstCorner.getX()) {
		codeP1 += (1 < 0);
	}
	else if (x1 > oppositeCorner.getX()) {
		codeP1 += (1 << 1);
	}
	if (y1 < firstCorner.getY()) {
		codeP1 += (1 << 2);
	}
	else if (y1 > oppositeCorner.getY()) {
		codeP1 += (1 << 3);
	}

	if (x2 < firstCorner.getX()) {
		codeP2 += (1 < 0);
	}
	else if (x2 > oppositeCorner.getX()) {
		codeP2 += (1 << 1);
	}
	if (y2 < firstCorner.getY()) {
		codeP2 += (1 << 2);
	}
	else if (y2 > oppositeCorner.getY()) {
		codeP2 += (1 << 3);
	}

	if (codeP1 == 0 && codeP2 == 0) {
		LineSegment l = line;
		l.setP1(Point2D(x1, y1));
		l.setP2(Point2D(x2, y2));
		tmp.push_back(l);
		return tmp;
	}
	else if (codeP1 & codeP2 != 0) {
		LineSegment l = line;
		l.setP1(Point2D(x1, y1));
		l.setP2(Point2D(x2, y2));
		tmp.push_back(l);
		return tmp;
	}
	else {
		if (codeP1 == 0) {
			swap(codeP1, codeP2);
			swap(x1, x2);
			swap(y1, y2);
		}

		if (codeP1 & (1 << 0) == (1 << 0)) {
			y1 = y1 + (firstCorner.getX() - x1)*(y2 - y1) / (x2 - x1);
			x1 = firstCorner.getX();
			goto step1;
		}
		if (codeP1 & (1 << 1) == (1 << 1)) {
			y1 = y1 + (oppositeCorner.getX() - x1)*(y2 - y1) / (x2 - x1);
			x1 = oppositeCorner.getX();
			goto step1;
		}
		if (codeP1 & (1 << 2) == (1 << 2)) {
			x1 = x1 + (oppositeCorner.getY() - y1)*(x2 - x1) / (y2 - y1);
			y1 = oppositeCorner.getY();
			goto step1;
		}
		if (codeP1 & (1 << 3) == (1 << 3)) {
			x1 = x1 + (firstCorner.getY() - y1)*(x2 - x1) / (y2 - y1);
			y1 = firstCorner.getY();
			goto step1;
		}
	}
	return tmp;
}
