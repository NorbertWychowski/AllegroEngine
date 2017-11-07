#ifndef Viewport_h
#define Viewport_h

#include <vector>

#include "LineSegment.h"

class Viewport {
public:
	Viewport();
	Viewport(Point2D firstCorner, Point2D oppositeCorner);
	~Viewport();

	void drawViewport(BITMAP *bitmap, int color, LineStyle lineStyle = DashLine);
	void drawViewport(BITMAP *bitmap, float r, float g, float b, LineStyle lineStyle = DashLine);
	void drawViewport(BITMAP *bitmap, int r, int g, int b, LineStyle lineStyle = DashLine);

	void setViewport(Point2D firstCorner, Point2D oppositeCorner);

	Point2D getFirstCorner();
	Point2D getOppositeCorner();

	std::vector<LineSegment> cutLine(LineSegment line);
	std::vector<LineSegment> cutLines(std::vector<LineSegment> lines);
	void drawPixel(Point2D point, BITMAP* bitmap, int color);
	void drawPixel(Point2D point, BITMAP* bitmap, float r, float g, float b);
	void drawPixel(Point2D point, BITMAP* bitmap, int r, int g, int b);
	bool isInViewport(Point2D point);

private:
	Point2D firstCorner;
	Point2D oppositeCorner;

	template <class T>
	void swap(T &a, T &b);
};

template<class T>
inline void Viewport::swap(T & a, T & b) {
	T tmp = a;
	a = b;
	b = tmp;
}

#endif
