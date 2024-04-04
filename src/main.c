/*Появление кругов (не более 10) различного диаметра (от 5 до
50) в различных координатах окна (с проверкой отсутствия
наложения кругов друг на друга) при нажатии на пробел. При левом
щелчке мышью по кругу, происходит его удаление. Организовать
контроль количества кругов на поле (не более 10 одновременно)*/
#include "main.h"

int main(int argc, char *args[])
{
	srand(time(NULL));					 // Создание сида для генератора чисел
	SDL_Colour bgCol = {BGCOLOUR, 0xFF}; // Цвет фона
	SDL_Colour fgCol = {FGCOLOUR, 0xFF}; // Цвет кругов
	SDL_Window *win = NULL;				 // Объявление окна
	SDL_Renderer *rend = NULL;			 // Объявление рисовальщика
	SDL_Event ev;						 // Объявление контейнера событий
	ProgMode mode;						 // Объявление контейнера флагов программы
	SDL_Point winSize = {WIN_W, WIN_H};	 // Задание размера окна
	Circle cirs[COUNT];					 // Объявление массива кругов

	Uint8 circle_count = 0;		 	 	// Инициализация числа кругов
	mode.rmCircle = SDL_FALSE;	 	 	// Сброс флага удаления круга
	mode.addCircle = SDL_FALSE;	 	 	// Сброс флага добавления круга
	mode.runs = SDL_TRUE;		 	 	// Установка флага работы программы

	/*Создание окна и рисовальщика. Проверка на то, удалось ли это*/
	int errCode = CreateWinAndRend(&rend, &win, SDL_WINDOW_SHOWN, winSize, "Лабораторная работа №5");
	if (errCode) // Если не удалось, то осуществляется завершение работы с кодом ошибки
		return PrintErrorAndLeaveWithCode(rend, win, errCode);

	while (mode.runs) // Цикл работы программы
	{
		while (!(SDL_PollEvent(&ev))) // Так как без событий изображение остаётся статичным
			continue;				  // Можно не делать повторную отрисовку

		EventControl(&ev, &mode); // Обработка событий

		if (mode.addCircle) // Добавление нового круга при соответсвующем флаге
		{
			mode.addCircle = SDL_FALSE; // Возврат флага в исходное положение

			/*Добавление нового круга.*/
			if (CreateCircle(cirs, &circle_count, COUNT, &winSize, MIN_D, MAX_D))
				SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, // Если количество кругов превышает максимально допустимое...
							"Достигнуто максимальное число кругов!\n"); // то осуществляется вывод сообщения
		}

		// Если флаг удаления круга поднят
		if (mode.rmCircle)
		{ // Удаление круга по данной координате
			RmCircle(cirs, &circle_count, mode.rm_x, mode.rm_y);
			mode.rmCircle = SDL_FALSE; // Сброс флага
		}

		// Отрисовка фона. Если это не удалось осуществить, завершение работы программы
		if ((errCode = SDL_SetRenderDrawColor(rend, bgCol.r, bgCol.g, bgCol.b, bgCol.a)) ||
			(errCode = SDL_RenderClear(rend)))
			return PrintErrorAndLeaveWithCode(rend, win, errCode);

		// Рисовка кругов из массива. Если это не удалось осуществить, завершение работы программы
		if (errCode = DrawCircles(rend, cirs, circle_count, &fgCol))
			return PrintErrorAndLeaveWithCode(rend, win, errCode);

		// Отображение полученного результата.
		SDL_RenderPresent(rend);
	}

	// Штатное завершение работы
	return LeaveWithCode(rend, win, errCode);
}
