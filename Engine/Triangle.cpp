#include "Triangle.h"

Triangle::Triangle(Point2D p1, Point2D p2, Point2D p3) {
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
}

void Triangle::draw(BITMAP * bitmap, Viewport viewport, int color) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap, points[0], points[1]),
		LineSegment(bitmap, points[1], points[2]), LineSegment(bitmap, points[0], points[2]) }))
		l.drawLine(color);
}

void Triangle::draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap, points[0], points[1]),
		LineSegment(bitmap, points[1], points[2]), LineSegment(bitmap, points[0], points[2]) }))
		l.drawLine(makecol(r * 255, g * 255, b * 255));
}

void Triangle::draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap, points[0], points[1]),
		LineSegment(bitmap, points[1], points[2]), LineSegment(bitmap, points[0], points[2]) }))
		l.drawLine(makecol(r, g, b));
}
