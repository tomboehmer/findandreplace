#include "replacechr.h"

#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LENGTH(ARR) (sizeof(ARR) / sizeof(ARR[0]))
#define STRLEN(X) (sizeof(X) - 1)

//#define INITIAL  "9%"
//#define EXPECTED "9%"
#define INITIAL  "enp3s0: 192.168.0.108\nwlp2s0: 192.168.0.109"
#define EXPECTED "enp3s0: 192.168.0.108 wlp2s0: 192.168.0.109"
//#define INITIAL  "enp3s0: 192.168.0.108"
//#define EXPECTED "enp3s0: 192.168.0.108"
#define BEFORE '\n'
#define AFTER ' '

typedef void(*replace_func)(char*, char*, char, char);

double
benchmark(size_t times, replace_func fnc)
{
	clock_t total = 0;

	while(times-- != 0)
	{
		char initial[] = INITIAL;

		char* begin = initial;
		char* end = initial + STRLEN(initial);

		clock_t start = clock();
		fnc(begin, end, BEFORE , AFTER);
		clock_t finish = clock();

		total += (finish - start);
	}

	return (double)total / CLOCKS_PER_SEC;
}

void
replacechr_naive(char* begin, char* end, char before, char after)
{
	for(; begin != end; ++begin)
	{
		if(*begin == before)
		{ *begin = after; }
	}
}

int
main()
{
	puts("check main");
	{
		char initial[] = INITIAL;
		char expected[] = EXPECTED;

		char* begin = initial;
		char* end = initial + STRLEN(initial);

		replacechr(begin, end, BEFORE, AFTER);
		assert(strcmp(initial, expected) == 0);
	}
	puts("check naive");
	{
		char initial[] = INITIAL;
		char expected[] = EXPECTED;

		char* begin = initial;
		char* end = initial + STRLEN(initial);

		replacechr_naive(begin, end, BEFORE, AFTER);
		assert(strcmp(initial, expected) == 0);
	}

	replace_func fncs[] = {
		replacechr,
		replacechr_naive,
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
