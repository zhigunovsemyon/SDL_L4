#include "sdl_drawing.h"

/*Количество вершин круга*/
static const int circle_presicion = 18;

/*Рисование круга рисовальщиком rend, радиуса rad, c ЛВ углом в (x,y), цвета col
Возвращает 0 при штатной работе, либо код ошибки*/
static int DrawCircle(SDL_Renderer *rend, Uint8 rad, int x, int y, const SDL_Colour *col)
{
	SDL_FPoint inCentre = {x + rad, y + rad}, // Центр круга
		texc = {0.0f, 0.0f};				  // Заглушка полигона

	SDL_Vertex verts[3]; // 3 вершины полигона
	verts[0].color = verts[1].color = verts[2].color = *col;

	verts[0].tex_coord = verts[1].tex_coord = verts[2].tex_coord = texc;

	// Определение вершины, расположенной в центре круга на всех полигонах
	verts[0].position = inCentre;

	for (int i = 0; i < circle_presicion; ++i)
	{
		// Определение остальных вершин полигонов, сдвинутых на углы
		//(i / кол-во полигонов) и (1+i / кол-во полигонов)
		verts[1].position.x = inCentre.x + rad * SDL_cosf(2 * M_PI * (i + 1) / circle_presicion);
		verts[1].position.y = inCentre.y - rad * SDL_sinf(2 * M_PI * (i + 1) / circle_presicion);
		verts[2].position.x = inCentre.x + rad * SDL_cosf(2 * M_PI * i / circle_presicion);
		verts[2].position.y = inCentre.y - rad * SDL_sinf(2 * M_PI * i / circle_presicion);

		// Рисование каждого полигона, возврат кода ошибки при её возникновении
		if (SDL_RenderGeometry(rend, NULL, verts, 3, NULL, 0))
			return SDLERR;
	}
	return NOERR;
}

int DrawCircles(SDL_Renderer *rend, Circle *circles, Uint8 circleCount, const SDL_Colour *col)
{
	for (int i = 0; i < circleCount; i++) // Перебор элементов массива
	{
		// Рисование i-го круга, возрат  кода ошибки если не удалось
		if (DrawCircle(rend, circles[i].d / 2, circles[i].x, circles[i].y, col))
			return SDLERR;
	}
	return NOERR; // Код отсутсвия ошибок
}
