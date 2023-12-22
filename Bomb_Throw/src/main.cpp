#include "Game.h"

int main(int argc, void** argv[])
{
	Game game;
	// основной цикл игры
	while (!game.GetWindow()->IsDone())
	{
		// обработка команд
		game.HandleInput();
		// обновление объектов
		game.Update();
		// отрисовка
		game.Render();
		// обновление тактов
		game.RestartClock();
	}
}