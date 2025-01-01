#pragma once

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <sal.h>

/* Nicer logic */#define OR  ||
#define AND &&
#define NOT !
/***************/

/* Win32 goodies */
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define export __declspec(dllexport)
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

/* Nicer pointer stuff ? */
#define ptr(type)  type*
#define deref(p)   *p	
#define addr(var)  &var
/*************************/

/* Array stuff */
#define arrayCount(array) (sizeof(array) / sizeof((array)[0]))
/***************/

/* Arenas */
typedef struct 
{
	u64		length;
	u64		used;
	ptr(u8) content;
} arena;

export arena makeArena(u64 length);
export void freeArena(arena a);
export ptr(void) allocateFromArena(ptr(arena) a, u64 size); 
export void resetArena(ptr(arena) a);
/**********/

/* Strings! Yay!!! */
typedef struct
{
	u64		length;
	ptr(u8) content;
} string;

#define toString(s) (string) { strlen(s), s }

export bool areStringsEqual(string first, string second);
export bool stringStartsWith(string str, string startsWith);
export s64 findString(string findString, string inString);
export bool stringIsNumber(string str);
export bool stringToNumber(string str, _Out_ ptr(s32) number);
export string pointerToString(ptr(arena) a, ptr(void) p);
export string buildString(ptr(arena) a, s32 numStrings, ...);
export void printString(string str, bool printNewline);
export string u64ToString(ptr(arena) a, u64 number);
export string s64ToString(ptr(arena) a, s64 number);
export string s32ToString(ptr(arena) a, s32 number);
/*******************/

/* Math */
export u32 getS32Length(s32 number);
export u64 getU64Length(u64 number);
export s64 abs(s64 number);
/********/