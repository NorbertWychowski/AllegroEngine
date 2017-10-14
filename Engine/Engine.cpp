#include "TimerFunction.h"
#include "Engine.h"

Engine::Engine() {
}

Engine::Engine(int width, int height) {
	this->width = width;
	this->height = height;
}

Engine::~Engine() {
	//delete timer;
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
		if (install_keyboard() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac dzwieku!");
		}
		else {
			install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, "");
			set_volume(255, 255);
		}
	}
	if (flags & INSTALL_TIMER) {
		if (install_timer() < 0) {
			return displayErrorMessage("Nie udalo sie zainstalowac timera!\n");
		}
		else {
			LOCK_VARIABLE(tick);
			LOCK_FUNCTION(ticker);
			install_int_ex(ticker, BPS_TO_TIMER(FRAMES_PER_SECOND));
		}
	}

	set_color_depth(desktop_color_depth());
	set_gfx_mode(windowMode, width, height, 0, 0);
	set_window_title("Silnik");

	clear_to_color(screen, makecol(255, 255, 255));

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

void Engine::loop(std::initializer_list<func> list) {
	while (!key[exitKey]) {
		for (auto elem : list) {
			elem();
		}
	}
}

Engine & Engine::getInstance(int width, int height) {
	static Engine instance(width, height);
	return instance;
}

int Engine::getWidth() {
	return width;
}

int Engine::getHeight() {
	return height;
}
