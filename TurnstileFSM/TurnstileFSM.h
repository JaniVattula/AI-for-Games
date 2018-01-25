#pragma once
#include <iostream>
#include "TurnstileGate.h"
#include "TurnstileState.h"

class TurnstileFSM
{
public:
	TurnstileFSM(TurnstileState* startupState);
	~TurnstileFSM();

	void setState(TurnstileState &newState);
	TurnstileGate* getTurnstile();

	void coinEvent();
	void passEvent();
	void resetEvent();
	void readyEvent();

private:
	TurnstileState* currentState;
	TurnstileGate* gate;
};