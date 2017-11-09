#if _MSC_VER && !__INTEL_COMPILER
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include "Player.h"

Player::Player(int x, int y, float speed, std::string filename) {
	this->x = x;
	this->y = y;
	this->speed = speed;

	bitmap.loadBitmap(filename);
}

Player::Player(int x, int y, float speed, char * filename) {
	this->x = x;
	this->y = y;
	this->speed = speed;

	bitmap.loadBitmap(filename);
}

Player::~Player() {
	bitmap.deleteBitmap();
}

void Player::moveTo(int x, int y) {
	float dx = this->x - x;
	float dy = this->y - y;
	float alpha = atan2f(dy, -dx);
	float radius = sqrt(dx*dx + dy*dy);

	if (radius < speed * 10) {
		this->x += radius / 10 * cosf(alpha);
		this->y -= radius / 10 * sinf(alpha);
	} else {
		this->x += speed * cosf(alpha);
		this->y -= speed * sinf(alpha);
	}
}

int Player::getX() {
	return x;
}
int Player::getY() {
	return y;
}

float Player::getSpeed() {
	return speed;
}

BITMAP* Player::getBitmap() {
	return bitmap.getBitmap();
}

void Player::setX(int x) {
	this->x = x;
}

void Player::setY(int y) {
	this->y = y;
}

void Player::setSpeed(float speed) {
	this->speed = speed;
}

void Player::setBitmap(BITMAP * playerBitmap) {
	bitmap.setBitmap(playerBitmap);
}

void Player::setBitmap(std::string filename) {
	bitmap.loadBitmap(filename);
}

void Player::setBitmap(char * filename) {
	bitmap.loadBitmap(filename);
}

bool Player::isCollision(BoundingBox object, bool centerXY) {
	if (bitmap.getBitmap() != nullptr) {
		if (centerXY) {
			return BoundingBox(x - bitmap.getWidth()*0.5, y - bitmap.getHeight()*0.5, bitmap.getWidth(), bitmap.getHeight()).isCollision(object);
		} else {
			return BoundingBox(x, y, bitmap.getWidth(), bitmap.getHeight()).isCollision(object);
		}
	} else {
		return false;
	}
}
