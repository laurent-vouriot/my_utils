/**
 *
 * demo_profiling.cpp
 *
 */ 
#include <math.h> 
#include <iostream> 

#include "../profiler.hpp"

void longFunc() { 
	PROFILE();
	int a = 0;
	for(int i = 0; i < 1000000000; i++) {
		a = sqrt(i); 
	}	
}

void shortFunc() {

	PROFILE(); 
	int a = 0; 
	for(int i = 0; i < 100000; i++) { 
		a = i; 
	}
}

void bench() {
	shortFunc();
	longFunc();
}

int main() {
	Profiler::getInstance().begin("demo_session", s);
	bench();
	Profiler::getInstance().end();
	return 0;
}
