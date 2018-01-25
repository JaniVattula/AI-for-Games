#include "TurnstileGate.h"

TurnstileGate::TurnstileGate()
{

}

TurnstileGate::~TurnstileGate()
{

}

void TurnstileGate::lock()
{
	std::cout << "Locked.\n";
}

void TurnstileGate::unlock()
{
	std::cout << "Unlocked.\n";
}

void TurnstileGate::alarm()
{
	std::cout << "ALARM!\n";
}

void TurnstileGate::resetAlarm()
{
	std::cout << "Alarm reset.\n";
}

void TurnstileGate::thankYou()
{
	std::cout << "Thank you!\n";
}