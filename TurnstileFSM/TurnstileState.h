#pragma once
#include <iostream>

enum Action { Default, Lock, Unlock, Alarm, Thank, Reset };

class TurnstileState
{
public:
	TurnstileState();
	~TurnstileState();
	
	virtual Action coin();
	virtual Action pass();
	virtual Action ready();
	virtual Action reset();
};