#include "Timer.h"

Timer::Timer(int speed) {
	install_param_int(Timer::timerUpdate, (void*)this, BPS_TO_TIMER(100));
	LOCK_VARIABLE(this);
	LOCK_FUNCTION(timerUpdate);
}

Timer::~Timer() {
	remove_param_int(timerUpdate, (void*)this);
}

void Timer::timerUpdate(void *param) {
	Timer *timer = (Timer*)param;
	++(timer->count);
}
END_OF_FUNCTION(timerUpdate);

void Timer::decreaseCount() {
	count--;
}

int Timer::getCount() {
	return count;
}