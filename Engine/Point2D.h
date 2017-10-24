#ifndef Point2D_h
#define Point2D_h

#include <vector>

class Point2D {
public:
	Point2D();
	Point2D(float x, float y);
	~Point2D();

	float getX();
	float getY();

	void setX(float x);
	void setY(float y);
	void setXY(float x, float y);

private:
	float x, y;
};

#endif
