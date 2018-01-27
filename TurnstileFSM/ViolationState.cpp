#include "ViolationState.h"

ViolationState::ViolationState()
{

}

ViolationState::~ViolationState()
{

}

Action ViolationState::coin()
{
	std::cout << "Violation - Coin: Event ignored, in Violation state.\n";
	return Default;
}

Action ViolationState::pass()
{
	std::cout << "Violation - Pass: Event ignored, in Violation state.\n";
	return Default;
}

Action ViolationState::ready()
{
	std::cout << "Violation - Ready\n";
	return Lock;
}

Action ViolationState::reset()
{
	std::cout << "Violation - Reset\n";
	return Reset;
}