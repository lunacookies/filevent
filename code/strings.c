function String
StringFromCString(char *c_string)
{
	String result = {0};
	result.data = (U8 *)c_string;
	result.count = MemoryStrlen(c_string);
	return result;
}

function B32
StringMatch(String a, String b)
{
	if (a.count != b.count)
	{
		return 0;
	}

	return MemoryMatch(a.data, b.data, a.count);
}
