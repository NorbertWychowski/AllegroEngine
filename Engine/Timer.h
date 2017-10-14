#ifndef Timer_h
#define Timer_h

#include <allegro.h>

class Timer {
public:
	Timer(int speed);
	~Timer();

	static void timerUpdate(void* param);
	void decreaseCount();
	int getCount();

private:
	volatile int count;
};

#endif