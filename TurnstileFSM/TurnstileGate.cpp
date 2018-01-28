#include "TurnstileGate.h"

TurnstileGate::TurnstileGate()
{

}

TurnstileGate::~TurnstileGate()
{

}

void TurnstileGate::lock()
{
	std::cout << "Gate locked.\n";
}

void TurnstileGate::unlock()
{
	std::cout << "Gate unlocked.\n";
}

void TurnstileGate::alarm()
{
	std::cout << "GATE ALARM!\n";
}

void TurnstileGate::resetAlarm()
{
	std::cout << "Gate alarm reset.\n";
}

void TurnstileGate::thankYou()
{
	std::cout << "Thank you for coin!\n";
}