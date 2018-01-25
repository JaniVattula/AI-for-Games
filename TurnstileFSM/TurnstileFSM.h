#pragma once
#include <iostream>

class TurnstileFSM
{
public:
	TurnstileFSM();
	~TurnstileFSM();

	void coinEvent();
	void passEvent();
	void resetEvent();
	void readyEvent();
};