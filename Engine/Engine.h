#ifndef Engine_h
#define Engine_h

#include <string>
//#include "Timer.h"
#include <allegro.h>

#include <initializer_list>

#define FRAMES_PER_SECOND 60

enum Flags {
	INSTALL_MOUSE = 1 << 0,
	INSTALL_KEYBOARD = 1 << 1,
	INSTALL_SOUND = 1 << 2,
	INSTALL_TIMER = 1 << 3
};

struct DefaultResolution {
	int width; int height;
};

static DefaultResolution const RES_640x480 = { 640, 480 };
static DefaultResolution const RES_800x600 = { 800, 600 };
static DefaultResolution const RES_1024x768 = { 1024, 768 };
static DefaultResolution const RES_1600x900 = { 1600, 900 };
static DefaultResolution const RES_1920x1080 = { 1920, 1080 };

typedef void(*func)();

class Engine
{
public:
	Engine();
	Engine(int width, int height);
	~Engine();

	int initAllegro(int flags);
	int initAllegro(int flags, int windowMode, struct DefaultResolution resolution);

	int displayErrorMessage(char message[]);
	int displayErrorMessage(std::string message);

	void setExitKey(int key);
	void loop(std::initializer_list<func> list);

	static Engine & getInstance(int width, int height);

	int getWidth();
	int getHeight();

private:
	int width = 800, height = 600;
	int windowMode = GFX_AUTODETECT_WINDOWED;
	int exitKey;
};
END_OF_FUNCTION(timer);

#endif