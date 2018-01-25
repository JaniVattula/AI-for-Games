#include "TurnstileState.h"


TurnstileState::TurnstileState()
{

}

TurnstileState::~TurnstileState()
{

}

void TurnstileState::coin(void*)
{
	std::cout << "COIN\n";
}

void TurnstileState::pass(void*)
{
	std::cout << "PASS\n";
}

void TurnstileState::ready(void*)
{
	std::cout << "READY\n";
}

void TurnstileState::reset(void*)
{
	std::cout << "RESET\n";
}