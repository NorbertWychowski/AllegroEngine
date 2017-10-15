#include "Engine.h"

//#include "TimerFunction.h"

int x = 0;
int y = 0;

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
	e->drawCircle(Point2D(300, 300), 50, RED);
	e->drawFilledCircle(Point2D(300, 300), 30, CYAN);
	e->drawRectangle(Point2D(100, 100), Point2D(200, 200), BLUE);
	e->drawTriangle(Point2D(300, 100), Point2D(100, 300), Point2D(250, 250), YELLOW);

	LineSegment line1(e->getBITMAP(), Point2D(550, 130), Point2D(30, 330), DashLine);
	LineSegment line2(e->getBITMAP(), Point2D(150, 230), Point2D(630, 530));
	LineSegment line3(e->getBITMAP(), Point2D(350, 530), Point2D(350, 330));
	LineSegment line4(e->getBITMAP(), Point2D(750, 230), Point2D(40, 190));
	LineSegment line5(e->getBITMAP(), Point2D(50, 130), Point2D(500, 530));

	std::vector<LineSegment> v2 = e->getViewport().cutLines({ line1, line2, line3, line4 });

	for (LineSegment l : v2) {
		l.drawLine(BLUE);
	}

	e->getViewport().drawViewport(e->getBITMAP(), CYAN);
}

int main() {
	Engine e = Engine::getInstance(RES_1600x900);

	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER) < 0)
		return -1;
	e.setExitKey(KEY_ESC);

	e.setViewport(Point2D(50, 50), Point2D(300, 300));

	e.loop({ f1 });

	return 1;
}
END_OF_MAIN()