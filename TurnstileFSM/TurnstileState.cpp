#include "TurnstileState.h"


TurnstileState::TurnstileState()
{

}

TurnstileState::~TurnstileState()
{

}

Action TurnstileState::coin()
{
	std::cout << "COIN\n";
	return Default;
}

Action TurnstileState::pass()
{
	std::cout << "PASS\n";
	return Default;
}

Action TurnstileState::ready()
{
	std::cout << "READY\n";
	return Default;
}

Action TurnstileState::reset()
{
	std::cout << "RESET\n";
	return Default;
}