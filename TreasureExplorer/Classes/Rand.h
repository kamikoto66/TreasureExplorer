#pragma once
#include "SingleTon.h"
#include "cocos2d.h"

class CWellRandom : public SingleTon<CWellRandom>
{
private:
	unsigned long state[16];
	unsigned int index;

public:

	void init()
	{
		for (int i = 0; i < 16; i++)
		{
			state[i] = cocos2d::random();
		}
	}

	unsigned long Next(int minValue, int maxValue)
	{
		return (unsigned long)((Next() % (maxValue - minValue)) + minValue);
	}

	unsigned long Next(long maxValue)
	{
		return Next() % maxValue;
	}

	unsigned long Next()
	{
			unsigned long a = 0, b = 0, c = 0, d = 0;
			a = state[index];
			c = state[(index + 13) & 15];
			b = a ^ c ^ (a << 16) ^ (c << 15);
			c = state[(index)+9 & 15];
			c ^= (c >> 11);
			a = state[index] = b^c;
			d = a ^ ((a << 5) & 0xDA442D20UL);
			index = (index + 15) & 15;
			a = state[index];
			state[index] = a^b^d ^ (a << 2) ^ (b << 18) ^ (c << 28);
			return state[index];
	}
};
#define WellRandom CWellRandom::getInstance()