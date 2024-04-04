#include "sdl_misc.h"

int CreateWinAndRend(SDL_Renderer **rend, SDL_Window **wind, Uint32 flags, const SDL_Point winSize, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) // Инициализация SDL. При неудаче возврат кода ошибки
		return SDLERR;
	/*Создание окна и рисовальщика. При неудаче возврат кода ошибки*/
	if (SDL_CreateWindowAndRenderer(winSize.x, winSize.y, flags, wind, rend))
		return SDLERR;
	/*Задание заголовка окна. Штатное завершение работы функции*/
	SDL_SetWindowTitle(*wind, title);
	return NOERR;
}

int PrintErrorAndLeaveWithCode(SDL_Renderer *rend, SDL_Window *wind, int errCode)
{
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Ошибка: %s \nЗавершение работы!\n",
				 SDL_GetError()); /*Вывод сообщения об ошибке. Завершение работы с переданным кодом*/
	return LeaveWithCode(rend, wind, errCode);
}

int LeaveWithCode(SDL_Renderer *rend, SDL_Window *wind, int errCode)
{
	// Если rend и wind были созданы, и их адреса не равны NULL, то они должны быть уничтожены при завершении
	if (rend)
		SDL_DestroyRenderer(rend);
	if (wind)
		SDL_DestroyWindow(wind);
	SDL_Quit();
	return errCode;
}

void EventControl(SDL_Event *ev, ProgMode *mode)
{
	// Определение типа события
	switch (ev->type)
	{
	default:
		return;

	case SDL_QUIT:			// Если пользователь решил закрыть программу...
		mode->runs = SDL_FALSE; // Флаг работы программы сбрасывается
		return;

	/*Обработка нажатия клавиши на клавиатуре*/
	case SDL_KEYDOWN:
		switch (ev->key.keysym.scancode)
		{
		default:
			return;

		/*Поднятие флага добавления круга*/
		case SDL_SCANCODE_SPACE:
			mode->addCircle = SDL_TRUE;
			return;

		case SDL_SCANCODE_ESCAPE: // Выход из программы
		case SDL_SCANCODE_RETURN:
		case SDL_SCANCODE_Q:
			mode->runs = SDL_FALSE;
			return;
		}

	case SDL_MOUSEBUTTONDOWN: // Если была нажата левая кнопка мыши
		if (ev->button.button == SDL_BUTTON_LEFT)
		{ // Передача координат нажатия
			mode->rm_x = ev->button.x;
			mode->rm_y = ev->button.y;
		}
		return;
	}
}
