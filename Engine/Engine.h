#ifndef Engine_h
#define Engine_h

#include <string>
#include <vector>
#include <stack>

#include "Timer.h"
#include "Point2D.h"
#include "Viewport.h"
#include "LineSegment.h"
#include "Player.h"

#include <allegro.h>


#include <initializer_list>

#define FRAMES_PER_SECOND 60

#define ENABLE_SCREEN_REFRESH true
#define DISABLE_SCREEN_REFRESH false

#define WHITE	makecol(255, 255, 255)
#define BLACK	makecol(0, 0, 0)
#define RED		makecol(255, 0, 0)
#define BLUE	makecol(0, 0, 255)
#define GREEN	makecol(0, 255, 0)
#define CYAN	makecol(0, 255, 255)
#define MAGENTA makecol(255, 0, 255)
#define YELLOW	makecol(255, 255, 0)

enum Flags {
	INSTALL_MOUSE = 1 << 0,
	INSTALL_KEYBOARD = 1 << 1,
	INSTALL_SOUND = 1 << 2,
	INSTALL_TIMER = 1 << 3
};

enum MouseButton {
	LEFT_BUTTON = 1 << 0,
	RIGHT_BUTTON = 1 << 1,
	MIDDLE_BUTTON = 1 << 2
};

struct DefaultResolution {
	int width; int height;
};

static DefaultResolution const RES_640x480 = { 640, 480 };
static DefaultResolution const RES_800x600 = { 800, 600 };
static DefaultResolution const RES_1024x768 = { 1024, 768 };
static DefaultResolution const RES_1600x900 = { 1600, 900 };
static DefaultResolution const RES_1920x1080 = { 1920, 1080 };



class Engine {
public:
	typedef void(*func)(Engine*);

	Engine(int width, int height);
	Engine(struct DefaultResolution resolution);
	~Engine();

	int initAllegro(int flags);
	int initAllegro(int flags, int windowMode, struct DefaultResolution resolution);
	int initMouseEvent(std::initializer_list<func> list);
	int initKeyBoardEvent(std::initializer_list<func> list);

	int displayErrorMessage(char message[]);
	int displayErrorMessage(std::string message);

	void setExitKey(int key);
	void setViewport(Point2D firstCorner, Point2D oppositeCorner);

	void addPlayer(float speed, std::string filename);
	void addPlayer(float speed, char *filename);
	void addPlayer(int x, int y, float speed, std::string filename);
	void addPlayer(int x, int y, float speed, char *filename);

	static Engine & getInstance(int width, int height);
	static Engine & getInstance(struct DefaultResolution resolution);
	int getWidth();
	int getHeight();
	Viewport getViewport();
	BITMAP* getBITMAP();
	Player* getPlayer();

	void loop(std::initializer_list<func> list, bool screenRefresh = ENABLE_SCREEN_REFRESH);

	void drawPoint(Point2D point, int color);
	void drawPoint(Point2D point, float r, float g, float b);
	void drawPoint(Point2D point, int r, int g, int b);
	void drawPoints(std::vector<Point2D> points, int color);
	void drawPoints(std::vector<Point2D> points, float r, float g, float b);
	void drawPoints(std::vector<Point2D> points, int r, int g, int b);
	void drawRectangle(Point2D firstCorner, Point2D oppositeCorner, int color);
	void drawRectangle(Point2D firstCorner, Point2D oppositeCorner, float r, float g, float b);
	void drawRectangle(Point2D firstCorner, Point2D oppositeCorner, int r, int g, int b);
	void drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, int color);
	void drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, float r, float g, float b);
	void drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, int r, int g, int b);
	void drawCircle(Point2D point, int radius, int color);
	void drawCircle(Point2D point, int radius, float r, float g, float b);
	void drawCircle(Point2D point, int radius, int r, int g, int b);
	void drawCircle4(Point2D point, int radius, int color);
	void drawCircle4(Point2D point, int radius, float r, float g, float b);
	void drawCircle4(Point2D point, int radius, int r, int g, int b);
	void drawFilledCircle(Point2D point, int radius, int color);
	void drawFilledCircle(Point2D point, int radius, float r, float g, float b);
	void drawFilledCircle(Point2D point, int radius, int r, int g, int b);
	void drawTriangle(Point2D p1, Point2D p2, Point2D p3, int color);
	void drawTriangle(Point2D p1, Point2D p2, Point2D p3, float r, float g, float b);
	void drawTriangle(Point2D p1, Point2D p2, Point2D p3, int r, int g, int b);
	void drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, int color);
	void drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, float r, float g, float b);
	void drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, int r, int g, int b);
	void drawLine(Point2D p1, Point2D p2, int color, LineStyle lineStyle = SolidLine);
	void drawLine(Point2D p1, Point2D p2, float r, float g, float b, LineStyle lineStyle = SolidLine);
	void drawLine(Point2D p1, Point2D p2, int r, int g, int b, LineStyle lineStyle = SolidLine);
	void drawOpenPolygon(std::vector<Point2D> points, int color, LineStyle lineStyle = SolidLine);
	void drawOpenPolygon(std::vector<Point2D> points, float r, float g, float b, LineStyle lineStyle = SolidLine);
	void drawOpenPolygon(std::vector<Point2D> points, int r, int g, int b, LineStyle lineStyle = SolidLine);
	void drawClosePolygon(std::vector<Point2D> points, int color, LineStyle lineStyle = SolidLine);
	void drawClosePolygon(std::vector<Point2D> points, float r, float g, float b, LineStyle lineStyle = SolidLine);
	void drawClosePolygon(std::vector<Point2D> points, int r, int g, int b, LineStyle lineStyle = SolidLine);

	void fill(Point2D p, int color);
	void fill(Point2D p, float r, float g, float b);
	void fill(Point2D p, int r, int g, int b);
	void fillStack(Point2D p, int color);
	void fillStack(Point2D p, float r, float g, float b);
	void fillStack(Point2D p, int r, int g, int b);

private:
	BITMAP *bitmap = nullptr;
	Timer *timer = nullptr;
	Player *player = nullptr;
	Viewport viewport;
	std::stack<Point2D> stack;
	std::vector<func> eventFunctions;
	int width = 800, height = 600;
	int windowMode = GFX_AUTODETECT_WINDOWED;
	int exitKey = KEY_ESC;
	int installedDevices;

	void fill(Point2D p, int color, int backgroundColor);
	void fillStack(Point2D p, int color, int backgroundColor);
};
END_OF_FUNCTION(timer);

#endif