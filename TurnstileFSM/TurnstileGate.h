#pragma once
#include <iostream>

class TurnstileGate
{
public:
	TurnstileGate();
	~TurnstileGate();

	void lock();
	void unlock();

	void alarm();
	void resetAlarm();

	void thankYou();
};

