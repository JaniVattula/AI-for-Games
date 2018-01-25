#include "UnlockedState.h"

UnlockedState::UnlockedState()
{

}

UnlockedState::~UnlockedState()
{

}

void UnlockedState::coin(TurnstileFSM* machine)
{
	std::cout << "Unlocked - Coin\n";
}

void UnlockedState::pass(TurnstileFSM* machine)
{
	std::cout << "Unlocked - Pass\n";
}

void UnlockedState::ready(TurnstileFSM* machine)
{
	std::cout << "Unlocked - Ready\n";
}

void UnlockedState::reset(TurnstileFSM* machine)
{
	std::cout << "Unlocked - Reset\n";
}