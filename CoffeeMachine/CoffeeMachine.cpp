// CoffeeMachine.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "CoffeeMachine.h"
#include "CoffePriceStruct.h"
#include "BevaregesInitializer.h"
#include"commctrl.h"
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

money currentInputMoney;
int currentInputMoneyValue = 0;
coffe_price currentBevarige;

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CoffeMachine(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Money(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Result(HWND, UINT, WPARAM, LPARAM);
void InitializeDrinks(HWND hDlg);
void InitializeCoffeeMachineDialog(HWND hDlg);
void InitializeMoney(HWND hDlg);
std::string GetMoneyStringvalue();
void ChangeMoneyDlgValue(HWND hDlg);
void ChangeCoffeeDlgMoneyValue(HWND hDlg);
void CalculateMoney();
void SetInfoText(HWND hDlg, LPSTR text);
int GetButtonNumber(int button);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_COFFEEMACHINE, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COFFEEMACHINE));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//  FUNCTION: MyRegisterClass()
//  PURPOSE: Registers the window class.
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COFFEEMACHINE));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_COFFEEMACHINE);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//   FUNCTION: InitInstance(HINSTANCE, int)
//   PURPOSE: Saves instance handle and creates main window
//   COMMENTS:
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   DialogBox(hInst, MAKEINTRESOURCE(IDD_COFFEE_MACHINE), hWnd, CoffeMachine);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

void SetInfoText(HWND hDlg, LPSTR text)
{
    SetDlgItemText(hDlg, IDC_STT_INFO, text);
}

int GetButtonNumber(int button)
{
    int number = 0;

    switch (button)
    {
    case IDC_BUTTON1:
        number = 1;
        break;
    case IDC_BUTTON2:
        number = 2;
        break;
    case IDC_BUTTON3:
        number = 3;
        break;
    case IDC_BUTTON4:
        number = 4;
        break;
    case IDC_BUTTON5:
        number = 5;
        break;
    case IDC_BUTTON6:
        number = 6;
        break;
    case IDC_BUTTON7:
        number = 7;
        break;
    case IDC_BUTTON8:
        number = 8;
        break;
    case IDC_BUTTON9:
        number = 9;
        break;
    case IDC_BUTTON10:
        number = 10;
        break;
    case IDC_BUTTON11:
        number = 11;
        break;
    case IDC_BUTTON12:
        number = 12;
        break;
    default:
        break;
    }

    return number;
}

void EnableAllBevarige(HWND hDlg, BOOL desable)
{
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON1), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON2), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON3), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON4), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON5), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON6), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON7), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON8), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON9), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON10), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON11), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON12), desable);
}

void EnableSuger(HWND hDlg, BOOL desable)
{
    EnableWindow(GetDlgItem(hDlg, IDC_RADIO1), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_RADIO2), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_RADIO3), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_RADIO4), desable);
    EnableWindow(GetDlgItem(hDlg, IDC_RADIO5), desable);
}

void InitializeCoffeeMachineDialog(HWND hDlg)
{
    money newInputMoney;
    currentInputMoney = newInputMoney;
    int currentInputMoneyValue = 0;
    coffe_price newBevarige;
    currentBevarige = newBevarige;

    InitializeDrinks(hDlg);

    CheckDlgButton(hDlg, IDC_RADIO3, MFS_CHECKED);
    EnableWindow(GetDlgItem(hDlg, IDC_BUUTON_GET), FALSE);
    EnableAllBevarige(hDlg, TRUE);
    EnableSuger(hDlg, TRUE);
    SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, 0, 0);
    ChangeCoffeeDlgMoneyValue(hDlg);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_ENTER_SUM), TRUE);
    SetInfoText(hDlg, (LPSTR)"Въведете желаната сума.");
}

void InitializeMoney(HWND hDlg)
{
    SetDlgItemText(hDlg, IDC_EDT_05, std::to_string(currentInputMoney.conut05).c_str());
    SetDlgItemText(hDlg, IDC_EDT_10, std::to_string(currentInputMoney.conut10).c_str());
    SetDlgItemText(hDlg, IDC_EDT_20, std::to_string(currentInputMoney.conut20).c_str());
    SetDlgItemText(hDlg, IDC_EDT_50, std::to_string(currentInputMoney.conut50).c_str());
    SetDlgItemText(hDlg, IDC_EDT_1 , std::to_string(currentInputMoney.conut1).c_str());

    ChangeMoneyDlgValue(hDlg);
}

void InitializeDrinks(HWND hDlg)
{
    int nIDDlgItem[BEVAREGE_COUNT];
    nIDDlgItem[0] = IDC_BUTTON1;
    nIDDlgItem[1] = IDC_BUTTON2;
    nIDDlgItem[2] = IDC_BUTTON3;
    nIDDlgItem[3] = IDC_BUTTON4;
    nIDDlgItem[4] = IDC_BUTTON5;
    nIDDlgItem[5] = IDC_BUTTON6;
    nIDDlgItem[6] = IDC_BUTTON7;
    nIDDlgItem[7] = IDC_BUTTON8;
    nIDDlgItem[8] = IDC_BUTTON9;
    nIDDlgItem[9] = IDC_BUTTON10;
    nIDDlgItem[10] = IDC_BUTTON11;
    nIDDlgItem[11] = IDC_BUTTON12;

    int nIDDlgItemPrice[BEVAREGE_COUNT];
    nIDDlgItemPrice[0] = IDC_PRICE_1;
    nIDDlgItemPrice[1] = IDC_PRICE_2;
    nIDDlgItemPrice[2] = IDC_PRICE_3;
    nIDDlgItemPrice[3] = IDC_PRICE_4;
    nIDDlgItemPrice[4] = IDC_PRICE_5;
    nIDDlgItemPrice[5] = IDC_PRICE_6;
    nIDDlgItemPrice[6] = IDC_PRICE_7;
    nIDDlgItemPrice[7] = IDC_PRICE_8;
    nIDDlgItemPrice[8] = IDC_PRICE_9;
    nIDDlgItemPrice[9] = IDC_PRICE_10;
    nIDDlgItemPrice[10] = IDC_PRICE_11;
    nIDDlgItemPrice[11] = IDC_PRICE_12;

    BevaregesInitializer bevaregesInitializer;
    bevaregesInitializer.Initialize(hDlg, nIDDlgItem);
    bevaregesInitializer.InitializePrice(hDlg, nIDDlgItemPrice);
}

void OnBevarige(HWND hDlg, int bevarigeNumber)
{
    coffe_price bevarige;
    BevaregesInitializer().GetBevarigeByNumber(bevarigeNumber, bevarige);
    double currentMoney = currentInputMoneyValue / 100.0;
    if (currentMoney < bevarige.price)
    {
        SetInfoText(hDlg, (LPSTR)"Недостатъчна наличност. \nВъведете по-голяма сума или изберете друга напитка.");
        return;
    }

    SetInfoText(hDlg, (LPSTR)"Напитката Ви е в процес на приготвяне.");

    EnableAllBevarige(hDlg, FALSE);
    EnableSuger(hDlg, FALSE);
    EnableWindow(GetDlgItem(hDlg, IDC_BUTTON_ENTER_SUM), FALSE);

    for (int i = 0; i <= 100; i++)
    {
        SendDlgItemMessage(hDlg, IDC_PROGRESS1, PBM_SETPOS, i, 0);
        std::this_thread::sleep_for(std::chrono::milliseconds(15));
    }

    SetInfoText(hDlg, currentMoney == bevarige.price ? (LPSTR)"Вземете вашата напитка." : (LPSTR)"Вземете вашата напитка и ресто.");

    HWND buttonHandle = GetDlgItem(hDlg, IDC_BUUTON_GET);
    EnableWindow(buttonHandle, TRUE);
}

INT_PTR CALLBACK CoffeMachine(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        InitializeCoffeeMachineDialog(hDlg);

        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == IDCANCEL)
        {
            PostQuitMessage(0);
        }
        else if (LOWORD(wParam) == IDC_BUTTON_ENTER_SUM)
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_MONNEY), hDlg, Money);
            ChangeCoffeeDlgMoneyValue(hDlg);

            SetInfoText(hDlg, currentInputMoneyValue > 0 ? (LPSTR)"Изберете желаната напитка." : (LPSTR)"Въведете желаната сума.");
        }
        else if (LOWORD(wParam) == IDC_BUUTON_GET)
        {
            DialogBox(hInst, MAKEINTRESOURCE(IDD_RESULT), hDlg, Result);
            InitializeCoffeeMachineDialog(hDlg);
        }
        else if (GetButtonNumber(LOWORD(wParam)) != 0) // въведена е напитка
        {
            OnBevarige(hDlg, (GetButtonNumber(LOWORD(wParam))));
        }
        break;
    }
    }
    return (INT_PTR)FALSE;
}

void Increment(HWND hDlg, int resourse, int& value)
{
    SetDlgItemText(hDlg, resourse, std::to_string(++value).c_str());
    ChangeMoneyDlgValue(hDlg);
}

void Decrement(HWND hDlg, int resourse, int& value)
{
    if (value == 0)
        return;

    SetDlgItemText(hDlg, resourse, std::to_string(--value).c_str());
    ChangeMoneyDlgValue(hDlg);
}

void CalculateMoney()
{
    currentInputMoneyValue =
        currentInputMoney.conut05 * 5
        + currentInputMoney.conut10 * 10
        + currentInputMoney.conut20 * 20
        + currentInputMoney.conut50 * 50
        + currentInputMoney.conut1 * 100;
}

std::string GetMoneyStringvalue()
{
    CalculateMoney();

    int firstNumber = currentInputMoneyValue / 100;
    int secondNumber = currentInputMoneyValue % 100;

    std::string firstNumberString = std::to_string(firstNumber).c_str();
    std::string secondNumberString = std::to_string(secondNumber).c_str();

    if (secondNumber < 9)
        secondNumberString = "0" + secondNumberString;

    std::string finalValue = (firstNumberString + "," + secondNumberString + " лв");

    return finalValue;
}

void ChangeMoneyDlgValue(HWND hDlg)
{
    SetDlgItemText(hDlg, IDC_EDIT_VALUE, GetMoneyStringvalue().c_str());
}

void ChangeCoffeeDlgMoneyValue(HWND hDlg)
{
    SetDlgItemText(hDlg, IDC_EDT_COFFE_MONEY, GetMoneyStringvalue().c_str());
}

// Message handler for about box.
INT_PTR CALLBACK Money(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        InitializeMoney(hDlg);

        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {
            switch (LOWORD(wParam))
            {
            case IDC_BTT_MIN_05:
                Decrement(hDlg, IDC_EDT_05, currentInputMoney.conut05);
                break;
            case IDC_BTT_MIN_10:
                Decrement(hDlg, IDC_EDT_10, currentInputMoney.conut10);
                break;
            case IDC_BTT_MIN_20:
                Decrement(hDlg, IDC_EDT_20, currentInputMoney.conut20);
                break;
            case IDC_BTT_MIN_50:
                Decrement(hDlg, IDC_EDT_50, currentInputMoney.conut50);
                break;
            case IDC_BTT_MIN_1:
                Decrement(hDlg, IDC_EDT_1, currentInputMoney.conut1);
                break;
            case IDC_BTT_PLUS_05:
                Increment(hDlg, IDC_EDT_05, currentInputMoney.conut05);
                break;
            case IDC_BTT_PLUS_10:
                Increment(hDlg, IDC_EDT_10, currentInputMoney.conut10);
                break;
            case IDC_BTT_PLUS_20:
                Increment(hDlg, IDC_EDT_20, currentInputMoney.conut20);
                break;
            case IDC_BTT_PLUS_50:
                Increment(hDlg, IDC_EDT_50, currentInputMoney.conut50);
                break;
            case IDC_BTT_PLUS_1:
                Increment(hDlg, IDC_EDT_1, currentInputMoney.conut1);
                break;
            default:
                break;
            }
        }
        break;
    }

    return (INT_PTR)FALSE;
}


INT_PTR CALLBACK Result(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    { 

       HICON hIcon = (HICON)LoadImage(NULL, "C:\\Users\\Alex\\Desktop\\Уни\\3 година\\1 Семестър\\Курсов проект\\ico\\Coffee.ico", IMAGE_ICON, 132, 132, LR_LOADFROMFILE);
        SendDlgItemMessage(hDlg, IDC_PIC, STM_SETICON, (WPARAM)hIcon, 0);

        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else
        {

        }
        break;
    }

    return (INT_PTR)FALSE;
}




