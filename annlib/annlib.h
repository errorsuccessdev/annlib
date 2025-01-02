#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <sal.h>

/* Nicer logic */
#define OR  ||
#define AND &&
#define NOT !
/***************/

/* Win32 goodies */
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
/*****************/

/* Fixed width types */
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;
/*********************/

/* Array stuff */
#define arrayCount(array) (sizeof(array) / sizeof((array)[0]))
/***************/

/* Arenas */
typedef struct 
{
	u64	length;
	u64	used;
	u8*	content;
} arena;

arena makeArena(u64 length);
void  freeArena(arena a);
void* allocateFromArena(arena* a, u64 size, size_t alignment); 
void  resetArena(arena* a);
/**********/

/* Strings! Yay!!! */
typedef struct
{
	u64	length;
	s8* content;
} string;

#define makeString(s) (string) { sizeof(s) - 1, s }

bool areStringsEqual(string first, string second);
bool stringStartsWith(string str, string startsWith);
s64 findString(string findString, string inString);
bool stringIsNumber(string str);
bool stringToNumber(string str, _Out_ s32* number);
string pointerToString(arena* a, void* p);
string buildString(arena* a, s32 numStrings, ...);
void printString(string str, bool printNewline);
string u64ToString(arena* a, u64 number);
string s64ToString(arena* a, s64 number);
string s32ToString(arena* a, s32 number);
string charPtrToString(s8* content);
string boolToString(bool b);
/*******************/

/* Math */
u32 getS32Length(s32 number);
u64 getU64Length(u64 number);
s64 absS64(s64 number);
/********/
