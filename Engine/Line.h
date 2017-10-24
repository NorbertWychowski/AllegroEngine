#ifndef Line_h
#define Line_h

#include "ShapeObject.h"

class Line : public ShapeObject {
public:
	Line(Point2D p1, Point2D p2, LineStyle lineStyle = SolidLine);
	~Line();

	virtual void draw(BITMAP * bitmap, Viewport viewport, int color) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) override;

private:
	LineStyle lineStyle;
};

#endif