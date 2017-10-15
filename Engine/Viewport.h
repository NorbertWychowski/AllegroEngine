#ifndef Viewport_h
#define Viewport_h

#include <vector>

#include "LineSegment.h"

#include <allegro.h>

class Viewport {
public:
	Viewport();
	Viewport(Point2D firstCorner, Point2D oppositeCorner);
	~Viewport();

	void drawViewport(BITMAP *bitmap, int color, LineStyle lineStyle = DashLine);
	void drawViewport(BITMAP *bitmap, float r, float g, float b, LineStyle lineStyle = DashLine);

	void setViewport(Point2D firstCorner, Point2D oppositeCorner);

	std::vector<LineSegment> cutLine(LineSegment line);
	std::vector<LineSegment> cutLines(std::vector<LineSegment> lines);
private:
	Point2D firstCorner;
	Point2D oppositeCorner;

	template <class T>
	void swap(T &a, T &b);
};

#endif

template<class T>
inline void Viewport::swap(T & a, T & b) {
	T tmp = a;
	a = b;
	b = tmp;
}
