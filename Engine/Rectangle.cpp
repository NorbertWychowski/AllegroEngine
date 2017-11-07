#include "Rectangle.h"

Rectangle::Rectangle(Point2D firstCorner, Point2D oppositeCorner) : BoundingBox(firstCorner, oppositeCorner) {
	points.push_back(firstCorner);
	points.push_back(Point2D(firstCorner.getX(), oppositeCorner.getY()));
	points.push_back(oppositeCorner);
	points.push_back(Point2D(oppositeCorner.getX(), firstCorner.getY()));
}

void Rectangle::draw(BITMAP * bitmap, Viewport viewport, int color) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap, points[0], points[1]), LineSegment(bitmap, points[1], points[2]),
		LineSegment(bitmap, points[2], points[3]), LineSegment(bitmap, points[3], points[0]) }))
		l.drawLine(color);
}

void Rectangle::draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap, points[0], points[1]), LineSegment(bitmap, points[1], points[2]),
		LineSegment(bitmap, points[2], points[3]), LineSegment(bitmap, points[3], points[0]) }))
		l.drawLine(makecol(r * 255, g * 255, b * 255));
}

void Rectangle::draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap, points[0], points[1]), LineSegment(bitmap, points[1], points[2]),
		LineSegment(bitmap, points[2], points[3]), LineSegment(bitmap, points[3], points[0]) }))
		l.drawLine(makecol(r, g, b));
}

