#include "BevaregesInitializer.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>


BevaregesInitializer::BevaregesInitializer()
{
	Initialize();
}

void BevaregesInitializer::Initialize()
{

	bevariges[0].description = "������� - ��������";
	bevariges[0].price = 1;
	
	bevariges[1].description = "������� - ����";
	bevariges[1].price = 1;

	bevariges[2].description = "������� - �����";
	bevariges[2].price = 1;

	bevariges[3].description = "���� � �����";
	bevariges[3].price = 1.2;

	bevariges[4].description = "��������";
	bevariges[4].price = 1.3;

	bevariges[5].description = "��������";
	bevariges[5].price = 1.4;

	bevariges[6].description = "��������� ����";
	bevariges[6].price = 2;

	bevariges[7].description = "�����";
	bevariges[7].price = 0.8;

	bevariges[8].description = "���";
	bevariges[8].price = 0.8;

	bevariges[9].description = "�������";
	bevariges[9].price = 0.8;

	bevariges[10].description = "������������ ����";
	bevariges[10].price = 1.5;

	bevariges[11].description = "��� � ����";
	bevariges[11].price = 1.30;

}

void BevaregesInitializer::Initialize(HWND hDlg, int nIDDlgItem[BEVAREGE_COUNT])
{
	for (int i = 0; i < BEVAREGE_COUNT; i++)
	{
		SetDlgItemText(hDlg, nIDDlgItem[i], bevariges[i].description.c_str());
	}
}

void BevaregesInitializer::InitializePrice(HWND hDlg, int nIDDlgItem[BEVAREGE_COUNT])
{
	for (int i = 0; i < BEVAREGE_COUNT; i++)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(2) << bevariges[i].price;
		std::string price = stream.str();

		SetDlgItemText(hDlg, nIDDlgItem[i], price.c_str());
	}
}

void BevaregesInitializer::GetBevarigeByNumber(int number, coffe_price& bevarige)
{
	if (number < 1 || number > BEVAREGE_COUNT)
		return;

	bevarige = bevariges[--number];
}




