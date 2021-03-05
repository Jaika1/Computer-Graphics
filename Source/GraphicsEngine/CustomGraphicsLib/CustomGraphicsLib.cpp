#include "pch.h"
#include "CustomGraphicsLib.h"
#include <iostream>
#include <Windows.h>

constexpr char VT_ESC = 0x1B;

void PrintHello(bool fancy)
{
	if (!fancy)
		std::cout << "Hello World!" << std::endl;
	else
	{
		char text[] = "Hello World!";
		for (int i = 0; i < sizeof(text); ++i)
			std::cout << VT_ESC << "[38;2;0;" << (150 + (i * (105 / sizeof(text)))) << ";255m" << text[i];
		std::cout << std::endl;
	}
}

bool TryEnableCVTS()
{
	HANDLE outHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if (outHandle == INVALID_HANDLE_VALUE)
		return false;

	DWORD consoleFlags;
	if (!GetConsoleMode(outHandle, &consoleFlags))
		return false;

	consoleFlags |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(outHandle, consoleFlags))
		return false;

	return true;
}
