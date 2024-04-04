#include "misc.h"

int PseudoRandom(int a, int b)
{
	//"Переворот" значений по необходимости
	if (a > b)
	{
		int tmp = a;
		a = b;
		b = tmp;
	}

	return (rand() % (b - a)) + a;
}

void RmCircle(Circle* Circles, Uint8* CircleCount, Uint16 x, Uint16 y)
{
	//Перебираем круги
	for (int i = 0; i < *CircleCount; ++i)
	{
		//Если координата x входит в отрезок ширины круга
		if ((x > Circles[i].x) && (x < Circles[i].x + Circles[i].d))
			//Если координата y входит в отрезок высоты круга
			if ((y > Circles[i].y) && (y < Circles[i].y + Circles[i].d))
			{
				//Удаляемый круг перезаписывается крайним, число кругов уменьшается
				Circles[i] = Circles[--(*CircleCount)]; 
				return; //Прерывание цикла после обнаружения и удаления круга
			}
	}
	return; //Завершение работы, если не было совпадения
}

int CreateCircle(Circle* Circles, Uint8* CircleCount, Uint8 CircleMax, 
	const SDL_Point* screenSize, int range_min, int range_max)
{
	if (CircleMax <= *CircleCount)	//Если массив и так наполнен кругами,
		return TOO_MANY_CIRCLES;	//то осуществляется возврат соответствующего кода

	/*Ячейки для хранения временных значений перед записью*/
	int tmp_x, tmp_y, tmp_d;

	//начальные значения
	tmp_d = PseudoRandom(range_min, range_max);
	tmp_y = PseudoRandom(0, screenSize->y - tmp_d);
	tmp_x = PseudoRandom(0, screenSize->x - tmp_d);

	//Цикл перебора существующих кругов, проверка на их пересечение
	int i = 0;
	do
	{
		/*Если круг находится левее существующего круга*/
		if ((tmp_x + tmp_d) < Circles[i].x)
		{	
			i++;	//Сравнение со следующим кругом
			continue;
		}
		/*Если круг находится правее существующего*/
		if ((tmp_x) > (Circles[i].x + Circles[i].d))
		{	
			i++;	//Сравнение со следующим кругом
			continue;
		}

		/*Если условия не сошлись, осуществляется перерасчёт размера круга...*/
		tmp_d = PseudoRandom(range_min, range_max);
		tmp_y = PseudoRandom(0, screenSize->y - tmp_d);
		tmp_x = PseudoRandom(0, screenSize->x - tmp_d);
		i = 0; //и сброс счётчика
	}
	while (i < *CircleCount); //Проверка осуществляется пока не будут перебраны все круги

	//Сохранение корректных значений. Вывод координат нового круга
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "d=%d, x=%d, y=%d\n",
		tmp_d, tmp_x, tmp_y);
	Circles[*CircleCount].d = tmp_d;
	Circles[*CircleCount].x = tmp_x;
	Circles[*CircleCount].y = tmp_y;

	(*CircleCount)++;	//Увеличение кол-ва кругов перед выходом
	return NOERR;		//Возврат кода отсутствия ошибок
}
