#ifndef BitmapHandler_h
#define BitmapHandler_h

#include <string>

#include <allegro.h>

class BitmapHandler {
public:
	BitmapHandler();
	BitmapHandler(BITMAP *bitmap);
	BitmapHandler(int width, int height);
	BitmapHandler(int width, int height, int color);
	BitmapHandler(int width, int height, int r, int g, int b);
	BitmapHandler(int width, int height, float r, float g, float b);

	int loadBitmap(std::string filename);
	int loadBitmap(char *filename);
	void saveBitmap(std::string filename);
	void saveBitmap(char *filename);

	void blitBitmap(BITMAP *destinationBitmap);
	void blitBitmap(BitmapHandler destinationBitmap);
	void blitBitmap(BITMAP *destinationBitmap, int sourceX, int sourceY, int destinationX, int destinationY, int width, int height);
	void blitBitmap(BitmapHandler destinationBitmap, int sourceX, int sourceY, int destinationX, int destinationY, int width, int height);
	void resizeBitmap(int width, int height);
	void clearBitmap();
	void clearBitmap(int color);
	void clearBitmap(int r, int g, int b);
	void clearBitmap(float r, float g, float b);
	void deleteBitmap();

	void setBitmap(BITMAP *bitmap);
	BITMAP * getBitmap();
	int getWidth();
	int getHeight();

	~BitmapHandler();

private:
	BITMAP *bitmap = nullptr;
};

#endif
