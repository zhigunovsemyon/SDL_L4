#ifndef _MISC_H_
#define _MISC_H_

#include "main.h"

/*Генератор псевдослучайных целых чисел из диапазона
Требует задания сида посредством вызова ф-ции srand(*источник сида*)*/
int PseudoRandom(int, int);

/*Функция добавляет новый круг в массив Circles из CircleCount кругов, с размером в диапазоне (range_min, range_max)
Проверяет на максимальное число кругов. Возращает 0 по добавлении, либо код ошибки*/
int CreateCircle(Circle *Circles, Uint8 *CircleCount, Uint8 CircleMax, const SDL_Point *screenSize, int range_min,
				 int range_max);

/*Удаление круга по координатам (x,y) из массива circles в CircleCount элементов*/
void RmCircle(Circle *Circles, Uint8 *CircleCount, Uint16 x, Uint16 y);

#endif // !_MISC_H_
