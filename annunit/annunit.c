#include "annunit.h"
#include "annlib/annlib.c"

#include <stdbool.h>
#if defined(_WIN32) || defined(WIN32) 
#include <Windows.h>
#include <processenv.h>
#include <handleapi.h>
#include <consoleapi.h>
#else

#define DWORD int
#define HANDLE int
#define BOOL int

#define GetStdHandle(x) 1
#define INVALID_HANDLE_VALUE -1
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0
#define SetConsoleMode(x, y) 1
#define GetConsoleMode(x, y) 1

#endif
#include <stdio.h>
#include <assert.h>

// Console colors
typedef enum
{
	DEFAULT, GREEN, RED, BOLD
} Color;
const ptr(s8) colors[] =
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
		addr(consoleMode)
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
	freeArena(testArena);
}

void testS32(s32 expected, s32 actual)
{
	testS64((s64) expected, (s64) actual);
}

void testS64(s64 expected, s64 actual)
{
	string results = buildString(addr(testArena), 4,
		makeString("Expected: "),
		s64ToString(addr(testArena), expected),
		makeString(", Actual: "),
		s64ToString(addr(testArena), actual)
	);
	printResults((actual == expected), results);
	resetArena(addr(testArena));
}

void testU32(u32 expected, u32 actual)
{
	testU64((u64) expected, (u64) actual);
}

void testU64(u64 expected, u64 actual)
{
	string results = buildString(addr(testArena), 4,
		makeString("Expected: "),
		u64ToString(addr(testArena), expected),
		makeString(", Actual: "),
		u64ToString(addr(testArena), actual)
	);
	printResults((actual == expected), results);
	resetArena(addr(testArena));
}

void testString(string expected, string actual)
{
	string results = buildString(addr(testArena), 5,
		makeString("Expected: \""),
		expected,
		makeString("\", Actual: \""),
		actual,
		makeString("\"")
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

void testPointer(bool nullExpected, ptr(void) actual)
{
	bool isNull = (actual == NULL);
	string results = buildString(addr(testArena), 4,
		makeString("Expected: "),
		(nullExpected) ? makeString("NULL") : makeString("Non-null"),
		makeString(", Actual: "),
		pointerToString(addr(testArena), actual)
	);
	printResults((isNull == nullExpected), results);
	resetArena(addr(testArena));
}

void testBool(bool expected, bool actual)
{
	string results = buildString(addr(testArena), 4,
		makeString("Expected: "),
		boolToString(expected),
		makeString(", Actual: "),
		boolToString(actual)
	);
	printResults((expected == actual), results);
	resetArena(addr(testArena));
}

void printHeading(string header)
{
	printf("\n%s", colors[BOLD]);
	for (u64 i = 0; i < header.length; i++)
	{
		printf("=");
	}
	printf("\n");
	printString(header, true);
	for (u64 i = 0; i < header.length; i++)
	{
		printf("=");
	}
	printf("\n%s", colors[DEFAULT]);
}

void printSubheading(string subheading)
{
	printf("\n%s", colors[BOLD]);
	printString(subheading, false);
	printf("%s\n", colors[DEFAULT]);
}
