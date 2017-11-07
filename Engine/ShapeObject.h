#ifndef ShapeObject_h
#define ShapeObject_h

#include <vector>

#include "LineSegment.h"
#include "Point2D.h"
#include "Viewport.h"

class ShapeObject {
public:
	virtual void draw(BITMAP *bitmap, Viewport viewport, int color) = 0;
	virtual void draw(BITMAP *bitmap, Viewport viewport, float r, float g, float b) = 0;
	virtual void draw(BITMAP *bitmap, Viewport viewport, int r, int g, int b) = 0;

	void translate(int tx, int ty);
	void rotate(float alpha);
	void rotate(float alpha, int x0, int y0);
	void scale(float k);
	void scale(float k, int x0, int y0);

	virtual ~ShapeObject();

protected:
	std::vector<Point2D> points;
};

#endif