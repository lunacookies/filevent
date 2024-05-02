#pragma once

#include "core.h"

typedef struct String String;
struct String
{
	U8 *data;
	U64 count;
};

typedef struct StringArray StringArray;
struct StringArray
{
	String *strings;
	U64 count;
};

#define StringLit(s) ((String){.data = (U8 *)(s), .count = sizeof(s) - 1})
#define StringVArg(s) (S32)(s).count, (s).data

function String StringFromCString(char *c_string);
function B32 StringMatch(String a, String b);
