#include "TurnstileFSM.h"


TurnstileFSM::TurnstileFSM(TurnstileState* startupState)
{
	currentState = startupState;
}

TurnstileFSM::~TurnstileFSM()
{

}

void TurnstileFSM::setState(TurnstileState &newState)
{
	currentState = &newState;
}

TurnstileGate* TurnstileFSM::getTurnstile()
{
	return gate;
}

void TurnstileFSM::coinEvent()
{
	currentState->coin(this);
}

void TurnstileFSM::passEvent()
{
	currentState->pass(this);
}

void TurnstileFSM::resetEvent()
{
	currentState->reset(this);
}

void TurnstileFSM::readyEvent()
{
	currentState->ready(this);
}