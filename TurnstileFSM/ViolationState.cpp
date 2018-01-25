#include "ViolationState.h"


ViolationState::ViolationState()
{

}

ViolationState::~ViolationState()
{

}

void ViolationState::coin(TurnstileFSM* machine)
{
	std::cout << "Violation - Coin: Event ignored, in Violation state.\n";
}

void ViolationState::pass(TurnstileFSM* machine)
{
	std::cout << "Violation - Pass: Event ignored, in Violation state.\n";
}

void ViolationState::ready(TurnstileFSM* machine)
{
	std::cout << "Violation - Ready\n";
}

void ViolationState::reset(TurnstileFSM* machine)
{
	std::cout << "Violation - Reset\n";
}