#pragma once
#include "TurnstileState.h"

class UnlockedState : public TurnstileState
{
public:
	UnlockedState();
	~UnlockedState();

	Action coin();
	Action pass();
	Action ready();
	Action reset();
};