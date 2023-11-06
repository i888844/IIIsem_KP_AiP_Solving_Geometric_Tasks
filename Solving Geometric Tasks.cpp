#include <iostream>
#include "conio.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "windows.h"
#include "wingdi.h"
#include "locale.h"

#pragma warning(disable: 4996)

typedef struct
{
    int x;
    int y;
} dot;

HDC hDC;
HWND hWnd;
RECT Rect;
HBRUSH hBrush;
HBRUSH hOldBrush;
HBRUSH hBrushBlack = CreateSolidBrush(RGB(0, 0, 0));
HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
HBRUSH hBrushRed = CreateSolidBrush(RGB(255, 0, 0));
HBRUSH hBrushGrey = CreateSolidBrush(RGB(71, 74, 81));
HFONT hFont;
HFONT hOldFont;
LOGFONT Lf = { 0 };

bool is_square_and_sides_not_zero(dot* rect_dots)
{
    bool result = false;
    int left_side = sqrt(pow(rect_dots[3].x - rect_dots[0].x, 2) + pow(rect_dots[3].y - rect_dots[0].y, 2));
    int right_side = sqrt(pow(rect_dots[2].x - rect_dots[1].x, 2) + pow(rect_dots[2].y - rect_dots[1].y, 2));
    int top_side = sqrt(pow(rect_dots[1].x - rect_dots[0].x, 2) + pow(rect_dots[1].y - rect_dots[0].y, 2));
    int bottom_side = sqrt(pow(rect_dots[2].x - rect_dots[3].x, 2) + pow(rect_dots[2].y - rect_dots[3].y, 2));
    if (left_side != 0 && left_side == right_side && top_side != 0 && top_side == bottom_side)
    {
        result = true;
    }
    return result;
}

bool sides_parallel_to_axes(dot* rect_dots)
{
    bool result = false;
    if (rect_dots[0].x == rect_dots[3].x && rect_dots[1].x == rect_dots[2].x && rect_dots[0].y == rect_dots[1].y && rect_dots[3].y == rect_dots[2].y)
    {
        result = true;
    }
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    Lf.lfHeight = 32;
    Lf.lfWeight = 900;
    Lf.lfWidth = 16;
    Lf.lfCharSet = RUSSIAN_CHARSET;
    strcpy((char*)Lf.lfFaceName, "Times New Roman");
    hFont = CreateFontIndirect(&Lf);
    hOldFont = (HFONT)SelectObject(hDC, hFont);
    SetTextColor(hDC, RGB(0, 0, 0));
    SetBkColor(hDC, RGB(255, 255, 255));
    GetClientRect(hWnd, &Rect);
    dot rect_dots[4];
    printf("Введите точки углов квадрата:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("Введите X для точки №%i: ", i + 1);
        scanf_s("%i", &rect_dots[i].x);
        printf("Введите Y для точки №%i: ", i + 1);
        scanf_s("%i", &rect_dots[i].y);
    }
    while (!is_square_and_sides_not_zero(&rect_dots[0]) || !sides_parallel_to_axes(&rect_dots[0]))
    {
        printf("[Ошибка]: введённые координаты не образуют квадрат, стороны которого параллельны осям. Повторите попытку:");
        for (int i = 0; i < 4; i++)
        {
            printf("\nВведите X для точки №%i: ", i + 1);
            scanf_s("%i", &rect_dots[i].x);
            printf("\nВведите Y для точки №%i: ", i + 1);
            scanf_s("%i", &rect_dots[i].y);
        }
    }
    return 0;
}