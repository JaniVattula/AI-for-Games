#pragma once
#include <iostream>

class TurnstileState
{
public:
	TurnstileState();
	~TurnstileState();

	virtual void coin(void*);
	virtual void pass(void*);
	virtual void ready(void*);
	virtual void reset(void*);
};