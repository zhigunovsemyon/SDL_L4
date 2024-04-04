#ifndef _SDL_DRAWING_H_
#define _SDL_DRAWING_H_

#include "main.h"

/*Рисование кругов из массива circles рисовальщиком rend, цвета col*/
int DrawCircles(SDL_Renderer *rend, Circle *circles, Uint8 circleCount, const SDL_Colour *col);

#endif // !_SDL_DRAWING_H_
