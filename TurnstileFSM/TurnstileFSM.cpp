#include "TurnstileFSM.h"

// Set the gate to be locked on creation.
TurnstileFSM::TurnstileFSM() : currentState(&s_locked)
{

}

TurnstileFSM::~TurnstileFSM()
{

}

void TurnstileFSM::setState(TurnstileState& newState)
{
	currentState = &newState;
}

void TurnstileFSM::stateMachine(Action action)
{
	switch (action)
	{
		case Default:
		{
			std::cout << "No action performed.\n";
			break;
		}
		case Lock:
		{
			gate.lock();
			setState(s_locked);
			break;
		}
		case Unlock:
		{
			gate.unlock();
			setState(s_unlocked);
			break;
		}
		case Alarm:
		{
			gate.alarm();
			setState(s_violation);
			break;
		}
		case Thank:
		{
			gate.thankYou();
			break;
		}
		case Reset:
		{
			gate.resetAlarm();
			break;
		}
	}
}

void TurnstileFSM::coinEvent()
{
	action = currentState->coin();
	stateMachine(action);
}

void TurnstileFSM::passEvent()
{
	action = currentState->pass();
	stateMachine(action);
}

void TurnstileFSM::resetEvent()
{
	action = currentState->reset();
	stateMachine(action);
}

void TurnstileFSM::readyEvent()
{
	action = currentState->ready();
	stateMachine(action);
}