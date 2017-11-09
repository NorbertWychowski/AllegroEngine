#if _MSC_VER && !__INTEL_COMPILER
#define _USE_MATH_DEFINES
#endif
#include <cmath>

#include "Engine.h"


Engine::Engine(int width, int height) {
	this->width = width;
	this->height = height;

	viewport.setViewport(Point2D(0, 0), Point2D(width, height));
}

Engine::Engine(DefaultResolution resolution) {
	this->width = resolution.width;
	this->height = resolution.height;

	viewport.setViewport(Point2D(0, 0), Point2D(width, height));
}

Engine::~Engine() {
	delete timer;
	delete player;
	show_mouse(screen);
	bitmap.deleteBitmap();
	allegro_exit();
}

int Engine::initAllegro(int flags) {
	allegro_init();
	LOCK_FUNCTION(close_button_handler);
	set_close_button_callback(close_button_handler);

	this->installedDevices = flags;

	if (flags & INSTALL_MOUSE) {
		if (install_mouse() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac myszy!");
		} else {
			enable_hardware_cursor();
			show_os_cursor(MOUSE_CURSOR_ARROW);
		}
	}
	if (flags & INSTALL_KEYBOARD) {
		if (install_keyboard() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac klawiatury!");
		}
	}
	if (flags & INSTALL_SOUND) {
		if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "") < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac dzwieku!");
		} else {
			set_volume(255, 255);
		}
	}
	if (flags & INSTALL_TIMER) {
		if (install_timer() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac timera!\n");
		} else {
			timer = new Timer(FRAMES_PER_SECOND);
		}
	}

	set_color_depth(desktop_color_depth());
	set_gfx_mode(windowMode, width, height, 0, 0);
	set_window_title("Silnik");

	bitmap = BitmapHandler(width, height, WHITE);
	bitmap.blitBitmap(screen);

	return 1;
}

int Engine::initAllegro(int flags, int windowMode, DefaultResolution resolution) {
	this->windowMode = windowMode;
	this->width = resolution.width;
	this->height = resolution.height;
	this->initAllegro(flags);

	return 1;
}

int Engine::initMouseEvent(func mouseunction) {
	if (installedDevices & INSTALL_MOUSE) {
		eventFunctions.push_back(mouseunction);
		return 1;
	} else {
		return displayErrorMessage("Nalezy dodac obsluge myszy!\n");
	}
}

int Engine::initKeyboardEvent(func keyboardFunction) {
	if (installedDevices & INSTALL_KEYBOARD) {
		eventFunctions.push_back(keyboardFunction);
		return 1;
	} else {
		return displayErrorMessage("Nalezy dodac obsluge klawiatury!\n");
	}
}

void Engine::close_button_handler(void) {
	close_button_pressed = TRUE;
}
END_OF_FUNCTION(close_button_handler)

int Engine::displayErrorMessage(char message[]) {
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message(message, allegro_error);
	return -1;
}

int Engine::displayErrorMessage(std::string message) {
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message(message.c_str(), allegro_error);
	return -1;
}

void Engine::setExitKey(int key) {
	this->exitKey = key;
}

void Engine::setViewport(Point2D firstCorner, Point2D oppositeCorner) {
	viewport.setViewport(firstCorner, oppositeCorner);
}

void Engine::addPlayer(float speed, std::string filename) {
	player = new Player(width / 2, height / 2, speed, filename.c_str());
}

void Engine::addPlayer(float speed, char * filename) {
	player = new Player(width / 2, height / 2, speed, filename);
}

void Engine::addPlayer(int x, int y, float speed, std::string filename) {
	player = new Player(x, y, speed, filename.c_str());
}

void Engine::addPlayer(int x, int y, float speed, char * filename) {
	player = new Player(x, y, speed, filename);
}

void Engine::loop(std::initializer_list<func> functions, bool screenRefresh) {
	Timer *timer = new Timer(FRAMES_PER_SECOND);
	BitmapHandler playertmp;

	int dx, dy;
	int halfWidth, halfHeight, width, height;

	if (player) {
		playertmp = BitmapHandler(player->getBitmap());

		width = playertmp.getWidth();
		height = playertmp.getHeight();
		halfWidth = playertmp.getWidth() * 0.5;
		halfHeight = playertmp.getHeight() * 0.5;
	}

	while (!key[exitKey] && !close_button_pressed) {
		while (timer->getCount() > 0) {
			for (func eF : eventFunctions) {
				eF(this);
			}

			for (func f : functions) {
				f(this);
			}

			if (player) {
				width = playertmp.getWidth();
				height = playertmp.getHeight();
				dx = 0;
				dy = 0;
				if (player->getX() - halfWidth < viewport.getFirstCorner().getX()) {
					dx = viewport.getFirstCorner().getX() - player->getX() + halfWidth;
					width -= dx;
				}
				if (player->getY() - halfHeight < viewport.getFirstCorner().getY()) {
					dy = viewport.getFirstCorner().getY() - player->getY() + halfHeight;
					height -= dy;
				}
				if (player->getX() + halfWidth > viewport.getOppositeCorner().getX()) {
					width -= player->getX() + halfWidth - viewport.getOppositeCorner().getX();
				}
				if (player->getY() + halfHeight > viewport.getOppositeCorner().getY()) {
					height -= player->getY() + halfHeight - viewport.getOppositeCorner().getY();
				}
				playertmp.blitBitmap(bitmap, dx, dy, player->getX() - halfWidth + dx, player->getY() - halfHeight + dy, width, height);
			}
			bitmap.blitBitmap(screen);
			if (screenRefresh)
				bitmap.clearBitmap();

			timer->decreaseCount();
		}
	}
}

void Engine::drawPoint(Point2D point, int color) {
	viewport.drawPixel(point, bitmap.getBitmap(), color);
}

void Engine::drawPoint(Point2D point, float r, float g, float b) {
	viewport.drawPixel(point, bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
}

void Engine::drawPoint(Point2D point, int r, int g, int b) {
	viewport.drawPixel(point, bitmap.getBitmap(), makecol(r, g, b));
}

void Engine::drawPoints(std::vector<Point2D> points, int color) {
	for (Point2D p : points) {
		viewport.drawPixel(p, bitmap.getBitmap(), color);
	}
}

void Engine::drawPoints(std::vector<Point2D> points, float r, float g, float b) {
	for (Point2D p : points) {
		viewport.drawPixel(p, bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
	}
}

void Engine::drawPoints(std::vector<Point2D> points, int r, int g, int b) {
	for (Point2D p : points) {
		viewport.drawPixel(p, bitmap.getBitmap(), makecol(r, g, b));
	}
}

void Engine::drawRectangle(Point2D firstCorner, Point2D oppositeCorner, int color) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap.getBitmap(), firstCorner, Point2D(firstCorner.getX(), oppositeCorner.getY())),
		LineSegment(bitmap.getBitmap(), firstCorner, Point2D(oppositeCorner.getX(), firstCorner.getY())),
		LineSegment(bitmap.getBitmap(), oppositeCorner, Point2D(oppositeCorner.getX(), firstCorner.getY())),
		LineSegment(bitmap.getBitmap(), oppositeCorner, Point2D(firstCorner.getX(), oppositeCorner.getY())) }))
		l.drawLine(color);
}

void Engine::drawRectangle(Point2D firstCorner, Point2D oppositeCorner, float r, float g, float b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap.getBitmap(), firstCorner, Point2D(firstCorner.getX(), oppositeCorner.getY())),
		LineSegment(bitmap.getBitmap(), firstCorner, Point2D(oppositeCorner.getX(), firstCorner.getY())),
		LineSegment(bitmap.getBitmap(), oppositeCorner, Point2D(oppositeCorner.getX(), firstCorner.getY())),
		LineSegment(bitmap.getBitmap(), oppositeCorner, Point2D(firstCorner.getX(), oppositeCorner.getY())) }))
		l.drawLine(makecol(r * 255, g * 255, b * 255));
}

void Engine::drawRectangle(Point2D firstCorner, Point2D oppositeCorner, int r, int g, int b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap.getBitmap(), firstCorner, Point2D(firstCorner.getX(), oppositeCorner.getY())),
		LineSegment(bitmap.getBitmap(), firstCorner, Point2D(oppositeCorner.getX(), firstCorner.getY())),
		LineSegment(bitmap.getBitmap(), oppositeCorner, Point2D(oppositeCorner.getX(), firstCorner.getY())),
		LineSegment(bitmap.getBitmap(), oppositeCorner, Point2D(firstCorner.getX(), oppositeCorner.getY())) }))
		l.drawLine(makecol(r, g, b));
}

void Engine::drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, int color) {
	rectfill(bitmap.getBitmap(), firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(), color);
}

void Engine::drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, float r, float g, float b) {
	rectfill(bitmap.getBitmap(), firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(),
		makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, int r, int g, int b) {
	rectfill(bitmap.getBitmap(), firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(),
		makecol(r, g, b));

}

void Engine::drawCircle(Point2D point, int radius, int color) {
	int x0 = point.getX();
	int y0 = point.getY();
	float step = asin(1.0 / radius);

	for (float alpha = 0; alpha < M_PI*0.25f; alpha += step) {
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + radius*sin(alpha), y0 + radius*cos(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + radius*sin(alpha), y0 + -1.0*radius*cos(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + -1.0*radius*sin(alpha), y0 + radius*cos(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + -1.0*radius*sin(alpha), y0 + -1.0*radius*cos(alpha)), bitmap.getBitmap(), color);
	}
}

void Engine::drawCircle(Point2D point, int radius, float r, float g, float b) {
	int x0 = point.getX();
	int y0 = point.getY();
	float step = asin(1.0 / radius);

	for (float alpha = 0; alpha < M_PI*0.25f; alpha += step) {
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + radius*sin(alpha), y0 + radius*cos(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + radius*sin(alpha), y0 + -1.0*radius*cos(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*sin(alpha), y0 + radius*cos(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*sin(alpha), y0 + -1.0*radius*cos(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
	}
}

void Engine::drawCircle(Point2D point, int radius, int r, int g, int b) {
	int x0 = point.getX();
	int y0 = point.getY();
	float step = asin(1.0 / radius);

	for (float alpha = 0; alpha < M_PI*0.25f; alpha += step) {
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + radius*sin(alpha), y0 + radius*cos(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + radius*sin(alpha), y0 + -1.0*radius*cos(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*sin(alpha), y0 + radius*cos(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*sin(alpha), y0 + -1.0*radius*cos(alpha)), bitmap.getBitmap(), makecol(r, g, b));
	}
}

void Engine::drawCircle4(Point2D point, int radius, int color) {
	int x0 = point.getX();
	int y0 = point.getY();
	float step = asin(1.0 / radius);

	for (float alpha = 0; alpha < M_PI*0.5f; alpha += step) {
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), color);
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), color);
	}
}

void Engine::drawCircle4(Point2D point, int radius, float r, float g, float b) {
	int x0 = point.getX();
	int y0 = point.getY();
	float step = asin(1.0 / radius);

	for (float alpha = 0; alpha < M_PI*0.5f; alpha += step) {
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r * 255, g * 255, b * 255));
	}
}

void Engine::drawCircle4(Point2D point, int radius, int r, int g, int b) {
	int x0 = point.getX();
	int y0 = point.getY();
	float step = asin(1.0 / radius);

	for (float alpha = 0; alpha < M_PI*0.5f; alpha += step) {
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
		viewport.drawPixel(Point2D(x0 + -1.0*radius*cos(alpha), y0 + -1.0*radius*sin(alpha)), bitmap.getBitmap(), makecol(r, g, b));
	}
}

void Engine::drawFilledCircle(Point2D point, int radius, int color) {
	circlefill(bitmap.getBitmap(), point.getX(), point.getY(), radius, color);
}

void Engine::drawFilledCircle(Point2D point, int radius, float r, float g, float b) {
	circlefill(bitmap.getBitmap(), point.getX(), point.getY(), radius, makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledCircle(Point2D point, int radius, int r, int g, int b) {
	circlefill(bitmap.getBitmap(), point.getX(), point.getY(), radius, makecol(r, g, b));
}

void Engine::drawTriangle(Point2D p1, Point2D p2, Point2D p3, int color) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap.getBitmap(), p1, p2), 
		LineSegment(bitmap.getBitmap(), p2, p3), LineSegment(bitmap.getBitmap(), p1, p3) }))
		l.drawLine(color);
}

void Engine::drawTriangle(Point2D p1, Point2D p2, Point2D p3, float r, float g, float b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap.getBitmap(), p1, p2), 
		LineSegment(bitmap.getBitmap(), p2, p3), LineSegment(bitmap.getBitmap(), p1, p3) }))
		l.drawLine(makecol(r * 255, g * 255, b * 255));
}

void Engine::drawTriangle(Point2D p1, Point2D p2, Point2D p3, int r, int g, int b) {
	for (LineSegment l : viewport.cutLines({ LineSegment(bitmap.getBitmap(), p1, p2), 
		LineSegment(bitmap.getBitmap(), p2, p3), LineSegment(bitmap.getBitmap(), p1, p3) }))
		l.drawLine(makecol(r, g, b));
}

void Engine::drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, int color) {
	triangle(bitmap.getBitmap(), p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(), color);
}

void Engine::drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, float r, float g, float b) {
	triangle(bitmap.getBitmap(), p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(),
		makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, int r, int g, int b) {
	triangle(bitmap.getBitmap(), p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(),
		makecol(r, g, b));
}

void Engine::drawLine(Point2D p1, Point2D p2, int color, LineStyle lineStyle) {
	viewport.cutLine(LineSegment(bitmap.getBitmap(), p1, p2, lineStyle))[0].drawLine(color);
}

void Engine::drawLine(Point2D p1, Point2D p2, float r, float g, float b, LineStyle lineStyle) {
	viewport.cutLine(LineSegment(bitmap.getBitmap(), p1, p2, lineStyle))[0].drawLine(makecol(r * 255, g * 255, b * 255));
}

void Engine::drawLine(Point2D p1, Point2D p2, int r, int g, int b, LineStyle lineStyle) {
	viewport.cutLine(LineSegment(bitmap.getBitmap(), p1, p2, lineStyle))[0].drawLine(makecol(r, g, b));
}

void Engine::drawOpenPolygon(std::vector<Point2D> points, int color, LineStyle lineStyle) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points[i], points[i + 1], lineStyle))[0].drawLine(color);
	}
}

void Engine::drawOpenPolygon(std::vector<Point2D> points, float r, float g, float b, LineStyle lineStyle) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points[i], points[i + 1], lineStyle))[0].drawLine(makecol(r * 255, g * 255, b * 255));
	}
}

void Engine::drawOpenPolygon(std::vector<Point2D> points, int r, int g, int b, LineStyle lineStyle) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points[i], points[i + 1], lineStyle))[0].drawLine(makecol(r, g, b));
	}
}

void Engine::drawClosePolygon(std::vector<Point2D> points, int color, LineStyle lineStyle) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points[i], points[i + 1], lineStyle))[0].drawLine(color);
	}
	if (!points.empty())
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points.front(), points.back(), lineStyle))[0].drawLine(color);
}

void Engine::drawClosePolygon(std::vector<Point2D> points, float r, float g, float b, LineStyle lineStyle) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points[i], points[i + 1], lineStyle))[0].drawLine(makecol(r * 255, g * 255, b * 255));
	}
	if (!points.empty())
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points.front(), points.back(), lineStyle))[0].drawLine(makecol(r * 255, g * 255, b * 255));
}

void Engine::drawClosePolygon(std::vector<Point2D> points, int r, int g, int b, LineStyle lineStyle) {
	for (int i = 0; i < points.size() - 1; ++i) {
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points[i], points[i + 1], lineStyle))[0].drawLine(makecol(r, g, b));
	}
	if (!points.empty())
		viewport.cutLine(LineSegment(bitmap.getBitmap(), points.front(), points.back(), lineStyle))[0].drawLine(makecol(r, g, b));
}

void Engine::fill(Point2D p, int color) {
	if ((getpixel(bitmap.getBitmap(), p.getX(), p.getY()) != color) && viewport.isInViewport(p)) {
		fill(Point2D(p.getX() + 1, p.getY()), color, getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX() - 1, p.getY()), color, getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX(), p.getY() + 1), color, getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX(), p.getY() - 1), color, getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
	}
}

void Engine::fill(Point2D p, float r, float g, float b) {
	if ((getpixel(bitmap.getBitmap(), p.getX(), p.getY()) != makecol(r * 255, g * 255, b * 255)) && viewport.isInViewport(p)) {
		fill(Point2D(p.getX() + 1, p.getY()), makecol(r * 255, g * 255, b * 255), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX() - 1, p.getY()), makecol(r * 255, g * 255, b * 255), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX(), p.getY() + 1), makecol(r * 255, g * 255, b * 255), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX(), p.getY() - 1), makecol(r * 255, g * 255, b * 255), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
	}
}

void Engine::fill(Point2D p, int r, int g, int b) {
	if ((getpixel(bitmap.getBitmap(), p.getX(), p.getY()) != makecol(r, g, b)) && viewport.isInViewport(p)) {
		fill(Point2D(p.getX() + 1, p.getY()), makecol(r, g, b), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX() - 1, p.getY()), makecol(r, g, b), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX(), p.getY() + 1), makecol(r, g, b), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
		fill(Point2D(p.getX(), p.getY() - 1), makecol(r, g, b), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
	}
}

void Engine::fillStack(Point2D p, int color) {
	fillStack(p, color, getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
}

void Engine::fillStack(Point2D p, float r, float g, float b) {
	fillStack(p, makecol(r * 255, g * 255, b * 255), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
}

void Engine::fillStack(Point2D p, int r, int g, int b) {
	fillStack(p, makecol(r, g, b), getpixel(bitmap.getBitmap(), p.getX(), p.getY()));
}

void Engine::fill(Point2D p, int color, int backgroundColor) {
	if (getpixel(bitmap.getBitmap(), p.getX(), p.getY()) == backgroundColor) {
		viewport.drawPixel(p, bitmap.getBitmap(), color);
		fill(Point2D(p.getX() + 1, p.getY()), color, backgroundColor);
		fill(Point2D(p.getX() - 1, p.getY()), color, backgroundColor);
		fill(Point2D(p.getX(), p.getY() + 1), color, backgroundColor);
		fill(Point2D(p.getX(), p.getY() - 1), color, backgroundColor);
	}
}

void Engine::fillStack(Point2D p, int color, int backgroundColor) {
	Point2D tmp;

	if (getpixel(bitmap.getBitmap(), p.getX(), p.getY()) == color)
		return;

	if (getpixel(bitmap.getBitmap(), p.getX(), p.getY()) == backgroundColor) {
		stack.push(Point2D(p.getX() + 1, p.getY()));
	}
	while (!stack.empty()) {
		tmp = stack.top();
		putpixel(bitmap.getBitmap(), tmp.getX(), tmp.getY(), color);

		stack.pop();

		if (getpixel(bitmap.getBitmap(), tmp.getX() + 1, tmp.getY()) == backgroundColor && viewport.isInViewport(tmp)) {
			stack.push(Point2D(tmp.getX() + 1, tmp.getY()));
		}
		if (getpixel(bitmap.getBitmap(), tmp.getX() - 1, tmp.getY()) == backgroundColor && viewport.isInViewport(tmp)) {
			stack.push(Point2D(tmp.getX() - 1, tmp.getY()));
		}
		if (getpixel(bitmap.getBitmap(), tmp.getX(), tmp.getY() + 1) == backgroundColor && viewport.isInViewport(tmp)) {
			stack.push(Point2D(tmp.getX(), tmp.getY() + 1));
		}
		if (getpixel(bitmap.getBitmap(), tmp.getX(), tmp.getY() - 1) == backgroundColor && viewport.isInViewport(tmp)) {
			stack.push(Point2D(tmp.getX(), tmp.getY() - 1));
		}
	}
}

Engine & Engine::getInstance(int width, int height) {
	static Engine instance(width, height);
	return instance;
}

Engine & Engine::getInstance(DefaultResolution resolution) {
	static Engine instance(resolution);
	return instance;
}

int Engine::getWidth() {
	return width;
}

int Engine::getHeight() {
	return height;
}

Viewport Engine::getViewport() {
	return viewport;
}

BITMAP * Engine::getBITMAP() {
	return bitmap.getBitmap();
}

Player * Engine::getPlayer() {
	return player;
}

volatile int Engine::close_button_pressed = false;