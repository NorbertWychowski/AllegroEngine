#ifndef Viewport_h
#define Viewport_h

#include <vector>

#include "LineSegment.h"

#include <allegro.h>

class Viewport {
public:
	Viewport(Point2D firstCorner, Point2D oppositeCorner);
	~Viewport();

	void drawViewport(BITMAP *bitmap, int color);
	void drawViewport(BITMAP *bitmap, float r, float g, float b);

	void setViewport(Point2D firstCorner, Point2D oppositeCorner);

	std::vector<LineSegment> cutLine(LineSegment line);
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
	b = a;
}
