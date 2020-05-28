#include <stddef.h>
#include <assert.h>

static
int
hasazero(size_t num)
{
	size_t lomagic = 0x01;
	size_t himagic = 0x80;

	for(size_t i = 0; i < sizeof(lomagic) - 1; ++i)
	{
		lomagic = (lomagic << 8) | lomagic;
		himagic = (himagic << 8) | himagic;
	}

	return ((num - lomagic) & ~num & himagic) != 0;
}

static
size_t
puffup(char fly)
{
	static_assert(sizeof(size_t) == 4 || sizeof(size_t) == 8);

	size_t elephant = fly;

	elephant = (elephant << 8) | elephant;
	elephant = (elephant << 16) | elephant;

	if(sizeof(elephant) == 8)
	{ elephant = (elephant << 32) | elephant; }

	return elephant;
}
