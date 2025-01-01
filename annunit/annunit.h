#pragma once

#include "annlib/annlib.h"

#include <stdbool.h>

export void testS32(s32 expected, s32 actual);
export void testS64(s64 expected, s64 actual);
export void testU32(u32 expected, u32 actual);
export void testU64(u64 expected, u64 actual);
export void testString(string expected, string actual);
export void testPointer(bool nullExpected, ptr(void) actual);
export void testBool(bool expected, bool actual);
export void initTests(void);
export void concludeTests(void);
export void printHeading(string heading);
export void printSubheading(string subheading);