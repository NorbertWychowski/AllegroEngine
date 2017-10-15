#include "LineSegment.h"


LineSegment::LineSegment(BITMAP * bitmap, Point2D p1, Point2D p2, LineStyle lineStyle) {
	this->bitmap = bitmap;
	this->p1 = p1;
	this->p2 = p2;
	this->lineStyle = lineStyle;
}

LineSegment::~LineSegment()
{
}

void LineSegment::drawLine(int color) {
	drawLineA(this->bitmap, this->p1, this->p2, color, lineStyle);
}

void LineSegment::drawLine(float r, float g, float b) {
	drawLineA(this->bitmap, this->p1, this->p2, makecol(r * 255, g * 255, b * 255), lineStyle);
}

void LineSegment::drawLineS(BITMAP * bitmap, Point2D p1, Point2D p2, int color, LineStyle lineStyle) {
	drawLineA(bitmap, p1, p2, color, lineStyle);
}

void LineSegment::drawLineS(BITMAP * bitmap, Point2D p1, Point2D p2, float r, float g, float b, LineStyle lineStyle) {
	drawLineA(bitmap, p1, p2, makecol(r * 255, g * 255, b * 255), lineStyle);
}

void LineSegment::setP1(Point2D p1) {
	this->p1 = p1;
}

void LineSegment::setP2(Point2D p2) {
	this->p2 = p2;
}

void LineSegment::setLineStyle(LineStyle lineStyle) {
	this->lineStyle = lineStyle;
}

Point2D LineSegment::getP1() {
	return p1;
}

Point2D LineSegment::getP2() {
	return p2;
}

void LineSegment::drawLineA(BITMAP * bitmap, Point2D p1, Point2D p2, int color, LineStyle lineStyle) {
	double tmpY, tmpX;
	int x1 = p1.getX();
	int x2 = p2.getX();
	int y1 = p1.getY();
	int y2 = p2.getY();
	double delta;

	if (x1 != x2) {
		delta = (double)(y1 - y2) / (x1 - x2);
	} else if ((x1 == x2) && (y1 == y2)){
		return;
	} else {
		delta = 2.0;
	}

	if (abs(delta) > 1) {
		if (y1 != y2) {
			delta = 1.0*(x1 - x2) / (y1 - y2);
		}

		if (y1 < y2) {
			tmpX = x1;
			for (int i = y1; i != y2; i++) {
				tmpX += delta;
				if (lineStyle == SolidLine)
					putpixel(bitmap, round(tmpX), i, color);
				else if (lineStyle == DashLine) {
					if (i % 8 < 5)
						putpixel(bitmap, round(tmpX), i, color);
				}
			}
		}
		else {
			tmpX = x2;
			for (int i = y2; i != y1; i++) {
				tmpX += delta;
				if (lineStyle == SolidLine)
					putpixel(bitmap, round(tmpX), i, color);
				else if (lineStyle == DashLine) {
					if (i % 8 < 5)
						putpixel(bitmap, round(tmpX), i, color);
				}
			}
		}
	}
	else {
		if (x1 < x2) {
			tmpY = y1;
			for (int i = x1; i != x2; i++) {
				tmpY += delta;
				if (lineStyle == SolidLine)
					putpixel(bitmap, i, round(tmpY), color);
				else if (lineStyle == DashLine) {
					if (i % 8 < 5)
						putpixel(bitmap, i, round(tmpY), color);
				}
			}
		}
		else {
			tmpY = y2;
			for (int i = x2; i != x1; i++) {
				tmpY += delta;
				if (lineStyle == SolidLine)
					putpixel(bitmap, i, round(tmpY), color);
				else if (lineStyle == DashLine) {
					if (i % 8 < 5)
						putpixel(bitmap, i, round(tmpY), color);
				}
			}
		}
	}
}
