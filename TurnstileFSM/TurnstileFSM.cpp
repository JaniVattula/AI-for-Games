#include "TurnstileFSM.h"


TurnstileFSM::TurnstileFSM()
{

}

TurnstileFSM::~TurnstileFSM()
{

}

void TurnstileFSM::coinEvent()
{
	std::cout << "Coin!\n";
}

void TurnstileFSM::passEvent()
{
	std::cout << "Pass!\n";
}

void TurnstileFSM::resetEvent()
{
	std::cout << "Reset!\n";
}

void TurnstileFSM::readyEvent()
{
	std::cout << "Ready!\n";
}