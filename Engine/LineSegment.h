#ifndef LineSegment_h
#define LineSegment_h

#include "Point2D.h"

#include <allegro.h>

enum LineStyle {
	SolidLine = 1,
	DashLine = 2
};

class LineSegment {
public:
	LineSegment(BITMAP *bitmap, Point2D p1, Point2D p2, LineStyle lineStyle = SolidLine);
	~LineSegment();

	void drawLine(int color);
	void drawLine(float r, float g, float b);
	static void drawLineS(BITMAP *bitmap, Point2D p1, Point2D p2, int color, LineStyle lineStyle = SolidLine);
	static void drawLineS(BITMAP *bitmap, Point2D p1, Point2D p2, float r, float g, float b, LineStyle lineStyle = SolidLine);

	void setP1(Point2D p1);
	void setP2(Point2D p2);
	void setLineStyle(LineStyle lineStyle);

	Point2D getP1();
	Point2D getP2();

private:
	BITMAP *bitmap;
	Point2D p1;
	Point2D p2;
	LineStyle lineStyle;

	static void drawLineA(BITMAP *bitmap, Point2D p1, Point2D p2, int color, LineStyle lineStyle);
};

#endif
