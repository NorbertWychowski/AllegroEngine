#ifndef Polygon_h
#define Polygon_h

#include "ShapeObject.h"

class Polygon : public ShapeObject {
public:
	Polygon(std::vector<Point2D> points, bool openPolygon, LineStyle lineStyle = SolidLine);

	virtual void draw(BITMAP * bitmap, Viewport viewport, int color) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, float r, float g, float b) override;
	virtual void draw(BITMAP * bitmap, Viewport viewport, int r, int g, int b) override;

private:
	LineStyle lineStyle;
	bool openPolygon;
};

#endif