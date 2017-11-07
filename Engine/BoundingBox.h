#ifndef BoundingBox_h
#define BoundingBox_h

#include "Point2D.h"
#include "LineSegment.h"

class BoundingBox {
public:
	BoundingBox(int x, int y, int width, int height);
	BoundingBox(Point2D firstCorner, Point2D oppositeCorner);

	bool isCollision(BoundingBox boundingBox);
	void drawBoundingBox(BITMAP *bitmap, int color, LineStyle lineStyle = DashLine);
	void drawBoundingBox(BITMAP *bitmap, float r, float g, float b, LineStyle lineStyle = DashLine);
	void drawBoundingBox(BITMAP *bitmap, int r, int g, int b, LineStyle lineStyle = DashLine);

	void setFirstCorner(Point2D point);
	void setOppositeCorner(Point2D point);
	void setX(int x);
	void setY(int y);
	void setWidth(int width);
	void setHeight(int height);

	Point2D getFirstCorner();
	Point2D getOppositeCorner();
	int getWidth();
	int getHeight();
	int getX();
	int getY();

private:
	Point2D firstCorner;
	Point2D oppositeCorner;
	int width, height;
};

#endif
