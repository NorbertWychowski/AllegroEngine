#ifndef LineSegment_h
#define LineSegment_h

#include "Point2D.h"

#include <allegro.h>

class LineSegment {
public:
	LineSegment(BITMAP *bitmap, Point2D p1, Point2D p2);
	~LineSegment();

	void drawLine(int color);
	void drawLine(float r, float g, float b);
	static void drawLineS(BITMAP *bitmap, Point2D p1, Point2D p2, int color);
	static void drawLineS(BITMAP *bitmap, Point2D p1, Point2D p2, float r, float g, float b);

	void setP1(Point2D p1);
	void setP2(Point2D p2);

	Point2D getP1();
	Point2D getP2();

private:
	BITMAP *bitmap;
	Point2D p1;
	Point2D p2;

	static void drawLineA(BITMAP *bitmap, Point2D p1, Point2D p2, int color);
};

#endif
