#ifndef Point2D_h
#define Point2D_h

#include <vector>

class Point2D {
public:
	Point2D();
	Point2D(int x, int y);
	~Point2D();

	int getX();
	int getY();

private:
	int x, y;
};

#endif
