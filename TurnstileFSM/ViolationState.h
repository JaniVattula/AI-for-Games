#pragma once
#include "TurnstileState.h"

class ViolationState : public TurnstileState
{
public:
	ViolationState();
	~ViolationState();

	Action coin();
	Action pass();
	Action ready();
	Action reset();
};