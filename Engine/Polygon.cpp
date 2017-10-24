#include "Polygon.h"


Polygon::Polygon(std::vector<Point2D> points, bool openPolygon, LineStyle lineStyle) {
	this->points = points;
	this->lineStyle = lineStyle;
	this->openPolygon = openPolygon;
}

Polygon::~Polygon() {
}

void Polygon::draw(BITMAP * bitmap, Viewport viewport, int color) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap, points[i], points[i + 1], lineStyle))[0].drawLine(color);
	}
	if (!points.empty() && !openPolygon)
		viewport.cutLine(LineSegment(bitmap, points.front(), points.back(), lineStyle))[0].drawLine(color);
}

void Polygon::draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap, points[i], points[i + 1], lineStyle))[0].drawLine(makecol(r * 255, g * 255, b * 255));
	}
	if (!points.empty() && !openPolygon)
		viewport.cutLine(LineSegment(bitmap, points.front(), points.back(), lineStyle))[0].drawLine(makecol(r*255, g*255, b*255));

}

void Polygon::draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap, points[i], points[i + 1], lineStyle))[0].drawLine(makecol(r, g, b));
	}
	if (!points.empty() && !openPolygon)
		viewport.cutLine(LineSegment(bitmap, points.front(), points.back(), lineStyle))[0].drawLine(makecol(r, g, b));

}
