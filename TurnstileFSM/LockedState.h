#pragma once
#include "TurnstileState.h"

class LockedState : public TurnstileState
{
public:
	LockedState();
	~LockedState();

	Action coin();
	Action pass();
	Action ready();
	Action reset();
};