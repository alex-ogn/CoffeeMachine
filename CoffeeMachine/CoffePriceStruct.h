#pragma once
#include <string>

#define BEVAREGE_COUNT 12

struct coffe_price
{
	std::string description;
	double price;
};

struct money
{
	int conut05;
	int conut10;
	int conut20;
	int conut50;
	int conut1;

	money()
	{
		conut05 = 0;
		conut10 = 0;
		conut20 = 0;
		conut50 = 0;
		conut1 = 0;
	}
};