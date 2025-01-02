#pragma once

#include "annlib/annlib.h"

#include <stdbool.h>

void testS32(s32 expected, s32 actual);
void testS64(s64 expected, s64 actual);
void testU32(u32 expected, u32 actual);
void testU64(u64 expected, u64 actual);
void testString(string expected, string actual);
void testPointer(bool nullExpected, void* actual);
void testBool(bool expected, bool actual);
void initTests(void);
void concludeTests(void);
void printHeading(string heading);
void printSubheading(string subheading);
