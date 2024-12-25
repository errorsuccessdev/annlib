#include "annunit.h"

// Console colors
typedef enum enumColor
{
	DEFAULT, GREEN, RED, BOLD
} Color;
const char* colors[] =
{
   "\x1b[0m",  // Defualt
   "\x1b[32m", // Green
   "\x1b[31m", // Red
   "\x1b[1m"   // Bold
};

void printResults(bool passed, string results);

arena testArena;
DWORD originalConsoleMode;

void initTests(void)
{
	testArena = makeArena(2048);
	// Set output mode to handle virtual terminal sequences
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	assert(hOut != INVALID_HANDLE_VALUE);
	DWORD consoleMode = 0;
	BOOL result = GetConsoleMode(
		hOut,
		&consoleMode
	);
	assert(result);

	// Save original console mode so we can restore it later
	originalConsoleMode = consoleMode;
	consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	result = SetConsoleMode(
		hOut,
		consoleMode
	);
	assert(result);
}

void concludeTests(void)
{
	// Reset console to prior settings
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	BOOL result = SetConsoleMode(
		hOut,
		originalConsoleMode
	);
	assert(result);
}

void testS32(s32 expected, s32 actual)
{
	string results = buildString(addr(testArena), 4,
		toString("Expected: "),
		numberToString(addr(testArena), expected),
		toString(", Actual: "),
		numberToString(addr(testArena), actual)
	);
	printResults((actual == expected), results);
}

void testU64(u64 expected, u64 actual)
{
	string results = buildString(addr(testArena), 4,
		toString("Expected: "),
		u64ToString(addr(testArena), expected),
		toString(", Actual: "),
		u64ToString(addr(testArena), actual)
	);
	printResults((actual == expected), results);
}

void testString(string expected, string actual)
{
	string results = buildString(addr(testArena), 4,
		toString("Expected: "),
		expected,
		toString(", Actual: "),
		actual
	);
	printResults(areStringsEqual(actual, expected), results);
}

void printResults(bool passed, string results)
{
	if (passed)
	{
		printf("%sTest passed. ", colors[GREEN]);
	}
	else
	{
		printf("%sTest failed. ", colors[RED]);
	}
	printf("%s", colors[DEFAULT]);
	printString(results, true);
}

void testPointer(bool nullExpected, void* actual)
{
	bool isNull = (actual == NULL);
	string results = buildString(addr(testArena), 4,
		toString("Expected: "),
		toString((nullExpected) ? "NULL" : "Non-null"),
		toString(", Actual: "),
		pointerToString(addr(testArena), actual)
	);
	printResults((isNull == nullExpected), results);
}

void printHeader(string header)
{
	printf("%s", colors[BOLD]);
	for (int i = 0; i < header.length; i++)
	{
		printf("=");
	}
	printf("\n");
	printString(header, true);
	for (int i = 0; i < header.length; i++)
	{
		printf("=");
	}
	printf("\n%s", colors[DEFAULT]);
}