#pragma once
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <stdarg.h>

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

arena makeArena(u64 length);
void freeArena(arena a);
ptr(void) allocateFromArena(ptr(arena) a, u64 size);
void resetArena(ptr(arena) a, bool shouldClear);
/**********/

/* Strings! Yay!!! */
typedef struct
{
	u64		length;
	ptr(u8) content;
} string;

#define toString(s) (string) { strlen(s), s }

bool areStringsEqual(string first, string second);
bool stringStartsWith(string str, string startsWith);
s64 findString(string findString, string inString);
bool stringIsNumber(string str);
bool stringToNumber(string str, _Out_ ptr(s32) number);
string numberToString(ptr(arena) a, s32 number);
string pointerToString(ptr(arena) a, ptr(void) p);
string buildString(ptr(arena) a, s32 numStrings, ...);
void printString(string str, bool printNewline);
string u64ToString(ptr(arena) a, u64 number);
string s64ToString(ptr(arena) a, s64 number);
string s32ToString(ptr(arena) a, s32 number);
/*******************/

/* Math */
u32 getNumberLength(s32 number);
s64 abs(s64 number);
/********/