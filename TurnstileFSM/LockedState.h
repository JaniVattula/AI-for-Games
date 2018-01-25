#pragma once
#include "TurnstileState.h"
#include "TurnstileFSM.h"

class LockedState : public TurnstileState
{
public:
	LockedState();
	~LockedState();

	void coin(TurnstileFSM* machine);
	void pass(TurnstileFSM* machine);
	void ready(TurnstileFSM* machine);
	void reset(TurnstileFSM* machine);
};