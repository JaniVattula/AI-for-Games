#include <Windows.h>
#include "TurnstileFSM.h"
#include "LockedState.h"
#include "UnlockedState.h"
#include "ViolationState.h"

#define KEY1 0x31
#define KEY2 0x32
#define KEY3 0x33
#define KEY4 0x34
#define ESC 0x1B

int main()
{
	bool running = true;
	int previousInput = 0;

	LockedState startupState;
	LockedState* ss_p = &startupState;
	TurnstileFSM stateMachine(ss_p);

	while (running)
	{
		// Key 1 COIN
		if (GetAsyncKeyState(KEY1))
		{
			if (previousInput == KEY1)
			{
				continue;
			}
			else
			{
				stateMachine.coinEvent();
				previousInput = KEY1;
			}
		}

		// Key 2 PASS
		else if (GetAsyncKeyState(KEY2))
		{
			if (previousInput == KEY2)
			{
				continue;
			}
			else
			{
				stateMachine.passEvent();
				previousInput = KEY2;
			}
		}

		// Key 3 RESET
		else if (GetAsyncKeyState(KEY3))
		{
			if (previousInput == KEY3)
			{
				continue;
			}
			else
			{
				stateMachine.resetEvent();
				previousInput = KEY3;
			}
		}

		// Key 4 READY
		else if (GetAsyncKeyState(KEY4))
		{
			if (previousInput == KEY4)
			{
				continue;
			}
			else
			{
				stateMachine.readyEvent();
				previousInput = KEY4;
			}
		}

		// Key Escape
		else if (GetAsyncKeyState(ESC))
		{
			// Exit FSM
			running = false;
		}

		else
		{
			// Do nothing
		}
	}

	return 0;
}