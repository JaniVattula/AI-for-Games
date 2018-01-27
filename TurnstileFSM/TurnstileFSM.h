#pragma once
#include <iostream>
#include "TurnstileGate.h"

#include "ViolationState.h"
#include "UnlockedState.h"
#include "LockedState.h"

class TurnstileFSM
{
public:
	TurnstileFSM();
	~TurnstileFSM();

	void setState(TurnstileState& newState);

	void coinEvent();
	void passEvent();
	void resetEvent();
	void readyEvent();

	// The "Action" enum is owned by the TurnstileState class.
	void stateMachine(Action action);

private:
	ViolationState s_violation;
	UnlockedState s_unlocked;
	LockedState s_locked;

	TurnstileState* currentState;
	TurnstileGate gate;

	Action action;
};