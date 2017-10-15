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
	destroy_bitmap(bitmap);
	allegro_exit();
}

int Engine::initAllegro(int flags) {
	allegro_init();

	if (flags & INSTALL_MOUSE) {
		if (install_mouse() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac myszy!");
		}
		else {
			enable_hardware_cursor();
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
		}
		else {	
			set_volume(255, 255);
		}
	}
	if (flags & INSTALL_TIMER) {
		if (install_timer() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac timera!\n");
		}
		else {
			timer = new Timer(FRAMES_PER_SECOND);
		}
	}

	set_color_depth(desktop_color_depth());
	set_gfx_mode(windowMode, width, height, 0, 0);
	set_window_title("Silnik");

	bitmap = create_bitmap(width, height);
	clear_to_color(bitmap, WHITE);
	blit(bitmap, screen, 0, 0, 0, 0, width, height);

	return 1;
}

int Engine::initAllegro(int flags, int windowMode, DefaultResolution resolution) {
	this->windowMode = windowMode;
	this->width = resolution.width;
	this->height = resolution.height;
	this->initAllegro(flags);

	return 1;
}

int Engine::displayErrorMessage(char message[]) {
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message(message, allegro_error);
	allegro_exit();
	return -1;
}

int Engine::displayErrorMessage(std::string message) {
	set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
	allegro_message(message.c_str(), allegro_error);
	allegro_exit();
	return -1;
}

void Engine::setExitKey(int key) {
	this->exitKey = key;
}

void Engine::setViewport(Point2D firstCorner, Point2D oppositeCorner) {
	viewport.setViewport(firstCorner, oppositeCorner);
}

void Engine::loop(std::initializer_list<func> list) {
	Timer *timer = new Timer(60);

	while (!key[exitKey]) {
		while (timer->getCount() > 0) {
			for (func f : list) {
				f(this);
			}
			blit(bitmap, screen, 0, 0, 0, 0, width, height);
			clear_to_color(bitmap, WHITE);
			timer->decreaseCount();
		}
	}
}

void Engine::drawPoint(Point2D point, int color) {
	putpixel(bitmap, point.getX(), point.getY(), color);
}

void Engine::drawPoint(Point2D point, float r, float g, float b) {
	putpixel(bitmap, point.getX(), point.getY(), makecol(r * 255, g * 255, b * 255));
}

void Engine::drawPoints(std::vector<Point2D> points, int color) {
	for (Point2D p : points) {
		putpixel(bitmap, p.getX(), p.getY(), color);
	}
}

void Engine::drawPoints(std::vector<Point2D> points, float r, float g, float b) {
	for (Point2D p : points) {
		putpixel(bitmap, p.getX(), p.getY(), makecol(r * 255, g * 255, b * 255));
	}
}

void Engine::drawEllipse(Point2D point, int Rx, int Ry, int color) {
	ellipse(bitmap, point.getX(), point.getY(), Rx, Ry, color);
}

void Engine::drawEllipse(Point2D point, int Rx, int Ry, float r, float g, float b) {
	ellipse(bitmap, point.getX(), point.getY(), Rx, Ry, makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledEllipse(Point2D point, int Rx, int Ry, int color) {
	ellipsefill(bitmap, point.getX(), point.getY(), Rx, Ry, color);
}

void Engine::drawFilledEllipse(Point2D point, int Rx, int Ry, float r, float g, float b) {
	ellipsefill(bitmap, point.getX(), point.getY(), Rx, Ry, makecol(r * 255, g * 255, b * 255));
}

void Engine::drawRectangle(Point2D firstCorner, Point2D oppositeCorner, int color) {
	rect(bitmap, firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(), color);
}

void Engine::drawRectangle(Point2D firstCorner, Point2D oppositeCorner, float r, float g, float b) {
	rect(bitmap, firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(),
		makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, int color) {
	rectfill(bitmap, firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(), color);
}

void Engine::drawFilledRectangle(Point2D firstCorner, Point2D oppositeCorner, float r, float g, float b) {
	rectfill(bitmap, firstCorner.getX(), firstCorner.getY(), oppositeCorner.getX(), oppositeCorner.getY(),
		makecol(r * 255, g * 255, b * 255));
}

void Engine::drawCircle(Point2D point, int radius, int color) {
	circle(bitmap, point.getX(), point.getY(), radius, color);
}

void Engine::drawCircle(Point2D point, int radius, float r, float g, float b) {
	circle(bitmap, point.getX(), point.getY(), radius, makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledCircle(Point2D point, int radius, int color) {
	circlefill(bitmap, point.getX(), point.getY(), radius, color);
}

void Engine::drawFilledCircle(Point2D point, int radius, float r, float g, float b) {
	circlefill(bitmap, point.getX(), point.getY(), radius, makecol(r * 255, g * 255, b * 255));
}

void Engine::drawTriangle(Point2D p1, Point2D p2, Point2D p3, int color) {
	line(bitmap, p1.getX(), p1.getY(), p2.getX(), p2.getY(), color);
	line(bitmap, p2.getX(), p2.getY(), p3.getX(), p3.getY(), color);
	line(bitmap, p1.getX(), p1.getY(), p3.getX(), p3.getY(), color);
}

void Engine::drawTriangle(Point2D p1, Point2D p2, Point2D p3, float r, float g, float b) {
	line(bitmap, p1.getX(), p1.getY(), p2.getX(), p2.getY(), makecol(r * 255, g * 255, b * 255));
	line(bitmap, p2.getX(), p2.getY(), p3.getX(), p3.getY(), makecol(r * 255, g * 255, b * 255));
	line(bitmap, p1.getX(), p1.getY(), p3.getX(), p3.getY(), makecol(r * 255, g * 255, b * 255));
}

void Engine::drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, int color) {
	triangle(bitmap, p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(), color);
}

void Engine::drawFilledTriangle(Point2D p1, Point2D p2, Point2D p3, float r, float g, float b) {
	triangle(bitmap, p1.getX(), p1.getY(), p2.getX(), p2.getY(), p3.getX(), p3.getY(),
		makecol(r * 255, g * 255, b * 255));
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
	return bitmap;
}
