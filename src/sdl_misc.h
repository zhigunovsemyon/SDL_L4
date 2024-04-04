#ifndef _SDL_MISC_H_
#define _SDL_MISC_H_

#include "main.h"

/*Завершение работы SDL, уничтожение рисовальщика rend, окна wind, возврат errCode.*/
int LeaveWithCode(SDL_Renderer *rend, SDL_Window *wind, int errCode);

/*Завершение работы SDL, уничтожение рисовальщика rend, окна wind, возврат errCode. Вывод сообщения ошибки в терминал*/
int PrintErrorAndLeaveWithCode(SDL_Renderer *rend, SDL_Window *wind, int errCode);

/*Вызов SDL_Quit, Создание окна wind, размером winSize, под названием title, рисовальщика rend, с флагами flags*/
int CreateWinAndRend(SDL_Renderer **rend, SDL_Window **wind, Uint32 flags, const SDL_Point winSize, const char *title);

/*Обработка событий ev, сохранение результатов в стуркутру mode*/
void EventControl(SDL_Event *ev, ProgMode *mode);

#endif // !_SDL_INIT_DEINIT_H_
