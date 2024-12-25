#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include "annunit.h"
#include "annlib_tests.h"
#include "annlib.h"

int main()
{
	arena a = makeArena(1024);
	string s = s32ToString(addr(a), -5285);
	printString(s, true);
	string s2 = s32ToString(addr(a), 7583);
	printString(s2, true);
	//initTests();
	//runArenaTests();
	//concludeTests();
}