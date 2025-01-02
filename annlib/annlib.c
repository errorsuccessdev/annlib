#include "annlib.h"

#include <stdbool.h>
#include <sal.h>
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <stdalign.h>
#include <string.h>

void private_numberToString(
	_Inout_ string* str, s32 startIndex, u64 number
);

bool areStringsEqual(string first, string second)
{
	if (first.length != second.length)
	{
		return false;
	}
	for (u64 i = 0; i < first.length; i++)
	{
		if (first.content[i] != second.content[i])
		{
			return false;
		}
	}
	return true;
}

bool stringIsNumber(string str)
{
	s32 startIndex = 0;
	if (str.length == 0)
	{
		return false;
	}
	if (str.content[0] == '-' AND
		str.length > 1)
	{
		startIndex += 1;
	}
	for (u64 i = startIndex; i < str.length; i++)
	{
		if (str.content[i] > '9' OR
			str.content[i] < '0')
		{
			return false;
		}
	}
	return true;
}

string pointerToString(arena* a, void* p)
{
	if (p == NULL)
	{
		return makeString("NULL");
	}
	u64 startIndex = 0;
	u32 length = sizeof(p) * 2;
	u8* content = allocateFromArena(a, length, alignof(u8));
	string str = { length, content };
	u64 value = (u64) p;
	for (u64 i = startIndex; i < str.length; i++)
	{
		u64 inverse = str.length - i - 1;
		s32 number = value % 16;
		if (number < 10)
		{
			str.content[inverse] = number + '0';
		}
		else
		{
			number -= 10;
			str.content[inverse] = number + 'A';
		}
		value /= 16;
		if (value == 0)
		{
			str.content += inverse;
			str.length = i + 1;
			break;
		}
	}
	return str;
}

bool stringToNumber(string str, _Out_ s32* number)
{
	*number = 0;
	if (NOT stringIsNumber(str))
	{
		return false;
	}
	s32 temp = 0;
	s32 startIndex = 0;
	bool isNegative = false;
	if (str.content[0] == '-' AND
		str.length > 1)
	{
		isNegative = true;
		startIndex += 1;
	}
	for (s32 i = startIndex; i < str.length; i++)
	{
		temp = (temp * 10) + (str.content[i] - '0');
	}
	*number = (isNegative) ? -temp : temp;
	return true;
}

bool stringStartsWith(string str, string startsWith)
{
	if (str.length < startsWith.length)
	{
		return false;
	}
	string subStr = { startsWith.length, str.content };
	return areStringsEqual(subStr, startsWith);
}

s64 findString(string findString, string inString)
{
	for (s32 i = 0; i <= inString.length - findString.length; i++)
	{
		string str = { findString.length, inString.content + i };
		bool startsWith = stringStartsWith(str, findString);
		if (startsWith)
		{
			return i;
		}
	}
	return -1;
}

u64 getU64Length(u64 number)
{
	u64 numDigits = 0;
	if (number == 0)
	{
		numDigits = 1;
	}
	else
	{
		while (number != 0)
		{
			numDigits += 1;
			number /= 10;
		}
	}
	return numDigits;
}

u32 getS32Length(s32 number)
{
	u32 numDigits = 0;
	if (number <= 0)
	{
		numDigits += 1;
	}
	while (number != 0)
	{
		numDigits += 1;
		number /= 10;
	}
	return numDigits;
}

string s32ToString(arena* a, s32 number)
{
	return s64ToString(a, (s64) number);
}

string s64ToString(arena* a, s64 number)
{
	if (number >= 0)
	{
		return u64ToString(a, (u64) number);
	}
	u64 absNumber = (u64) absS64(number);
	u64 length = getU64Length(absNumber) + 1;
	u8* content = allocateFromArena(a, sizeof(u8) * length, alignof(u8));
	content[0] = '-';
	string str = { length, content };
	private_numberToString(&str, 1, absNumber);
	return str;
}

void private_numberToString(
	_Inout_ string* str, s32 startIndex, u64 number
)
{
	u64 inverse = str->length - 1;
	for (u64 i = startIndex; i < str->length; i++)
	{
		str->content[inverse] = (u8) (number % 10) + '0';
		inverse -= 1;
		number /= 10;
	}
}

string u64ToString(arena* a, u64 number)
{
	u64 length = getU64Length(number);
	u8* content = allocateFromArena(a, sizeof(u8) * length, alignof(u8));
	string str = { length, content };
	private_numberToString(&str, 0, number);
	return str;
}

string charPtrToString(s8* content)
{
	string str = { strlen(content), content };
	return str;
}

string boolToString(bool b)
{
	return (b) ? makeString("true") : makeString("false");
}

arena makeArena(u64 length)
{
	u8* content = malloc(length);
	assert(content);
	arena a = { length, 0, content };
	memset(a.content, 0, a.length);
	return a;
}

void freeArena(arena a)
{
	free(a.content);
}

// Todo: This is borked
void* allocateFromArena(arena* a, u64 size, size_t alignment)
{
	if ((size + alignment) > (a->length - a->used))
	{
		return NULL;
	}
	uintptr_t ret = (uintptr_t) (a->content + a->used);
	uintptr_t theModulo = ret % (uintptr_t) alignment;
	if (theModulo == 0)
	{
		a->used += size;
		return (void*) ret;
	}
	uintptr_t offset = alignment - theModulo;
	ret += offset;
	a->used += (size + offset);
	return (void*) ret;
}

void resetArena(arena* a)
{
	a->used = 0;
	memset(a->content, 0, a->length);
}

s64 absS64(s64 number)
{
	return (number < 0) ? -number : number;
}

string buildString(arena* a, s32 numStrings, ...)
{
	va_list args;
	va_start(args, numStrings);

	// Get the length
	u64 length = 0;
	for (s32 i = 0; i < numStrings; i++)
	{
		string str = va_arg(args, string);
		length += str.length;
	}
	if (length > (a->length - a->used))
	{
		return makeString("");
	}
	va_end(args);

	// Combine the strings
	u8* content = allocateFromArena(a, length, alignof(u8));
	va_start(args, numStrings);
	s32 contentIndex = 0;
	for (s32 i = 0; i < numStrings; i++)
	{
		string str = va_arg(args, string);
		for (s32 j = 0; j < str.length; j++)
		{
			content[contentIndex] = str.content[j];
			contentIndex += 1;
		}
	}
	va_end(args);

	string str = { length, content };
	return str;
}

void printString(string str, bool printNewline)
{
	const s8* newline = (printNewline) ? "\n" : "";
	printf("%.*s%s", (s32) str.length, str.content, newline);
}
