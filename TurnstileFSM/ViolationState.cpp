#include "ViolationState.h"

ViolationState::ViolationState()
{

}

ViolationState::~ViolationState()
{

}

Action ViolationState::coin()
{
	std::cout << "Previous state: Violation \nEvent: Coin \nEvent ignored, in Violation state.\n";
	return Default;
}

Action ViolationState::pass()
{
	std::cout << "Previous state: Violation \nEvent: Pass \nEvent ignored, in Violation state.\n";
	return Default;
}

Action ViolationState::ready()
{
	std::cout << "Previous state: Violation \nEvent: Ready \nAlarm cleared, locking gate.\n";
	return Lock;
}

Action ViolationState::reset()
{
	std::cout << "Previous state: Violation \nEvent: Reset \nAlarm still active.\n";
	return Reset;
}