#if _MSC_VER && !__INTEL_COMPILER
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include "Player.h"

Player::Player(int x, int y, float speed, std::string filename) {
	this->x = x;
	this->y = y;
	this->speed = speed;

	this->playerBitmap = load_bmp(filename.c_str(), default_palette);
}

Player::Player(int x, int y, float speed, char * filename) {
	this->x = x;
	this->y = y;
	this->speed = speed;

	this->playerBitmap = load_bmp("bitmap/playerBitmap.bmp", default_palette);


	if (this->playerBitmap == nullptr) {
		int x = 0;
		int y = 10 / x;
	}
}

Player::~Player() {
	destroy_bitmap(playerBitmap);
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
	return playerBitmap;
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
	this->playerBitmap = playerBitmap;
}

void Player::setBitmap(std::string filename) {
	playerBitmap = load_bmp(filename.c_str(), default_palette);
}

void Player::setBitmap(char * filename) {
	playerBitmap = load_bmp(filename, default_palette);
}