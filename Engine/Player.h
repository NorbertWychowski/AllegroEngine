#ifndef Player_h
#define Player_h

#include "BitmapHandler.h"
#include "BoundingBox.h"

class Player {
public:
	Player(int x, int y, float speed, std::string filename);
	Player(int x, int y, float speed, char *filename);
	~Player();

	void moveTo(int x, int y);

	int getX();
	int getY();
	float getSpeed();
	BITMAP* getBitmap();

	void setX(int x);
	void setY(int y);
	void setSpeed(float speed);
	void setBitmap(BITMAP *playerBitmap);
	void setBitmap(std::string filename);
	void setBitmap(char *filename);

	bool isCollision(BoundingBox object);

private:
	float x, y;
	float speed;
	BitmapHandler bitmap;
};

#endif
