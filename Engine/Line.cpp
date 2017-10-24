#include "Line.h"



Line::Line(Point2D p1, Point2D p2, LineStyle lineStyle) {
	points.push_back(p1);
	points.push_back(p2);
	this->lineStyle = lineStyle;
}


Line::~Line() {
}

void Line::draw(BITMAP * bitmap, Viewport viewport, int color) {
	viewport.cutLine(LineSegment(bitmap, points[0], points[1], lineStyle))[0].drawLine(color);
}

void Line::draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) {
	viewport.cutLine(LineSegment(bitmap, points[0], points[1], lineStyle))[0].drawLine(makecol(r * 255, g * 255, b * 255));
}

void Line::draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) {
	viewport.cutLine(LineSegment(bitmap, points[0], points[1], lineStyle))[0].drawLine(makecol(r, g, b));
}
