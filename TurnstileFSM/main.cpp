#include <Windows.h>
#include "TurnstileFSM.h"

#define KEY1 0x31
#define KEY2 0x32
#define KEY3 0x33
#define KEY4 0x34
#define ESC 0x1B

void printCommands();

int main()
{
	bool running = true;
	int previousInput = 0;

	TurnstileFSM stateMachine;

	printCommands();

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
				system("cls");
				printCommands();
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
				system("cls");
				printCommands();
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
				system("cls");
				printCommands();
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
				system("cls");
				printCommands();
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

		// Clear inputs when a key is released
		else if (!GetAsyncKeyState(KEY1) || !GetAsyncKeyState(KEY2) || 
			!GetAsyncKeyState(KEY3) || !GetAsyncKeyState(KEY4) || !GetAsyncKeyState(ESC))
		{
			previousInput = NULL;
		}

		else
		{
			// Do nothing
		}
	}

	return 0;
}

void printCommands()
{
	std::cout << "Actions:\n1: Coin\n2: Pass\n3: Reset\n4: Ready\n\n";
}