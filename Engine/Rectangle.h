#ifndef Rectangle_h
#define Rectangle_h

#include "ShapeObject.h"

class Rectangle : public ShapeObject {
public:
	Rectangle(Point2D firstCorner, Point2D oppositeCorner);
	~Rectangle();

	virtual void draw(BITMAP * bitmap, Viewport viewport, int color) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) override;
};

#endif
