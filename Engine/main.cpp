#include "Engine.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Line.h"
#include "Polygon.h"
#include "BitmapHandler.h"

int simpleGame() {
	Engine e = Engine::getInstance(RES_1600x900);
	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER | INSTALL_MOUSE) < 0)
		return -1;
	e.setExitKey(KEY_ESC);
	e.addPlayer(5, "bitmap/2.tga");
	e.disableDrawPlayer(true);

	const float gravity = 1;
	bool jumping = false;

	int x = 500, y = 500;
	int HspeedR = 5;
	int HspeedL = 5;
	float Vspeed = 0.0;
	BitmapHandler bitmap1("bitmap/1.tga");
	BitmapHandler background("bitmap/background.bmp");

	BitmapHandler buf(e.getBITMAP());

	Rectangle r(Point2D(500, 600), Point2D(655, 899));
	Rectangle ground(Point2D(0, 750), Point2D(1599, 899));

	auto draw = [&](Engine *e) {
		if (jumping) {
			Vspeed += gravity;
			y += Vspeed;
		}
		e->getPlayer()->setX(x);
		e->getPlayer()->setY(y);
		if (e->getPlayer()->isCollision(ground) || e->getPlayer()->isCollision(r)) {
			if (e->getPlayer()->isCollision(ground) && !jumping) {
				y = ground.getFirstCorner().getY() - e->getPlayer()->getBitmap()->h;
				e->getPlayer()->setY(y);
				if (e->getPlayer()->isCollision(r)) {
					if (e->getPlayer()->getX() < r.getX())
						HspeedR = 0;
					else HspeedR = 5;
					if (e->getPlayer()->getX() > r.getX())
						HspeedL = 0;
					else HspeedL = 5;
				} else {
					HspeedL = HspeedR = 5;
				}
			} else if (e->getPlayer()->isCollision(r) && !jumping) {
				y = r.getFirstCorner().getY() - e->getPlayer()->getBitmap()->h;
				e->getPlayer()->setY(y);
				HspeedL = HspeedR = 5;
			}
			jumping = false;
		} else {
			jumping = true;
		}


		background.blitBitmap(buf);
		bitmap1.drawSprite(buf, 500, 600);
		draw_trans_sprite(buf.getBitmap(), e->getPlayer()->getBitmap(), x, y);


		r.drawBoundingBox(buf.getBitmap(), BLACK);
		ground.drawBoundingBox(buf.getBitmap(), BLACK);
	};

	auto keyboardEvent = [&](Engine *e) {
		if (key[KEY_A]) {
			x -= HspeedL;
		}
		if (key[KEY_D]) {
			x += HspeedR;
		}
		if (key[KEY_W] || key[KEY_SPACE]) {
			if (!jumping) {
				jumping = true;
				Vspeed = -20;
			}
		}
	};

	e.initKeyboardEvent(keyboardEvent);

	e.loop({ draw }, ENABLE_SCREEN_REFRESH);

	return 1;
}

int playerTest() {
	int speed = 10;
	Point2D p1(50, 50);
	Point2D p2(300, 300);
	int cx = (p1.getX() + p2.getX()) / 2;
	int cy = (p1.getY() + p2.getY()) / 2;
	Rectangle rotateRectangle(p1, p2);

	Engine e = Engine::getInstance(RES_1600x900);
	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER | INSTALL_MOUSE) < 0)
		return -1;

	e.setExitKey(KEY_ESC);
	e.setViewport(Point2D(20, 20), Point2D(700, 700));
	e.addPlayer(speed, "bitmap/playerBitmap.bmp");

	auto draw = [&](Engine *e) {
		Rectangle r(Point2D(300, 300), Point2D(400, 400));
		r.drawBoundingBox(e->getBITMAP(), BLACK);

		if (e->getPlayer()->isCollision(r, true)) {
			e->drawTriangle(Point2D(0, 200), Point2D(300, 200), Point2D(150, 0), 0.0f, 1.0f, 0.0f);
		}

		rotateRectangle.rotate(1, cx, cy);
		rotateRectangle.draw(e->getBITMAP(), e->getViewport(), RED);

		e->getViewport().drawViewport(e->getBITMAP(), CYAN);
	};

	auto keyboardEvent = [&](Engine *e) {
		if (key[KEY_SPACE]) {
			e->getPlayer()->setSpeed(speed*2.0);
		} else {
			e->getPlayer()->setSpeed(speed);
		}
	};

	auto mouseEvent = [&](Engine *e) {
		e->getPlayer()->moveTo(mouse_x, mouse_y);
	};

	e.initKeyboardEvent(keyboardEvent);
	e.initMouseEvent(mouseEvent);

	e.loop({ draw }, ENABLE_SCREEN_REFRESH);

	return 1;
}

int drawTest() {
	int x = 50;
	int y = 50;
	Engine e = Engine::getInstance(RES_1600x900);
	e.setExitKey(KEY_ESC);
	e.setViewport(Point2D(20, 20), Point2D(700, 700));

	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER | INSTALL_MOUSE) < 0)
		return -1;

	auto draw = [&](Engine *e) {
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

		v2[0].drawLine(RED);
		v2[1].drawLine(CYAN);

		std::vector<Point2D> v3 = { Point2D(100, 200), Point2D(300, 150), Point2D(500, 400), Point2D(600, 900) };
		std::vector<Point2D> v4 = { Point2D(100, 210), Point2D(300, 160), Point2D(500, 410), Point2D(600, 910) };

		e->drawOpenPolygon(v3, MAGENTA);
		e->drawClosePolygon(v4, GREEN, DashLine);

		e->getViewport().drawViewport(e->getBITMAP(), CYAN);
	};

	auto mouseEvent = [](Engine *e) {
		if (mouse_b & RIGHT_BUTTON) {
			e->fillStack(Point2D(mouse_x, mouse_y), RED);
		}
	};

	e.initMouseEvent(mouseEvent);

	e.loop({ draw }, DISABLE_SCREEN_REFRESH);

	return 1;
}

int lorenzAttractor() {
	int ch = 1;
	double X1(16.0), X2(16.0), Y1(16.0), Y2(16.0), Z1(16.0), Z2(16.00001);

	Engine e = Engine::getInstance(RES_1600x900);

	e.setExitKey(KEY_ESC);

	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER) < 0)
		return -1;

	auto changeView = [&](Engine*e) {
		if (key[KEY_1]) {
			ch = 1;
		} else if (key[KEY_2]) {
			ch = 2;
		} else if (key[KEY_3]) {
			ch = 3;
		}
		if (key[KEY_1] || key[KEY_2] || key[KEY_3]) {
			X1 = 16.0;
			X2 = 16.0;
			Y1 = 16.0;
			Y2 = 16.0;
			Z1 = 16.0;
			Z2 = 16.00001;
			clear_to_color(e->getBITMAP(), WHITE);
		}
	};

	auto atr1 = [&](Engine *e) {
		double x = X1 + 10.0 * (Y1 - X1)*0.01;
		double y = Y1 + (X1*(28.0 - Z1) - Y1)*0.01;
		double z = Z1 + (X1*Y1 - (8.0 / 3.0)*Z1)*0.01;

		switch (ch) {
		case 1:
			e->drawLine(Point2D(10 * Y1 + 300, 10 * X1 + 300), Point2D(10 * y + 300, 10 * x + 300), RED);
			break;
		case 2:
			e->drawLine(Point2D(10 * X1 + 300, 10 * Z1 + 300), Point2D(10 * x + 300, 10 * z + 300), RED);
			break;
		case 3:
			e->drawLine(Point2D(10 * Y1 + 300, 10 * Z1 + 300), Point2D(10 * y + 300, 10 * z + 300), RED);
			break;
		}

		X1 = x;
		Y1 = y;
		Z1 = z;

	};
	auto atr2 = [&](Engine *e) {
		double x = X2 + 10.0 * (Y2 - X2)*0.01;
		double y = Y2 + (X2*(28.0 - Z2) - Y2)*0.01;
		double z = Z2 + (X2*Y2 - (8.0 / 3.0)*Z2)*0.01;

		switch (ch) {
		case 1:
			e->drawLine(Point2D(10 * Y2 + 300, 10 * X2 + 300), Point2D(10 * y + 300, 10 * x + 300), BLUE);
			break;
		case 2:
			e->drawLine(Point2D(10 * X2 + 300, 10 * Z2 + 300), Point2D(10 * x + 300, 10 * z + 300), BLUE);
			break;
		case 3:
			e->drawLine(Point2D(10 * Y2 + 300, 10 * Z2 + 300), Point2D(10 * y + 300, 10 * z + 300), BLUE);
			break;
		}

		X2 = x;
		Y2 = y;
		Z2 = z;

	};
	if (e.initKeyboardEvent(changeView) < 0)
		return -1;

	e.loop({ atr1, atr2 }, DISABLE_SCREEN_REFRESH);

	return 1;
}

int main() {
	if (playerTest() < 0) return -1;
	if (drawTest() < 0) return -1;
	if (lorenzAttractor() < 0) return -1;
	simpleGame();
	return 1;
}
END_OF_MAIN()