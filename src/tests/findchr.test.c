#include "findchr.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LENGTH(ARR) (sizeof(ARR) / sizeof(ARR[0]))
#define STRLEN(X) (sizeof(X) - 1)

#define HAYSTACK "ooooooooooooooooooooooooooooooooooxoo"
#define NEEDLE 'x'
#define NOTHERE 'y'

typedef char const*(*findchr_func)(char const*, char const*, char);

double
benchmark(size_t times, findchr_func fnc)
{
	clock_t total = 0;

	while(times-- != 0)
	{
		char haystack[] = HAYSTACK;

		char* begin = haystack;
		char* end = haystack + STRLEN(haystack);

		clock_t start = clock();
		fnc(begin, end, NEEDLE);
		//fnc(begin, end, NOTHERE);
		clock_t finish = clock();

		total += (finish - start);
	}

	return (double)total / CLOCKS_PER_SEC;
}

const char*
findchr_naive(char const* begin, char const* end, char needle)
{
	for(; begin != end; ++begin)
	{
		if(*begin == needle)
		{ return begin; }
	}
	return end;
}

int
main()
{
	puts("check main");
	{
		char haystack[] = HAYSTACK;

		char const* begin = haystack;
		char const* end = haystack + STRLEN(haystack);

		char const* ptr = findchr(begin, end, NEEDLE);
		assert(*ptr == NEEDLE);
		ptr = findchr(begin, end, NOTHERE);
		assert(ptr == end);
	}
	puts("check naive");
	{
		char haystack[] = HAYSTACK;

		char const* begin = haystack;
		char const* end = haystack + STRLEN(haystack);

		char const* ptr = findchr_naive(begin, end, NEEDLE);
		assert(*ptr == NEEDLE);
		ptr = findchr_naive(begin, end, NOTHERE);
		assert(ptr == end);
	}

	findchr_func fncs[] = {
		findchr,
		findchr_naive,
	};

	char const* names[] = {
		"main",
		"naive",
	};

	for(size_t i = 0; i < LENGTH(fncs); ++i)
	{
		double elapsed = benchmark(10000000, fncs[i]);
		printf("%-5s: %lf seconds\n", names[i], elapsed);
	}
}
