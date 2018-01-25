#pragma once
#include "TurnstileState.h"
#include "TurnstileFSM.h"

class UnlockedState : public TurnstileState
{
public:
	UnlockedState();
	~UnlockedState();

	void coin(TurnstileFSM* machine);
	void pass(TurnstileFSM* machine);
	void ready(TurnstileFSM* machine);
	void reset(TurnstileFSM* machine);
};