#pragma once

#include "annlib.h"
#include <windows.h>

void testS32(s32 expected, s32 actual);
void testU64(u64 expected, u64 actual);
void testString(string expected, string actual);
void testPointer(bool nullExpected, void* actual);
void initTests(void);
void concludeTests(void);
void printHeader(string header);