#pragma once
#include "CoffePriceStruct.h"
#include "framework.h"
#include "CoffeeMachine.h"

class BevaregesInitializer
{

public:
	BevaregesInitializer();


	void Initialize(HWND hDlg, int nIDDlgItem[BEVAREGE_COUNT]);
	void InitializePrice(HWND hDlg, int nIDDlgItem[BEVAREGE_COUNT]);

private:
	void Initialize();

private:
	coffe_price bevariges[BEVAREGE_COUNT];
};

