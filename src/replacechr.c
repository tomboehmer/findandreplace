#include "replacechr.h"
#include "bits/common.c"

void
replacechr(char* begin, char* end, char before, char after)
{
	static_assert(sizeof(size_t) == sizeof(size_t*), "");

	for(; ((size_t) begin & (sizeof(size_t) - 1)) != 0; ++begin)
	{
		if(begin == end)
		{ return; }

		if(*begin == before)
		{ *begin = after; }
	}

	size_t* ptr = (size_t*) begin;
	size_t longbefore = puffup(before);

	for(; (char*)ptr < end; ++ptr)
	{
		if(hasazero(*ptr ^ longbefore))
		{
			for(begin = (char*) ptr; begin != (char*)(ptr + 1); ++begin)
			{
				if(begin == end)
				{ return; }

				if(*begin == before)
				{ *begin = after; }
			}
		}
	}
}

