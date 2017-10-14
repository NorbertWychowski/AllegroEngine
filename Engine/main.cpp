#include "Engine.h"

//#include "TimerFunction.h"

void f1() {
	line(screen, 0, 0, 100, 100, makecol(255, 0, 0));
}
void f2() {
	line(screen, 100, 100, 200, 200, makecol(0, 255, 0));
}
void f3() {
	line(screen, 200, 200, 300, 300, makecol(0, 0, 255));
}
void f4() {
	line(screen, 300, 300, 400, 400, makecol(0, 0, 0));
}

int main() {
	Engine e = Engine::getInstance(800, 600);

	if (e.initAllegro(INSTALL_KEYBOARD | INSTALL_TIMER) < 0)
		return -1;
	e.setExitKey(KEY_ESC);

	e.loop({ f1, f2, f3, f4 });

	return 1;
}
END_OF_MAIN()