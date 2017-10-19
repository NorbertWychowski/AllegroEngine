#include "Engine.h"

//#include "TimerFunction.h"

int x = 0;
int y = 0;
float speed = 10.0;

void f1(Engine *e) {
	std::vector<Point2D> v;
	if (key[KEY_A]) x--;
	if (key[KEY_D]) x++;
	if (key[KEY_W]) y--;
	if (key[KEY_S]) y++;
	v.push_back(Point2D(100 + x, 100 + y));
	v.push_back(Point2D(100 + x, 101 + y));
	v.push_back(Point2D(100 + x, 102 + y));
	v.push_back(Point2D(101 + x, 100 + y));
	v.push_back(Point2D(101 + x, 101 + y));
	v.push_back(Point2D(101 + x, 102 + y));
	v.push_back(Point2D(102 + x, 100 + y));
	v.push_back(Point2D(102 + x, 101 + y));
	v.push_back(Point2D(102 + x, 102 + y));

	e->drawPoints(v, BLACK);
	e->drawCircle(Point2D(300, 300), 520, RED);
	e->drawCircle4(Point2D(300, 300), 400, RED);
	e->drawFilledCircle(Point2D(300, 300), 30, CYAN);
	e->drawRectangle(Point2D(100, 100), Point2D(200, 200), BLUE);
	e->drawTriangle(Point2D(300, 100), Point2D(100, 300), Point2D(250, 250), YELLOW);

	LineSegment line1(e->getBITMAP(), Point2D(550, 130), Point2D(30, 830), DashLine);
	LineSegment line2(e->getBITMAP(), Point2D(50, 130), Point2D(1330, 930));

	std::vector<LineSegment> v2 = e->getViewport().cutLines({ line1, line2 });

	/*
	for (LineSegment l : v2) {
		l.drawLine(BLUE);
	}*/

	v2[0].drawLine(RED);
	v2[1].drawLine(CYAN);

	std::vector<Point2D> v3 = {Point2D(100, 200), Point2D(300, 150), Point2D(500, 400), Point2D(600, 900)};
	std::vector<Point2D> v4 = { Point2D(100, 210), Point2D(300, 160), Point2D(500, 410), Point2D(600, 910) };

	e->drawOpenPolygon(v3, MAGENTA);
	e->drawClosePolygon(v4, GREEN, DashLine);

	e->getViewport().drawViewport(e->getBITMAP(), CYAN, SolidLine);
}

void f2(Engine *e) {
	if (mouse_b & LEFT_BUTTON) {
	}
	if (mouse_b & RIGHT_BUTTON) {
		e->fillStack(Point2D(mouse_x, mouse_y), RED);
	}
	if (mouse_b & MIDDLE_BUTTON) {

	}
	e->getPlayer()->moveTo(mouse_x, mouse_y);
}

void f3(Engine *e) {
	if (key[KEY_SPACE]) {
		e->getPlayer()->setSpeed(speed*2.0);
	} else {
		e->getPlayer()->setSpeed(speed);
	}
}

int main() {
	Engine e = Engine::getInstance(RES_1600x900);

	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER | INSTALL_MOUSE) < 0)
		return -1;

	e.addPlayer(speed, "bitmap/playerBitmap.bmp");

	if (e.initMouseEvent({ f2 }) < 0 || e.initKeyBoardEvent({ f3 }) < 0)
		return -1;

	e.setViewport(Point2D(50, 50), Point2D(800, 800));

	e.loop({ f1 }, ENABLE_SCREEN_REFRESH);

	return 1;
}
END_OF_MAIN()