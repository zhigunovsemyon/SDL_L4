#ifndef _MAIN_H_
#define _MAIN_H_

#include "SDL.h"
#ifndef SDL_h_
#include <SDL2/SDL.h>
#endif

#include <time.h>

enum Errors
{
	NOERR,
	SDLERR,
	TOO_MANY_CIRCLES
};

/*Диапазон диаметров круга*/
#define MAX_D 50
#define MIN_D 5

/*Количество кругов*/
#define COUNT 10

/*Размеры окна*/
#define WIN_W 1024
#define WIN_H 600

/*Цвета фона и кругов*/
#define BGCOLOUR 0x77, 0xAA, 0x42
#define FGCOLOUR 0x20, 0x20, 0x20

/*Структура, содержащая координаты ЛВ угла круга, его диаметр*/
typedef struct
{
	Uint16 x;
	Uint16 y;
	Uint16 d;
}
Circle;

/*Параметры программы*/
typedef struct
{
	int runs;	   // Флаг её работы
	int addCircle; // Флаг изменения числа кругов
	union		   //"Конкатинация" координат нажатой мыши
	{
		Uint32 rmCircle; // Флаг нажатия мыши
		struct
		{
			Uint16 rm_x; // Координаты нажатия
			Uint16 rm_y; // Координаты нажатия
		};
	};
}
ProgMode;

// Подключение остальных заголовков
#include "misc.h"
#include "sdl_drawing.h"
#include "sdl_misc.h"

#endif // !_MAIN_H_
