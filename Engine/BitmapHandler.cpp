#include "BitmapHandler.h"

BitmapHandler::BitmapHandler() {
	bitmap = nullptr;
}

BitmapHandler::BitmapHandler(BITMAP * bitmap) {
	this->bitmap = bitmap;
}

BitmapHandler::BitmapHandler(int width, int height) {
	bitmap = create_bitmap(width, height);
	clear_to_color(bitmap, makecol(255, 255, 255));
}

BitmapHandler::BitmapHandler(int width, int height, int color) {
	bitmap = create_bitmap(width, height);
	clear_to_color(bitmap, color);
}

BitmapHandler::BitmapHandler(int width, int height, int r, int g, int b) {
	bitmap = create_bitmap(width, height);
	clear_to_color(bitmap, makecol(r, g, b));
}

BitmapHandler::BitmapHandler(int width, int height, float r, float g, float b) {
	bitmap = create_bitmap(width, height);
	clear_to_color(bitmap, makecol(255 * r, 255 * g, 255 * b));
}

int BitmapHandler::loadBitmap(std::string filename) {
	bitmap = load_bitmap(filename.c_str(), default_palette);
	if (bitmap) {
		return 1;
	} else {
		return -1;
	}
}

int BitmapHandler::loadBitmap(char * filename) {
	bitmap = load_bitmap(filename, default_palette);
	if (bitmap) {
		return 1;
	} else {
		return -1;
	}
}

void BitmapHandler::saveBitmap(std::string filename) {
	save_bmp(filename.c_str(), bitmap, default_palette);
}

void BitmapHandler::saveBitmap(char * filename) {
	save_bmp(filename, bitmap, default_palette);
}

void BitmapHandler::blitBitmap(BITMAP * destinationBitmap) {
	blit(this->bitmap, destinationBitmap, 0, 0, 0, 0, this->bitmap->w, this->bitmap->h);
}

void BitmapHandler::blitBitmap(BitmapHandler destinationBitmap) {
	blit(this->bitmap, destinationBitmap.getBitmap(), 0, 0, 0, 0, this->bitmap->w, this->bitmap->h);
}

void BitmapHandler::blitBitmap(BITMAP * destinationBitmap, int sourceX, int sourceY, int destinationX, int destinationY, int width, int height) {
	blit(this->bitmap, destinationBitmap, sourceX, sourceY, destinationX, destinationY, width, height);
}

void BitmapHandler::blitBitmap(BitmapHandler destinationBitmap, int sourceX, int sourceY, int destinationX, int destinationY, int width, int height) {
	blit(this->bitmap, destinationBitmap.getBitmap(), sourceX, sourceY, destinationX, destinationY, width, height);
}

void BitmapHandler::resizeBitmap(int width, int height) {
	BITMAP *tmp = create_bitmap(width, height);
	stretch_blit(bitmap, tmp, 0, 0, bitmap->w, bitmap->h, 0, 0, width, height);
	destroy_bitmap(bitmap);
	bitmap = tmp;
}

void BitmapHandler::clearBitmap() {
	clear_to_color(bitmap, makecol(255, 255, 255));
}

void BitmapHandler::clearBitmap(int color) {
	clear_to_color(bitmap, color);
}

void BitmapHandler::clearBitmap(int r, int g, int b) {
	clear_to_color(bitmap, makecol(r, g, b));
}

void BitmapHandler::clearBitmap(float r, float g, float b) {
	clear_to_color(bitmap, makecol(255 * r, 255 * g, 255 * b));
}

void BitmapHandler::deleteBitmap() {
	destroy_bitmap(bitmap);
	bitmap = nullptr;
}

void BitmapHandler::setBitmap(BITMAP * bitmap) {
	this->bitmap = bitmap;
}

BITMAP * BitmapHandler::getBitmap() {
	return bitmap;
}

int BitmapHandler::getWidth() {
	if (bitmap)
		return bitmap->w;
	return -1;
}

int BitmapHandler::getHeight() {
	if (bitmap)
		return bitmap->h;
	return -1;
}

BitmapHandler::~BitmapHandler() {
	if (!bitmap)
		destroy_bitmap(bitmap);
}
