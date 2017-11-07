#ifndef Triangle_h
#define Triangle_h

#include "ShapeObject.h"

class Triangle : public ShapeObject {
public:
	Triangle(Point2D p1, Point2D p2, Point2D p3);

	virtual void draw(BITMAP * bitmap, Viewport viewport, int color) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) override;
};

#endif
