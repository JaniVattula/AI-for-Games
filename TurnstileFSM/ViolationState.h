#pragma once
#include "TurnstileState.h"
#include "TurnstileFSM.h"

class ViolationState : public TurnstileState
{
public:
	ViolationState();
	~ViolationState();

	void coin(TurnstileFSM* machine);
	void pass(TurnstileFSM* machine);
	void ready(TurnstileFSM* machine);
	void reset(TurnstileFSM* machine);
};

