#include "findchr.h"
#include "bits/common.c"

char const*
findchr(char const* begin, char const* end, char needle)
{
	static_assert(sizeof(size_t) == sizeof(size_t*), "");

	for(; ((size_t) begin & (sizeof(size_t) - 1)) != 0; ++begin)
	{
		if(begin == end)
		{ return end; }

		if(*begin == needle)
		{ return begin; }
	}

	size_t const* ptr = (size_t const*) begin;
	size_t longneedle = puffup(needle);

	for(; (char const*) ptr < end; ++ptr)
	{
		if(hasazero(*ptr ^ longneedle))
		{
			for(begin = (char const*) ptr; ; ++begin)
			{
				if(*begin == needle)
				{ return begin < end ? begin : end; }
			}
		}
	}

	return end;
}

