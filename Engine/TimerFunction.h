#ifndef TimerFunction_h
#define TimerFunction_h

volatile long tick = 0;

inline void ticker() {
	++tick;
}

#endif