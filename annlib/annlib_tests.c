#include "annlib_tests.h"

void runArenaTests(void)
{
	printHeader(toString("makeArena tests"));
	u64 arenaLength = 4;
	arena a = makeArena(arenaLength);

	// Todo, test number for u64 maybe?
	printf("Arena was allocated successfully\n");
	testPointer(false, a.content);
	printf("Arena is correct length\n");
	testS32((s32) arenaLength, (s32) a.length);
	printf("Arena.used is set to 0\n");
	testS32(0, (s32) a.used);
	printf("\n");

	printHeader(toString("allocateFromArena and resetArena tests"));
	ptr(s32) p = allocateFromArena(addr(a), sizeof(s32));
	printf("Can allocate a pointer in arena\n");
	testPointer(false, p);
	s32 value = INT_MIN;
	deref(p) = value;
	printf("Can set value of pointer\n");
	testS32(value, deref(p));
	ptr(s32) p2 = allocateFromArena(addr(a), sizeof(s32));
	printf("Cannot allocate if arena is out of space\n");
	testPointer(true, p2); // Don't have enough space
	resetArena(addr(a), true); 
	p2 = allocateFromArena(addr(a), sizeof(s32));
	printf("Can allocate again after resetting arena\n");
	testPointer(false, p2);
	printf("Arena's memory was set to 0\n");
	testS32(0, deref(p2));
	deref(p2) = value;
	printf("Can set value of pointer after reset\n");
	testS32(value, deref(p2));
	printf("\n");

	// All done.
	freeArena(a);
}